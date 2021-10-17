class BuildingLivespace : HouseNoDestruct
{
    scope=0;
};

class Land_Barn_Wood2_Livespace0: BuildingLivespace
{
    scope=1;
    model="SyberiaScripts\data\building\barn\barn_wood2_livespace0.p3d";
    simpleHiddenSelections[] = {
        "barricade_l1",
        "d5_l1",
        "d5_l2",
        "d5_l3",
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
        class Doors1
        {
            displayName="door 1";
            component="Doors1";
            soundPos="doors1_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0.30000001;
            soundOpen="doorWoodSlideBigOpen";
            soundClose="doorWoodSlideBigClose";
            soundLocked="doorWoodSlideBigRattle";
            soundOpenABit="doorWoodSlideBigOpenABit";
        };
        class Doors2
        {
            displayName="door 2";
            component="Doors2";
            soundPos="doors2_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0.30000001;
            soundOpen="doorWoodSlideBigOpen";
            soundClose="doorWoodSlideBigClose";
            soundLocked="doorWoodSlideBigRattle";
            soundOpenABit="doorWoodSlideBigOpenABit";
        };
        class Doors3
        {
            displayName="door 3";
            component="Doors3";
            soundPos="doors3_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0.30000001;
            soundOpen="doorWoodSlideBigOpen";
            soundClose="doorWoodSlideBigClose";
            soundLocked="doorWoodSlideBigRattle";
            soundOpenABit="doorWoodSlideBigOpenABit";
        };
        class Doors4
        {
            displayName="door 4";
            component="Doors4";
            soundPos="doors4_action";
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
};
