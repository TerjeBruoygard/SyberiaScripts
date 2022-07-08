class BuildingLivespace : HouseNoDestruct
{
    scope=1;
    model="SyberiaScripts\data\building\building_livespace.p3d";
};

class BuildingElement : HouseNoDestruct
{
    scope=0;
};

class BuildingLeveledElement : BuildingElement
{
    scope=0;
};

class BuildingHomeBook : BuildingElement
{
    scope=1;
    model="SyberiaScripts\data\building\homebook\homebook.p3d";
};

// ============ DOORS ============ 
class BuildingDoorBase : BuildingLeveledElement
{
    scope=0;
};

class BuildingDoor_T1_L1 : BuildingDoorBase
{
    scope=1;
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

class BuildingDoor_T1_L3 : BuildingDoorBase
{
    scope=1;
    model="SyberiaScripts\data\building\doors\door_t1_l3.p3d";
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

class BuildingDoor_T1_L4 : BuildingDoorBase
{
    scope=1;
    model="SyberiaScripts\data\building\doors\door_t1_l4.p3d";
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

class BuildingDoor_T1_L5 : BuildingDoorBase
{
    scope=1;
    model="SyberiaScripts\data\building\doors\door_t1_l5.p3d";
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

// ============ WINDOWS ============ 
class BuildingWindowBase : BuildingLeveledElement
{
    scope=0;
};

class BuildingWindow_T1_L1 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t1_l1.p3d";
};

class BuildingWindow_T1_L2 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t1_l2.p3d";
};

class BuildingWindow_T1_L3 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t1_l3.p3d";
};

class BuildingWindow_T1_L4 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t1_l4.p3d";
};

class BuildingWindow_T1_L5 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t1_l5.p3d";
};

class BuildingWindow_T2_L1 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t2_l1.p3d";
};

class BuildingWindow_T2_L2 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t2_l2.p3d";
};

class BuildingWindow_T2_L3 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t2_l3.p3d";
};

class BuildingWindow_T2_L4 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t2_l4.p3d";
};

class BuildingWindow_T2_L5 : BuildingWindowBase
{
    scope=1;
    model="SyberiaScripts\data\building\windows\window_t2_l5.p3d";
};