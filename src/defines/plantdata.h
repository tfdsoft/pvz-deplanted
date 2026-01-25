struct __attribute__((aligned(16))) PlantDefinition {
    const unsigned char* PlantImage; // pointer to compressed chr, as found in chr_bank_2
    const unsigned char* Animation;
    const unsigned char* AnimationData;
    const unsigned char PacketIndex; 
    const unsigned short SeedCost;
    const unsigned short RefreshTime; // time in frames to recharge
    const unsigned short LaunchRate;  // time in frames to fire
    const unsigned char Palette;
};

file(chr_game_seedpacket_peashooter, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Peashooter.bin"
};
file(chr_game_animation_peashooter, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Peashooter.bin"
};
file(ani_game_peashooter, fixed_lo.animdata) = {
    0, 1, 0, 2, // idle
    3, 2, 0, 1, // shoot
    0xff        // end of animation
};

file(chr_game_seedpacket_sunflower, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Sunflower.bin"
};
file(chr_game_animation_sunflower, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Sunflower.bin"
};

file(chr_game_seedpacket_cherrybomb, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Cherrybomb.bin"
};
file(chr_game_animation_cherrybomb, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Cherrybomb.bin"
};

file(chr_game_seedpacket_wallnut, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Wallnut.bin"
};
file(chr_game_animation_wallnut, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Wallnut.bin"
};

file(chr_game_seedpacket_potatomine, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Potatomine.bin"
};
file(chr_game_animation_potatomine, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Potatomine.bin"
};

file(chr_game_seedpacket_snowpea, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Snowpea.bin"
};
file(chr_game_animation_snowpea, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Snowpea.bin"
};

file(chr_game_seedpacket_chomper, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Chomper.bin"
};
file(chr_game_animation_chomper, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Chomper.bin"
};

file(chr_game_seedpacket_repeater, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Repeater.bin"
};
file(chr_game_animation_repeater, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Repeater.bin"
};

putinbank(fixed_lo.plantdata)
const struct PlantDefinition PlantData[] = { // ALIGN THIS TO A 16-BYTE BOUNDARY FOR EXTRA  S P E E D

//  SEEDPACKET                          ANIMATION                       ANIMATION DATA          ID  COST    RECHARGE    FIRE RATE   PALETTE
    {chr_game_seedpacket_peashooter,    chr_game_animation_peashooter,  ani_game_peashooter,    0,  100,    450,        90,         0},
    {chr_game_seedpacket_sunflower,     chr_game_animation_sunflower,   ani_game_peashooter,    1,  50,     450,        1500,       0},
    {chr_game_seedpacket_cherrybomb,    chr_game_animation_cherrybomb,  ani_game_peashooter,    3,  150,    3000,       0,          0},
    {chr_game_seedpacket_wallnut,       chr_game_animation_wallnut,     ani_game_peashooter,    2,  50,     1800,       0,          0},
    {chr_game_seedpacket_potatomine,    chr_game_animation_potatomine,  ani_game_peashooter,    37, 25,     1800,       0,          0},
    {chr_game_seedpacket_snowpea,       chr_game_animation_snowpea,     ani_game_peashooter,    4,  175,    450,        90,         1},
    {chr_game_seedpacket_chomper,       chr_game_animation_chomper,     ani_game_peashooter,    31, 150,    450,        0,          1},
    {chr_game_seedpacket_repeater,      chr_game_animation_repeater,    ani_game_peashooter,    5,  200,    450,        90,         0},
};







