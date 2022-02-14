class CfgPatches {
	class SyberiaScripts {
        units[] = {};
		requiredAddons[] = {"DZ_Data", "DZ_Scripts", "DZ_Gear_Medical", "DZ_Gear_Consumables"};
	};
};

class CfgMods {
	class SyberiaScripts {
		type = "mod";
        author = "Terje Broygard";
        inputs = "SyberiaScripts/inputs/inputs.xml";

		class defs {
			class gameScriptModule {
				value = "";
				files[] = {"SyberiaScripts/scripts/3_Game"};
			};

			class worldScriptModule {
				value = "";
				files[] = {"SyberiaScripts/scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"SyberiaScripts/scripts/5_Mission"};
			};

			class imageSets {
				files[] = { };
			};
		};
	};
};

class CfgVehicles
{
    #include "predef.hpp"
    #include "characters.hpp"
    #include "zombie_redef.hpp"
    #include "animals_redef.hpp"
    #include "fix_items.hpp"
    #include "drinks.hpp"
    #include "foods.hpp"
    #include "medicine_base.hpp"
    #include "electronic_base.hpp"
    #include "sleeping_bags.hpp"
    #include "sounds_emitters.hpp"
    #include "clothing_vests.hpp"
    #include "clothing_masks.hpp"
    #include "clothing_helmets.hpp"
    #include "clothing_medical.hpp"
    #include "clothing_nbc.hpp"
    #include "building_items.hpp"
    #include "building_livespaces.hpp"
    #include "trading_objects.hpp"
    #include "debug_items.hpp"
    #include "vehicle_parts_redef.hpp"
    #include "containers.hpp"
    #include "objective_zones.hpp"
};

class CfgAmmo
{
    #include "ammo.hpp"
};

class CfgSounds
{
    #include "sounds.hpp"
};

class CfgSoundShaders
{
    #include "sounds_shaders.hpp"
};

class CfgSoundSets
{
    #include "sounds_sets.hpp"
};

class CfgSyberia
{
    #include "syberia_config.hpp"
};

class CfgSlots
{
    #include "slots.hpp"
};

class CfgBuildingInfo
{

};

class CfgBuildingResources
{
    #include "building_resources.hpp"
};

#include "map_settings.hpp"