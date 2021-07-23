class BuildingLivespace : HouseNoDestruct
{
    scope=1;
    model="SyberiaScripts\data\building\building_livespace.p3d";
};

class BuildingElement : HouseNoDestruct
{
};

class BuildingLeveledElement : BuildingElement
{
};

class BuildingHomeBook : BuildingElement
{
    scope=1;
    model="SyberiaScripts\data\building\homebook\homebook.p3d";
};

class BuildingDoorBase : BuildingLeveledElement
{
};

class BuildingDoor_T1_L1 : BuildingDoorBase
{
    scope=1;
    indoorOffset[] = { 0.0, 0.0, 0.0 };
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

class BuildingDoor_T1_L2 : BuildingDoorBase
{
    scope=1;
    indoorOffset[] = { 0.0, -0.00402, -0.049804 };
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