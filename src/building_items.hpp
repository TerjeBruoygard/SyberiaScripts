class BuildingElement : HouseNoDestruct
{
};

class BuildingLeveledElement : BuildingElement
{
    prevLevel = "";
    nextLevel = "";
};

class BuildingHomeBook : BuildingElement
{
    scope=1;
    model="SyberiaScripts\data\building\homebook\homebook.p3d";
};

class BuildingDoor_T1_L1 : BuildingLeveledElement
{
    scope=1;
    prevLevel = "";
    nextLevel = "BuildingDoor_T1_L2";
    model="SyberiaScripts\data\building\doors\door_t1_l1.p3d";
    class Doors
    {
        class Doors1
        {
            displayName="door 1";
            component="Doors1";
            soundPos="doors1_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0;
            soundOpen="doorWoodFrontOpen";
            soundClose="doorWoodFrontClose";
            soundLocked="doorWoodFrontRattle";
            soundOpenABit="doorWoodFrontOpenABit";
        };
    };
};

class BuildingDoor_T1_L2 : BuildingLeveledElement
{
    scope=1;
    prevLevel = "BuildingDoor_T1_L1";
    nextLevel = "";
    model="SyberiaScripts\data\building\doors\door_t1_l2.p3d";
    class Doors
    {
        class Doors1
        {
            displayName="door 1";
            component="Doors1";
            soundPos="doors1_action";
            animPeriod=1;
            initPhase=0;
            initOpened=0;
            soundOpen="doorWoodFrontOpen";
            soundClose="doorWoodFrontClose";
            soundLocked="doorWoodFrontRattle";
            soundOpenABit="doorWoodFrontOpenABit";
        };
    };
};