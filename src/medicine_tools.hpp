class SyringeEmpty : Inventory_Base
{
    scope=2;
    displayName="#syb_syringe_empty_name";
    descriptionShort="#syb_syringe_empty_desc";
    model="SyberiaScripts\data\medical\syringe_empty.p3d";
    rotationFlags=17;
    itemSize[]={2,1};
    weight=50;
    absorbency=0;
    varTemperatureMax=100;
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\syringe");
};

class SyringeDirty : Inventory_Base
{
    scope=2;
    displayName="#syb_syringe_dirty_name";
    descriptionShort="#syb_syringe_dirty_desc";
    model="SyberiaScripts\data\medical\syringe_empty.p3d";
    rotationFlags=17;
    itemSize[]={2,1};
    weight=50;
    absorbency=0;
    varTemperatureMax=100;
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\syringe");
};

class SyringeFull : Inventory_Base
{
    scope=2;
    displayName="#syb_syringe_full_name";
    descriptionShort="#syb_syringe_full_desc";
    model="SyberiaScripts\data\medical\syringe_full.p3d";
    rotationFlags=17;
    itemSize[]={2,1};
    weight=100;
    absorbency=0;
    varTemperatureMax=100;
    hiddenSelections[]=
    {
        "camo"
    };
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\syringefluid_med_ca.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\syringe");
    class AnimEvents
    {
        class SoundWeapon
        {
            class Syringe_out
            {
                soundSet="Syringe_out_SoundSet";
                id=201;
            };
            class Syringe_spear
            {
                soundSet="Syringe_spear_SoundSet";
                id=202;
            };
            class Syringe_splash
            {
                soundSet="Syringe_splash_SoundSet";
                id=203;
            };
        };
    };
};