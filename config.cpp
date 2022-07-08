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
				files[] = {};
			};
		};
	};
};

class CfgVehicles
{
    class SurvivorM_Mirek;
    class Survivor_Ghost: SurvivorM_Mirek {
        class BloodyHands
		{
			mat_normal="dz\characters\heads\data\m_adam\hhl_m_adam_body_shaved.rvmat";
			mat_blood="dz\characters\heads\data\m_adam\hhl_m_adam_body_bloodyhands.rvmat";
		};
    };
};