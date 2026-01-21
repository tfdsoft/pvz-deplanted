struct __attribute__((aligned(16))) PlantDefinition {
    const unsigned char* PlantImage; // pointer to compressed chr, as found in chr_bank_2
    const unsigned char* Animation;
    const unsigned char PacketIndex; 
    const unsigned short SeedCost;
    const unsigned short RefreshTime; // time in frames to recharge
    const unsigned short LaunchRate;  // time in frames to fire
};

file(chr_game_seedpacket_peashooter, chr_bank_2) = {
    #embed "../chr/dnt/Game_Seedpacket_Peashooter.bin"
};
file(chr_game_animation_peashooter, chr_bank_2) = {
    #embed "../chr/dnt/Game_Animation_Peashooter.bin"
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

putinbank(fixed_lo.plantdata)
const struct PlantDefinition PlantData[] = {
    {chr_game_seedpacket_peashooter,    chr_game_animation_peashooter,  0,  100,    450,    90},
    {chr_game_seedpacket_sunflower,     chr_game_animation_sunflower,   1,  50,     450,    1500},
    {chr_game_seedpacket_cherrybomb,    chr_game_animation_cherrybomb,  3,  150,   3000,    0},
    {chr_game_seedpacket_wallnut,       chr_game_animation_wallnut,     3,  50,    1800,    0},
    {chr_game_seedpacket_potatomine,    chr_game_animation_potatomine,  3,  50,    1800,    0},
};







