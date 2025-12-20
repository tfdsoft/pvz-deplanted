; welcome to the world's worst IRQ function ever :sob:

; you can't use ANY function in here that uses the
; imaginary registers (rc0-rc31). have fun!

IRQ_LATCH   = $c000
IRQ_RELOAD  = $c001
IRQ_DISABLE = $e000
IRQ_ENABLE  = $e001

.global irq_ptr
.global irq_count
.global irq_table, irq_table_offset

.section .zp.bss
    irq_count:          .fill 1     ; how many IRQs have
                                    ; been executed this
                                    ; frame
    irq_ptr:            .fill 2     ; pointer to next IRQ function

.section .bss
    irq_table_offset:   .fill 1     ; offset in below table
    irq_table:          .fill 31    ; 31 bytes should be enough.
    irq_tmp:            .fill 1     ; 6 bytes * 5 interrupts 
                                    ; = 30 bytes total. have the
                                    ; extra byte to catch the
                                    ; end of the table.

; yes, i am fully aware that there is a better way to do this:
; - only increment the offset by the amount of arguments
; - bake the function pointers into the reload value,
;   using a lookup table

.section .prg_rom_fixed_lo.text.irq,"a",@progbits
.globl irq
    irq:

        pha     ; store A
        txa
        pha     ; store X
        tya
        pha     ; store Y

        sta IRQ_DISABLE ; disable mmc3 irq

        ldy irq_table_offset

        ldx irq_table+0,y
        inx 
        beq exitirq     ; if the reload value is 255,
                        ; don't bother

        ; RUN THIS INTERRUPT
        ; setup new pointer
        lda irq_table+1,y
        ldx irq_table+2,y
        sta irq_ptr+0
        stx irq_ptr+1

        jsr 1f              ; jsr here first since the
                            ; OG 6502 doesn't have an 
                            ; indirect JSR opcode

        ; SETUP NEXT INTERRUPT
        ; code will return here after an rts

        ; increment table offset
        lda irq_table_offset
        clc
        adc #$6
        sta irq_table_offset
        tay

        lda irq_table,y
        sta IRQ_LATCH
        sta IRQ_RELOAD
        sta IRQ_ENABLE

    
        ; EXIT IRQ
    exitirq:
        pla     ; get Y
        tay
        pla     ; get X
        tax
        pla     ; get A
        
        rti
    1:
        jmp (irq_ptr)
    2:
        sta IRQ_LATCH
        sta IRQ_RELOAD
        beq exitirq ; bra




stall:
    1:          ; stall for a bit so that the
        dey     ; register updates are outside
        bne 1b  ; the active display
        rts

    
.globl irq_basic
    irq_basic:
        ;inc irq_count
        rts



.globl irq_set_x_scroll
    ; ptr+3 = new X scroll value
    irq_set_x_scroll:
        ldy #$7
        jsr stall
        
        ldy irq_table_offset

        lda irq_table+3,y
        sta $2005 ;PPU_SCROLL
        sta $2005 ;PPU_SCROLL
        
        ;inc irq_count
        rts



.globl irq_set_chr
    ; ptr+3 = chr bank ID
    ; ptr+4 = chr bank value
    irq_set_chr:
        ldy #$2
        jsr stall

        ldy irq_table_offset

        lda irq_table+3,y
        ldx irq_table+4,y
        
        jsr set_chr_bank    ; args were loaded
                            ; at the start
        ;inc irq_count
        rts



.globl irq_set_chr_and_scroll
    ; ptr+3 = chr bank ID
    ; ptr+4 = chr bank value
    ; ptr+5 = new X scroll value
    irq_set_chr_and_scroll:

    ; inline'd the stall(in) here because it took too long to jsr
        ldy #3
    1:          ; stall for a bit so that the
        dey     ; register updates are outside
        bne 1b  ; the active display


        ldy irq_table_offset

        lda irq_table+3,y
        pha ; push chr bank for faster access later
        ldx irq_table+4,y

        lda irq_table+5,y
        
        sta $2005 ; PPU_SCROLL
        sta $2005 ; PPU_SCROLL

        pla
        ora __bank_select_hi
        sta $8000
        stx $8001

        ;inc irq_count
        rts



.globl irq_copy_bg_palette_and_scroll
    irq_copy_bg_palette_and_scroll:
        ; re-use the irq pointer for the
        ; palette data
        ldy irq_table_offset

        lda irq_table+3,y
        ldx irq_table+4,y
        sta irq_ptr+0
        stx irq_ptr+1

        ;burn cycles
        ldy #1
        jsr stall

        ldx #16

    1:  ; calculate the brightness of the new palette set
        txa
        tay
        dey
        lda (irq_ptr),y
        tay
        lda (PAL_BG_PTR),y
        pha
        dex
        bne 1b

        ; turn off ppu
        lda PPU_MASK_VAR
        and #$E7    ;disable rendering
        sta $2001   ;PPU_MASK

        ; set ppu address
        ldy #16
        lda #$3f
        ldx #$00
        sta $2006
        stx $2006

    1:  ; copy to palette RAM
        pla
        tax ; background color in X
        pla ; color 1 in A
        stx $2007
        sta $2007
        pla ; color 2 in A
        sta $2007
        pla ; color 3 in A
        sta $2007
        dey ; four DEYs take the same amount of time
        dey ; as subtract by four
        dey 
        dey 

        beq 1f  ; exit if four loops complete

        tya
        pha
        ldy #8
        jsr stall
        pla
        tay
        nop
        bne 1b


    1:  ; reset everything before updating scroll

        ; set 2kb chr 0 to the 8th bank
        lda #0
        jsr set_chr_mode_0

        ; The first two PPU writes can come anytime during the scanline:
        ; Nametable number << 2 to $2006.
        lda #2
        lsr
        lda #2
        rol
        asl
        asl
        sta $2006

        ; Y position to $2005.
        lda #49
        sta $2005
        
        ; Prepare for the 2 later writes:
        ; We reuse new_x to hold (Y & $F8) << 2.
        and #%11111000
        asl
        asl
        ldx #0  ; X position in X for $2005 later.
        sta irq_tmp

        ; ((Y & $F8) << 2) | (X >> 3) in A for $2006 later.
        txa
        lsr
        lsr
        lsr
        ora irq_tmp

        nop
        nop
        ldy PPU_MASK_VAR
        ; The last two PPU writes must happen during hblank:
        stx $2005
        sta $2006

        ; Restore new_x.
        ;stx irq_tmp

        sty $2001

        
        inc PAL_UPDATE
        rts




