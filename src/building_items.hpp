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

#include "building_items_doors.hpp"
#include "building_items_windows.hpp"