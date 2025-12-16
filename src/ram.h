__attribute__((section(".aligned.0"),retain)) struct OAM_BUF {
    unsigned char y;
    unsigned char tile;
    unsigned char attr;
    unsigned char x;
} OAM_BUF[64];



unsigned char gamestate=0xff;

unsigned char song;


struct Player {
    // X
    union {
        unsigned _BitInt(24) int24;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } x;
    uint8_t width;

    // Y
    union {
        unsigned _BitInt(24) int24;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } y;
    uint8_t height;

    // properties
    struct {
        uint8_t speed : 3;
        uint8_t can_jump : 1;
        uint8_t click_buffered : 1;
        uint8_t dead : 1;
    } prop;
};
struct Camera {
    union {
        unsigned _BitInt(24) int24;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } x;
    union {
        unsigned _BitInt(24) int24;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } y;
};


__attribute__((retain))
uint8_t return_gamestate;

__attribute__((retain)) struct Player player;
__attribute__((retain)) struct Camera camera;
__attribute__((retain)) int16_t player_speed_x, player_speed_y;

__attribute__((section(".prg_ram"),retain)) 
uint8_t sram_buffer[2048];

#define bg_buffer (&sram_buffer[0])
#define coll_buffer (&sram_buffer[0])

#define bg_buffer_1 (&bg_buffer[0])
#define bg_buffer_2 (&bg_buffer[1024])


__attribute__((section(".prg_ram"),retain)) 
uint8_t saved_menu_theme;