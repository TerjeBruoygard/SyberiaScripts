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

class InjectorZivirol : InjectorBase
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

class InjectorErytropoenin : InjectorBase
{
    scope=2;
    displayName="#syb_erytropoenin_name";
    model="SyberiaScripts\data\medical\injector.p3d";
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=900;
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=900;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\injector_red_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\injector");
    INJECTOR_ANIM_EVENTS();
};

class InjectorNeiroks : InjectorBase
{
    scope=2;
    displayName="#syb_neiroks_name";
    model="SyberiaScripts\data\medical\injector.p3d";
    medConcussionHeal=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\injector_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\injector");
    INJECTOR_ANIM_EVENTS();
};

class InjectorAmoksivan : InjectorBase
{
    scope=2;
    displayName="#syb_amoksivan_name";
    model="SyberiaScripts\data\medical\injector.p3d";
    medAntibioticLevel=3;
    medAntibioticsTimeSec=2500;
    medAntibioticsStrength=5.0;
    medRemoveSepsis=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\injector_red_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\injector");
    INJECTOR_ANIM_EVENTS();
};

class InjectorKetorol : InjectorBase
{
    scope=2;
    displayName="#syb_ketorol_name";
    model="SyberiaScripts\data\medical\injector.p3d";
    medStomatchhealLevel=2;
    medStomatchhealTimeSec=2000;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\injector_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\injector");
    INJECTOR_ANIM_EVENTS();
};