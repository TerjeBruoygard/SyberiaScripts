#define INJECTOR_ANIM_EVENTS class AnimEvents\
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
    overdosedIncrement=0.4;
    medicalItem=1;
};

class InjectorPromedol : InjectorBase
{
    scope=2;
    displayName="#syb_promedol_name";
    model="\dz\gear\medical\morphine.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=1800;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorZivirol : InjectorBase
{
    scope=2;
    displayName="#syb_zvirus_antidot_name";
    model="\dz\gear\medical\morphine.p3d";
    medRemoveZVirus=1;
    overdosedIncrement=1.8;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorTopoizomeraza : InjectorBase
{
    scope=2;
    displayName="#syb_topoizomeraza_name";
    model="\dz\gear\medical\morphine.p3d";
    medRemoveSepsis=1;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorErytropoenin : InjectorBase
{
    scope=2;
    displayName="#syb_erytropoenin_name";
    model="\dz\gear\medical\morphine.p3d";
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=900;
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=900;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorNeiroks : InjectorBase
{
    scope=2;
    displayName="#syb_neiroks_name";
    model="\dz\gear\medical\morphine.p3d";
    medConcussionHeal=1;
    overdosedIncrement=0.5;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorAmoksivan : InjectorBase
{
    scope=2;
    displayName="#syb_amoksivan_name";
    model="\dz\gear\medical\morphine.p3d";
    medAntibioticLevel=3;
    medAntibioticsTimeSec=1800;
    medAntibioticsStrength=5.0;
    medRemoveSepsis=1;
    overdosedIncrement=0.6;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorKetorol : InjectorBase
{
    scope=2;
    displayName="#syb_ketorol_name";
    model="\dz\gear\medical\morphine.p3d";
    medStomatchhealLevel=2;
    medStomatchhealTimeSec=1600;
    medPainkillerLevel=1;
    medPainkillerTimeSec=1800;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=1800;
    medAntibioticsStrength=2.0;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorEpipen : InjectorBase
{
    scope=2;
    displayName="#syb_epipen_name";
    model="\dz\gear\medical\morphine.p3d";
    medAdrenalinLevel=3;
    medAdrenalinTimeSec=300;
    overdosedIncrement=0.5;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorNovichek : InjectorBase
{
    scope=2;
    displayName="#syb_novichek_name";
    model="\dz\gear\medical\morphine.p3d";
    medHemologicShock=1;
    overdosedIncrement=5;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};

class InjectorRadioprotector : InjectorBase
{
    scope=2;
    displayName="#syb_radioprotector";
    model="\dz\gear\medical\morphine.p3d";
    medRadioprotectionLevel=2;
    medRadioprotectionTimer=350;
    overdosedIncrement=0.7;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\injector_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(100, "DZ\gear\medical\data\Morphine.rvmat", "DZ\gear\medical\data\Morphine_damage.rvmat", "DZ\gear\medical\data\Morphine_destruct.rvmat");
    INJECTOR_ANIM_EVENTS;
};