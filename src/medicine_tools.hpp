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
    medicalItem=1;
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\syringe.rvmat", "SyberiaScripts\data\medical\syringe_damage.rvmat", "SyberiaScripts\data\medical\syringe_destruct.rvmat");
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
    medicalItem=1;
    hiddenSelections[]=
    {
        "camo"
    };
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\syringefluid_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\syringe.rvmat", "SyberiaScripts\data\medical\syringe_damage.rvmat", "SyberiaScripts\data\medical\syringe_destruct.rvmat");
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

class BandageHemostatic: BandageDressing
{
    scope=2;
    displayName="#syb_hemostatic_bandage_name";
    descriptionShort="#syb_hemostatic_bandage_desc";
    model="SyberiaScripts\data\medical\hemostatic_bandage.p3d";
    inventorySlot[]=
    {
        "MedicalBandage"
    };
    isMeleeWeapon=1;
    varQuantityInit=1;
    varQuantityMin=0;
    varQuantityMax=1;
    quantityBar=1;
    varQuantityDestroyOnMin=1;
    rotationFlags=17;
    weight=150;
    absorbency=0.0;
    itemSize[]={1,1};
    medBloodStop=3;
    varCleannessInit=1;
    medicalItem=1;
    ITEM_DAMAGE_SYSTEM(80, "DZ\gear\medical\data\bandage.rvmat", "DZ\gear\medical\data\bandage_damage.rvmat", "DZ\gear\medical\data\bandage_destruct.rvmat");
    class AnimEvents
    {
        class SoundWeapon
        {
            class Bandage_loop1
            {
                soundSet="Bandage_loop_SoundSet";
                id=201;
            };
            class Bandage_loop2
            {
                soundSet="Bandage_loop_SoundSet";
                id=202;
            };
            class Bandage_loop3
            {
                soundSet="Bandage_loop_SoundSet";
                id=203;
            };
            class Bandage_start
            {
                soundSet="Bandage_start_SoundSet";
                id=204;
            };
            class Bandage_end
            {
                soundSet="Bandage_end_SoundSet";
                id=205;
            };
        };
    };
};

class SurgicalKit: Inventory_Base
{
    scope=2;
    displayName="#syb_surgical_kit_once_name";
    descriptionShort="#syb_surgical_kit_once_desc";
    model="\dz\gear\tools\sewing_kit.p3d";
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\surgical_kit_co.paa" };
    rotationFlags=17;
    varQuantityInit=100;
    varQuantityMin=0;
    varQuantityMax=100;
    quantityBar=1;
    stackedUnit="percentage";
    varQuantityDestroyOnMin=1;
    weight=300;
    absorbency=0.0;
    itemSize[]={1,2};
    varCleannessInit=1;
    medicalItem=1;
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\tools\data\sewing_kit.rvmat", "DZ\gear\tools\data\sewing_kit_damage.rvmat", "DZ\gear\tools\data\sewing_kit_destruct.rvmat");
};