class CfgPatches
{
	class SyberiaScripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgVehicles
{
	class BuildingLivespace;
	
	class Land_Garage_Small_Livespace0: BuildingLivespace
    {
        simpleHiddenSelections[] = {
            "barricade_l1",
			"barricade_l2",
			"barricade_l3",
            "d1_l1",
            "d1_l2",
            "d1_l3",
            "d2_l1",
            "d2_l2",
            "d2_l3",
            "d3_l1",
            "d12_l1",
            "d12_l2",
            "d12_l3",
			"w1",
            "homebook"
        };
        model="\SyberiaScripts\data\building\industrial\garages\garage_small\garage_small_livespace0.p3d";
		class Doors
		{
			class DoorsTwin1
			{
				displayName="door Twin1";
				component="DoorsTwin1";
				soundPos="doorsTwin1_action";
				animPeriod=1;
				initPhase=0;
				initOpened=0.30000001;
				soundOpen="doorMetalTwinBigOpen";
				soundClose="doorMetalTwinBigClose";
				soundLocked="doorMetalTwinBigRattle";
				soundOpenABit="doorMetalTwinBigOpenABit";
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
			class DamageZones
			{
				class twin1
				{
					class Health
					{
						hitpoints=2000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"doorsTwin1"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=2;
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
								damage=2.5;
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
								damage=2;
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
		};
    };
};
class CfgBuildingInfo
{
    class Land_Garage_Small
    {
        class Livespace0
        {
            //debug = 1;  // разметка
			bboxStart[] = {6.13555, -2.73677, -7.8543}; // Bounding box min 
            bboxEnd[] = {-6.95293, 2.20354, 7.9916}; // Bounding box max
            classname = "Land_Garage_Small_Livespace0"; // Classname of livespace object
            offset[] = { 0.379883, 0.23674, 0.429688 }; // Livespace object offset on spawn 0.379883, 0.23674, 0.429688
            homebook = "homebook";
            class Door0
            {
                selfDoorId = 0; // ID of this door of livespace. (Check by DebugBuildingTool)0
                linkedDoorIds[] = { 0 }; // ID of vanilla house doors. Empty if not exist.0
                outerDoor = 1; // Is door from house to outside world
                levels[] = {  "d12_l1", "d12_l2" }; // Selection in p3d relative to this door for each level
            };
            class Barricade0
            {
                component="w1";
				levels[] = { "barricade_l1", "barricade_l2" }; // Selection in p3d relative to this barricade for each level
            };
        };
    };
};