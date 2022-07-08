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
    class SurvivorM_Boris;
    class SurvivorM_Cyril;
    class SurvivorM_Denis;
    class SurvivorM_Elias;
    class SurvivorM_Francis;
    class SurvivorM_Guo;
    class SurvivorM_Hassan;
    class SurvivorM_Indar;
    class SurvivorM_Jose;
    class SurvivorM_Kaito;
    class SurvivorM_Lewis;
    class SurvivorM_Manua;
    class SurvivorM_Niki;
    class SurvivorM_Oliver;
    class SurvivorM_Peter;
    class SurvivorM_Quinn;
    class SurvivorM_Rolf;
    class SurvivorM_Seth;
    class SurvivorM_Taiki;
    class SurvivorF_Eva;
    class SurvivorF_Frida;
    class SurvivorF_Gabi;
    class SurvivorF_Helga;
    class SurvivorF_Irena;
    class SurvivorF_Judy;
    class SurvivorF_Keiko;
    class SurvivorF_Linda;
    class SurvivorF_Maria;
    class SurvivorF_Naomi;

    class SurvivorM_Mirek_Ghost : SurvivorM_Mirek { };
    class SurvivorM_Boris_Ghost : SurvivorM_Boris { };
    class SurvivorM_Cyril_Ghost : SurvivorM_Cyril { };
    class SurvivorM_Denis_Ghost : SurvivorM_Denis { };
    class SurvivorM_Elias_Ghost : SurvivorM_Elias { };
    class SurvivorM_Francis_Ghost : SurvivorM_Francis { };
    class SurvivorM_Guo_Ghost : SurvivorM_Guo { };
    class SurvivorM_Hassan_Ghost : SurvivorM_Hassan { };
    class SurvivorM_Indar_Ghost : SurvivorM_Indar { };
    class SurvivorM_Jose_Ghost : SurvivorM_Jose { };
    class SurvivorM_Kaito_Ghost : SurvivorM_Kaito { };
    class SurvivorM_Lewis_Ghost : SurvivorM_Lewis { };
    class SurvivorM_Manua_Ghost : SurvivorM_Manua { };
    class SurvivorM_Niki_Ghost : SurvivorM_Niki { };
    class SurvivorM_Oliver_Ghost : SurvivorM_Oliver { };
    class SurvivorM_Peter_Ghost : SurvivorM_Peter { };
    class SurvivorM_Quinn_Ghost : SurvivorM_Quinn { };
    class SurvivorM_Rolf_Ghost : SurvivorM_Rolf { };
    class SurvivorM_Seth_Ghost : SurvivorM_Seth { };
    class SurvivorM_Taiki_Ghost : SurvivorM_Taiki { };
    class SurvivorF_Eva_Ghost : SurvivorF_Eva { };
    class SurvivorF_Frida_Ghost : SurvivorF_Frida { };
    class SurvivorF_Gabi_Ghost : SurvivorF_Gabi { };
    class SurvivorF_Helga_Ghost : SurvivorF_Helga { };
    class SurvivorF_Irena_Ghost : SurvivorF_Irena { };
    class SurvivorF_Judy_Ghost : SurvivorF_Judy { };
    class SurvivorF_Keiko_Ghost : SurvivorF_Keiko { };
    class SurvivorF_Linda_Ghost : SurvivorF_Linda { };
    class SurvivorF_Maria_Ghost : SurvivorF_Maria { };
    class SurvivorF_Naomi_Ghost : SurvivorF_Naomi { };
};