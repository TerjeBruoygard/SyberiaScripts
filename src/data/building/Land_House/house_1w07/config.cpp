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
	
	class Land_House_1W07_Livespace0: BuildingLivespace
    {
        simpleHiddenSelections[] = {
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
			"w1_l1",
			"w1_l2",
			"w1_l3",
			"w1_l4",
			"w2_l1",
			"w2_l2",
			"w2_l3",
			"w2_l4",
			"w3_l1",
			"w3_l2",
			"w3_l3",
			"w3_l4",
			"w4_l1",
			"w4_l2",
			"w4_l3",
			"w4_l4",
			"w5_l1",
			"w5_l2",
			"w5_l3",
			"w5_l4",
			"w1",
			"w2",
			"w3",
			"w4",
			"w5",
			"marc",
			"homebook"
        };
		model="\SyberiaScripts\data\building\Land_House\house_1w07\house_1w07_livespace0.p3d";
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
				soundOpen="doorWoodFrontOpen";
				soundClose="doorWoodFrontClose";
				soundLocked="doorWoodFrontRattle";
				soundOpenABit="doorWoodFrontOpenABit";
			};
			class Doors2
			{
				displayName="door 2";
				component="Doors2";
				soundPos="doors2_action";
				animPeriod=1;
				initPhase=0;
				initOpened=0.69999999;
				soundOpen="doorWoodSmallOpen";
				soundClose="doorWoodSmallClose";
				soundLocked="doorWoodSmallRattle";
				soundOpenABit="doorWoodSmallOpenABit";
			};
			class Doors3
			{
				displayName="door 3";
				component="Doors3";
				soundPos="doors3_action";
				animPeriod=1;
				initPhase=0;
				initOpened=0.69999999;
				soundOpen="doorWoodSmallOpen";
				soundClose="doorWoodSmallClose";
				soundLocked="doorWoodSmallRattle";
				soundOpenABit="doorWoodSmallOpenABit";
			};
			class Doors4
			{
				displayName="door 4";
				component="Doors4";
				soundPos="doors4_action";
				animPeriod=1;
				initPhase=0;
				initOpened=0.69999999;
				soundOpen="doorWoodSmallOpen";
				soundClose="doorWoodSmallClose";
				soundLocked="doorWoodSmallRattle";
				soundOpenABit="doorWoodSmallOpenABit";
			};
			class Doors5
			{
				displayName="door 5";
				component="Doors5";
				soundPos="doors5_action";
				animPeriod=1;
				initPhase=0;
				initOpened=0.30000001;
				soundOpen="doorWoodFrontOpen";
				soundClose="doorWoodFrontClose";
				soundLocked="doorWoodFrontRattle";
				soundOpenABit="doorWoodFrontOpenABit";
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
				class door1
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"doors1"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=3;
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
								damage=5;
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
								damage=3;
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
				class door2
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"doors2"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=3;
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
								damage=5;
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
								damage=3;
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
				class door3
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"doors3"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=3;
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
								damage=5;
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
								damage=3;
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
				class door4
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"doors4"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=3;
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
								damage=5;
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
								damage=3;
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
				class door5
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"doors5"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=3;
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
								damage=5;
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
								damage=3;
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
    class Land_House_1W07
    {
		class Livespace0
		{
			//debug = 1;  // разметка
			bboxStart[] = {-100, -100, -100}; // Bounding box min
			bboxEnd[] = {100, 100, 100}; // Bounding box max
			classname = "Land_House_1W07_Livespace0"; // Classname of livespace object
			offset[] = { -0.357422, -1.86346, -2.21387 }; // Livespace object offset on spawn -0.357422, -1.86346, -2.21387
			homebook = "homebook";
			class Door0
			{
				selfDoorId = 0; // ID of this door of livespace. (Check by DebugBuildingTool)
				linkedDoorIds[] = { 0 }; // ID of vanilla house doors. Empty if not exist.
				outerDoor = 1; // Is door from house to outside world
				levels[] = { "d1_l1", "d1_l2", "d1_l3" }; // Selection in p3d relative to this door for each level
			};
			class Door1
			{
				selfDoorId = 1; // ID of this door of livespace. (Check by DebugBuildingTool)
				linkedDoorIds[] = { 1 }; // ID of vanilla house doors. Empty if not exist.
				outerDoor = 0; // Is door from house to outside world
				levels[] = { "d2_l1", "d2_l2", "d2_l3" }; // Selection in p3d relative to this door for each level
			};
			class Door2
			{
				selfDoorId = 2; // ID of this door of livespace. (Check by DebugBuildingTool)
				linkedDoorIds[] = { 2 }; // ID of vanilla house doors. Empty if not exist.
				outerDoor = 0; // Is door from house to outside world
				levels[] = { "d3_l1", "d3_l2", "d3_l3" }; // Selection in p3d relative to this door for each level
			};
			class Door3
			{
				selfDoorId = 3; // ID of this door of livespace. (Check by DebugBuildingTool)
				linkedDoorIds[] = { 3 }; // ID of vanilla house doors. Empty if not exist.
				outerDoor = 0; // Is door from house to outside world
				levels[] = { "d4_l1", "d4_l2", "d4_l3" }; // Selection in p3d relative to this door for each level
			};
			class Door4
			{
				selfDoorId = 4; // ID of this door of livespace. (Check by DebugBuildingTool)
				linkedDoorIds[] = { 4 }; // ID of vanilla house doors. Empty if not exist.
				outerDoor = 1; // Is door from house to outside world
				levels[] = { "d5_l1", "d5_l2", "d5_l3" }; // Selection in p3d relative to this door for each level
			};
			class Barricade0
			{
				component="w1";
				levels[] = { "w1_l1", "w1_l2", "w1_l3" }; // Selection in p3d relative to this barricade for each level
			};
			class Barricade1
			{
				component="w2";
				levels[] = { "w2_l1", "w2_l2", "w2_l3" }; // Selection in p3d relative to this barricade for each level
			};
			class Barricade2
			{
				component="w3";
				levels[] = { "w3_l1", "w3_l2", "w3_l3" }; // Selection in p3d relative to this barricade for each level
			};
			class Barricade3
			{
				component="w4";
				levels[] = { "w4_l1", "w4_l2", "w4_l3" }; // Selection in p3d relative to this barricade for each level
			};
			class Barricade4
			{
				component="w5";
				levels[] = { "w5_l1", "w5_l2", "w5_l3" }; // Selection in p3d relative to this barricade for each level
			};
		};
    };
};