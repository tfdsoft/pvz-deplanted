struct PlantDefinition {
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

putinbank(fixed_lo.plantdata)
const struct PlantDefinition PlantData[] __attribute__((aligned(16))) = {
    {chr_game_seedpacket_peashooter,    chr_game_animation_peashooter,  0,  100,    450,    90},
    {chr_game_seedpacket_sunflower,     chr_game_animation_sunflower,   1,  50,     450,    90},
};







