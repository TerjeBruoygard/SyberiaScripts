class Stethoscope: Clothing
{
    scope=2;
    displayName="#syb_stethoscope_name";
    descriptionShort="#syb_stethoscope_desc";
    model="SyberiaScripts\data\medical\Stethoscope_g.p3d";
    vehicleClass="Clothing";
    simulation="clothing";
    medicalItem=1;
    inventorySlot[]=
    {
        "Eyewear"
    };
    itemInfo[]=
    {
        "Clothing",
        "Eyewear"
    };
    rotationFlags=17;
    itemSize[]={3,2};
    weight=200;
    lootCategory="Eyewear";
    lootTag[]=
    {
        "Civilian"
    };
    hiddenSelections[]=
    {
        "camoGround",
        "camoMale",
        "camoFemale"
    };
    class DamageSystem {
        class GlobalHealth {
            class Health {
                hitpoints=50;
                healthLevels[]={
                    { 1.0, { } },
                    { 0.7, { } },
                    { 0.5, { } },
                    { 0.3, { } },
                    { 0.0, { } }
                };
            };
        };
    };
    class ClothingTypes
    {
        male="SyberiaScripts\data\medical\Stethoscope_m.p3d";
        female="SyberiaScripts\data\medical\Stethoscope_m.p3d";
    };
    class AnimEvents
    {
        class SoundWeapon
        {
            class pickUpItem
            {
                soundSet="SportGlasses_pickup_SoundSet";
                id=797;
            };
            class drop
            {
                soundset="SportGlasses_drop_SoundSet";
                id=898;
            };
        };
    };
};