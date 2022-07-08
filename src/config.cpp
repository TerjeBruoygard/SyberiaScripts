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
    
    class SodaCan_ColorBase;
    class SodaCan_EnergyDrink : SodaCan_ColorBase { };
    class SodaCan_MadBull: SodaCan_EnergyDrink
    {
        scope=2;
        displayName="#syb_mad_bull_name";
        descriptionShort="#syb_mad_bull_desc";
        hiddenSelectionsTextures[]=
        {
            "SyberiaScripts\data\drinks\sodacan_madbull_co.paa"
        };
        class AnimEvents
        {
            class SoundWeapon
            {
                class SodaCan_in_B
                {
                    soundSet="SodaCan_in_B_SoundSet";
                    id=202;
                };
                class WellPond_loop
                {
                    soundSet="WellPond_loop_SoundSet";
                    id=209;
                };
                class WellBottle_loop
                {
                    soundSet="WellBottle_loop_SoundSet";
                    id=210;
                };
                class pickup
                {
                    soundSet="SodaCan_pickup_SoundSet";
                    id=797;
                };
                class drop
                {
                    soundset="SodaCan_drop_SoundSet";
                    id=898;
                };
            };
        };
    };
    
    class Edible_Base;
    class PainkillerTablets : Edible_Base
    {
        scope=0;
    };
    
    class SyberiaMedicineBase : Edible_Base {
        medPainkillerLevel=0;
        medPainkillerTimeSec=0;
    }
    class TabletsBase : SyberiaMedicineBase {
        descriptionShort="#syb_tablets_common_desc";
        rotationFlags=0;
        itemSize[]={1,2};
        varQuantityInit=10;
        varQuantityMin=0;
        varQuantityMax=10;
        varQuantityDestroyOnMin=1;
        weight=20;
        stackedUnit="pills";
        quantityBar=0;
        absorbency=0.69999999;
    };
    class TabletsAnalgin : TabletsBase
    {
        scope=2;
        displayName="#syb_analgin_name";
        model="SyberiaScripts\data\medical\tablets_green.p3d";
        varQuantityInit=10;
        varQuantityMax=10;
        medPainkillerLevel=1;
        medPainkillerTimeSec=900; // 15 minutes
        class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=30;
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Tablets_open
				{
					soundSet="Tablets_open_SoundSet";
					id=201;
				};
				class Tablets_catch
				{
					soundSet="Tablets_catch_SoundSet";
					id=202;
				};
				class Tablets_close
				{
					soundSet="Tablets_close_SoundSet";
					id=203;
				};
				class pickup
				{
					soundSet="purificationtablets_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="purificationtablets_drop_SoundSet";
					id=898;
				};
			};
		};
    };
};