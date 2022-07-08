#define ITEM_DAMAGE_SYSTEM(hitpoints_value, rvmat_path, rvmat_path_damage, rvmat_path_destruct) class DamageSystem {\
    class GlobalHealth {\
        class Health {\
            hitpoints=hitpoints_value;\
            healthLevels[]={\
                { 1.0, { rvmat_path } },\
                { 0.7, { rvmat_path } },\
                { 0.5, { rvmat_path_damage } },\
                { 0.3, { rvmat_path_damage } },\
                { 0.0, { rvmat_path_destruct } }\
            };\
        };\
    };\
}

// Items
class Inventory_Base;
class Edible_Base: Inventory_Base
{
    varTemperatureMin=-100;
};

class Bottle_Base;
class SodaCan_ColorBase;
class Clothing;
class Container_Base;
class BaseBuildingBase;
class House;
class HouseNoDestruct;
class Transmitter_Base;
class EffectArea;

// Characters
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

// Areas
class ContaminatedArea_Static: EffectArea
{
    scope=0;
};
class ContaminatedArea_Dynamic: EffectArea
{
    scope=0;
};