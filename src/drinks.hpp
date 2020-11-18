class SodaCan_EnergyDrink : SodaCan_ColorBase { };
class SodaCan_MadBull: SodaCan_EnergyDrink
{
    scope=2;
    displayName="#syb_mad_bull_name";
    descriptionShort="#syb_mad_bull_desc";
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\drinks\sodacan_madbull_co.paa"
    };
    class AnimEvents
    {
        class SoundWeapon
        {
            class SodaCan_in_B
            {
                soundSet="SodaCan_in_B_SoundSet";
                id=202;
            };
            class WellPond_loop
            {
                soundSet="WellPond_loop_SoundSet";
                id=209;
            };
            class WellBottle_loop
            {
                soundSet="WellBottle_loop_SoundSet";
                id=210;
            };
            class pickup
            {
                soundSet="SodaCan_pickup_SoundSet";
                id=797;
            };
            class drop
            {
                soundset="SodaCan_drop_SoundSet";
                id=898;
            };
        };
    };
};