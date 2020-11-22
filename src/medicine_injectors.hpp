#define INJECTOR_ANIM_EVENTS()\
class AnimEvents\
{\
    class SoundWeapon\
    {\
        class Morphine_spear\
        {\
            soundSet="Morphine_spear_SoundSet";\
            id=201;\
        };\
        class Morphine_out\
        {\
            soundSet="Morphine_out_SoundSet";\
            id=202;\
        };\
    };\
}


class InjectorBase : Inventory_Base
{
    descriptionShort="#syb_injector_base_desc";
    rotationFlags=17;
    itemSize[]={1,2};
    weight=60;
    hiddenSelections[]=
    {
        "zbytek"
    };
};

class InjectorPromedol : InjectorBase
{
    scope=2;
    displayName="#syb_promedol_name";
    model="SyberiaScripts\data\medical\injector.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=2400; // 40 minutes
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\injector_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\injector");
    INJECTOR_ANIM_EVENTS();
};

class InjectorZVirusAntidot : InjectorBase
{
    scope=2;
    displayName="#syb_zvirus_antidot_name";
    model="SyberiaScripts\data\medical\injector.p3d";
    medRemoveZVirus=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\injector_red_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\injector");
    INJECTOR_ANIM_EVENTS();
};

class InjectorTopoizomeraza : InjectorBase
{
    scope=2;
    displayName="#syb_topoizomeraza_name";
    model="SyberiaScripts\data\medical\injector.p3d";
    medRemoveSepsis=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\injector_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\injector");
    INJECTOR_ANIM_EVENTS();
};