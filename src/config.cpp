class CfgPatches {
	class SyberiaScripts {
        units[] = {};
		requiredAddons[] = {"DZ_Data", "DZ_Scripts"};
	};
};

class CfgMods {
	class SyberiaScripts {
		type = "mod";

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
    #include "drinks.hpp"
    #include "foods.hpp"
    #include "medicine_base.hpp"
    #include "electronic_base.hpp"
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