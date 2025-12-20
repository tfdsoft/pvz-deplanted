#include "../BUILDFLAGS.h"

#include "assets.h"
#include "include.h"

__attribute__((leaf)) __asm__(
    ".section .init.100,\"ax\",@progbits \n"
    ".globl clearRAM \n"
    "clearRAM: \n"
        "lda #0 \n"
        "tax \n"
    "1: \n"
        "sta  $00,x \n"
        "pha \n"
        "sta $200,x \n"
        "sta $300,x \n"
        "sta $400,x \n"
        "sta $500,x \n"
        "sta $600,x \n"
        "sta $700,x \n"
        "inx \n"
        "bne 1b \n"

    // end of clearRAM

    ".section .init.280,\"ax\",@progbits \n"
        "lda #0 \n"
        "sta __rc2 \n"
        "sta __rc3 \n"
        "jsr set_vram_buffer \n"

    ".section .init.300,\"ax\",@progbits \n"
        // make sure the irq doesn't trigger itself
        "lda #255 \n"
        "sta irq_table+0 \n"
        "sta irq_table+6 \n"

        "lda #$37 \n"
        "jsr set_prg_a000 \n"

        "lda #$01 \n"
        "ldx #$00 \n"
        "ldy #$a0 \n"
        "jsr famistudio_init \n"

        "lda #$c0\n"
        "sta $4017\n" // disable apu frame counter irq

/*
        "ldx #$00 \n"
        "tax \n"
        "dex \n"
        "ldy #$a0 \n"
        "jsr famistudio_sfx_init \n"
*/
);

putinbank(fixed_lo)
int main(void){

    PPU.control = PPU_CTRL_VAR = 0b10100000;
    PPU.mask = PPU_MASK_VAR = 0b00000110;
    ppu_off(); // turn off everything

    banked_call(extra_code_bank, state_ramcheck); 
    set_vram_buffer();

    set_wram_mode(WRAM_ON);

    //gamestate = 0x19;

    while(1){
        __asm__("sei");
        pal_bright(0);
        ppu_off();
        oam_clear();
        set_chr_default();
        flush_irq();
        vram_adr(0);
        //famistudio_music_pause(1);

        switch(gamestate){
            // when in doubt, go back to startup
            default: 
                banked_call(extra_code_bank, state_startup); 
                //state_startup();
                break;

            //
            //  CREDITS-RELATED STUFF
            //
            case 0x00:
                banked_call(extra_code_bank, state_credits);
                //state_menu();
                break;
              
            //
            //  MENU-RELATED STUFF
            //
            case 0x10:
                banked_call(extra_code_bank, state_menu);
                break;
  
            //case 0x11:
            //    banked_call(extra_code_bank, state_levelselect);
            //    break;
            
            case 0x19:
                banked_call(extra_code_bank, state_test);
                break;
/*
            case 0x14:
                banked_call(sound_test_bank, state_soundtest);
                break;
*/
            //
            //  GAME-RELATED STUFF
            //
            case 0x20:
                banked_call(extra_code_bank, state_game);
                break;

            //
            //  DEBUG STUFF
            //
            /*case 0xf0:
                banked_call(extra_code_bank, state_bankexplorer);
                break;*/
        }
    }
}