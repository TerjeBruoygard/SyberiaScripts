class BuildingLivespace : HouseNoDestruct
{
    scope=0;
};

class Land_Barn_Wood2_Livespace0: BuildingLivespace
{
    scope=1;
    model="SyberiaScripts\data\building\barn\barn_wood2_livespace0.p3d";
    simpleHiddenSelections[] = {
        "l1",
        "l2",
        "l3",
        "barricade_l1",
        "d1_l1",
        "d1_l2",
        "d1_l3",
        "d2_l1",
        "d2_l2",
        "d2_l3",
        "d3_l1",
        "d3_l2",
        "d3_l3",
        "d4_l1",
        "d4_l2",
        "d4_l3",
        "d5_l1",
        "d5_l2",
        "d5_l3",
        "d5_l2_base",
        "d5_l3_base",
        "d12_l1",
        "d12_l2",
        "d12_l3",
        "d34_l1",
        "d34_l2",
        "d34_l3",
        "homebook"
    };
    class Doors
    {
        class DoorsTwin1
        {
            displayName="door 1";
            component="DoorsTwin1";
            soundPos="doorstwin1_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0.30000001;
            soundOpen="doorWoodSlideBigOpen";
            soundClose="doorWoodSlideBigClose";
            soundLocked="doorWoodSlideBigRattle";
            soundOpenABit="doorWoodSlideBigOpenABit";
        };
        class DoorsTwin2
        {
            displayName="door 3";
            component="DoorsTwin2";
            soundPos="doorstwin2_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0.30000001;
            soundOpen="doorWoodSlideBigOpen";
            soundClose="doorWoodSlideBigClose";
            soundLocked="doorWoodSlideBigRattle";
            soundOpenABit="doorWoodSlideBigOpenABit";
        };
        class Doors5
        {
            displayName="door 5";
            component="Doors5";
            soundPos="doors5_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0.30000001;
            soundOpen="doorWoodNolatchOpen";
            soundClose="doorWoodNolatchClose";
            soundLocked="doorWoodNolatchRattle";
            soundOpenABit="doorWoodNolatchOpenABit";
        };
    };
    class DamageSystem
    {
        class GlobalHealth
        {
            class Health
            {
                hitpoints=1000;
            };
        };
        class GlobalArmor
        {
            class Projectile
            {
                class Health
                {
                    damage=0;
                };
                class Blood
                {
                    damage=0;
                };
                class Shock
                {
                    damage=0;
                };
            };
            class Melee
            {
                class Health
                {
                    damage=0;
                };
                class Blood
                {
                    damage=0;
                };
                class Shock
                {
                    damage=0;
                };
            };
            class FragGrenade
            {
                class Health
                {
                    damage=0;
                };
                class Blood
                {
                    damage=0;
                };
                class Shock
                {
                    damage=0;
                };
            };
        };
    };
};
