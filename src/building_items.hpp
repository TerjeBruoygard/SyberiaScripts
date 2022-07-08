class BuildingHomeBook : HouseNoDestruct
{
    scope=1;
    model="SyberiaScripts\data\building\homebook\homebook.p3d";
};

class BuildingDoor_T1_L1 : HouseNoDestruct
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