#define TABLETS_ANIM_EVENTS class AnimEvents\
{\
    class SoundWeapon\
    {\
        class Tablets_open\
        {\
            soundSet="Tablets_open_SoundSet";\
            id=201;\
        };\
        class Tablets_catch\
        {\
            soundSet="Tablets_catch_SoundSet";\
            id=202;\
        };\
        class Tablets_close\
        {\
            soundSet="Tablets_close_SoundSet";\
            id=203;\
        };\
        class pickup\
        {\
            soundSet="purificationtablets_pickup_SoundSet";\
            id=797;\
        };\
        class drop\
        {\
            soundset="purificationtablets_drop_SoundSet";\
            id=898;\
        };\
    };\
}

class TabletsBase : Edible_Base {
    descriptionShort="#syb_tablets_common_desc";
    rotationFlags=17;
    itemSize[]={1,2};
    varQuantityInit=10;
    varQuantityMin=0;
    varQuantityMax=10;
    varQuantityDestroyOnMin=1;
    weight=20;
    stackedUnit="pills";
    canBeSplit=1;
    quantityBar=0;
    absorbency=0;
    overdosedIncrement=0.1;
    medicalItem=1;
    hiddenSelections[]=
    {
        "pills"
    };
};

class TabletsAnalgin : TabletsBase
{
    scope=2;
    displayName="#syb_analgin_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=300;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsNaiz : TabletsBase
{
    scope=2;
    displayName="#syb_naiz_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=1400;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAertal : TabletsBase
{
    scope=2;
    displayName="#syb_aertal_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=1300;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsNimesil : TabletsBase
{
    scope=2;
    displayName="#syb_nimesil_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=1300;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsPentalgin : TabletsBase
{
    scope=2;
    displayName="#syb_pentalgin_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=800;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsMovalis : TabletsBase
{
    scope=2;
    displayName="#syb_movalis_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=800;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_sepia_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};


class TabletsCytramon : TabletsBase
{
    scope=2;
    displayName="#syb_cytramon_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=400;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsParacetamol : TabletsBase
{
    scope=2;
    displayName="#syb_paracetamol_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=1000;
    medAntibioticLevel=1;
    medAntibioticsTimeSec=200;
    medAntibioticsStrength = 0.5;
    overdosedIncrement=0.15;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsIbuprofen : TabletsBase
{
    scope=2;
    displayName="#syb_ibuprofen_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=800;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=400;
    medAntibioticsStrength = 0.8;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsNurofen : TabletsBase
{
    scope=2;
    displayName="#syb_nurofen_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=800;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=600;
    medAntibioticsStrength = 1.0;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsTetracycline : TabletsBase
{
    scope=2;
    displayName="#syb_tetracycline_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=900;
    medAntibioticsStrength = 1.5;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAmoksiklav : TabletsBase
{
    scope=2;
    displayName="#syb_amoksiklav_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=1200;
    medAntibioticsStrength = 1.5;
    overdosedIncrement=0.25;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_sepia_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAmpicylin : TabletsBase
{
    scope=2;
    displayName="#syb_ampicilin_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=900;
    medAntibioticsStrength = 1.3;
    overdosedIncrement=0.23;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsPiperacylin : TabletsBase
{
    scope=2;
    displayName="#syb_piperacyclin_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=1100;
    medAntibioticsStrength = 1.4;
    overdosedIncrement=0.25;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsTrihopol : TabletsBase
{
    scope=2;
    displayName="#syb_trihopol_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=1;
    medAntibioticsTimeSec=400;
    medAntibioticsStrength = 0.8;
    overdosedIncrement=0.15;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsCyprolet : TabletsBase
{
    scope=2;
    displayName="#syb_cyprolet_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=1;
    medAntibioticsTimeSec=500;
    medAntibioticsStrength = 0.8;
    overdosedIncrement=0.15;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAmoksivan : TabletsBase
{
    scope=2;
    displayName="#syb_amoksivan_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=600;
    medAntibioticsStrength = 1.2;
    overdosedIncrement=0.28;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_sepia_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAmibaktam : TabletsBase
{
    scope=2;
    displayName="#syb_amibaktam_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=1;
    medAntibioticsTimeSec=300;
    medAntibioticsStrength = 0.5;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsCharcoal : TabletsBase
{
    scope=2;
    displayName="#syb_charcoal_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=60;
    overdosedIncrement=0.0;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_black_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsMezimForte : TabletsBase
{
    scope=2;
    displayName="#syb_mezim_forte_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=120;
    overdosedIncrement=0.05;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsZerukal : TabletsBase
{
    scope=2;
    displayName="#syb_zerukal_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=180;
    overdosedIncrement=0.05;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsNifuroksazid : TabletsBase
{
    scope=2;
    displayName="#syb_nifuroksazid_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=300;
    overdosedIncrement=0.05;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsPolisorb : TabletsBase
{
    scope=2;
    displayName="#syb_polisorb_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=300;
    overdosedIncrement=0.05;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsKarbopekt : TabletsBase
{
    scope=2;
    displayName="#syb_karbopekt_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=300;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_sepia_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsEnterofuril : TabletsBase
{
    scope=2;
    displayName="#syb_enterofuril_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=250;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsErsefuril : TabletsBase
{
    scope=2;
    displayName="#syb_ersefuril_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=400;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsSalofalk : TabletsBase
{
    scope=2;
    displayName="#syb_salofalk_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=250;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsFtalazol : TabletsBase
{
    scope=2;
    displayName="#syb_ftalazol_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=250;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsMesalazin : TabletsBase
{
    scope=2;
    displayName="#syb_mesalazin_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=380;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsNoopept : TabletsBase
{
    scope=2;
    displayName="#syb_noopept_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=60;
    medConcussionHeal=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsVikasol : TabletsBase
{
    scope=2;
    displayName="#syb_vikasol_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=180;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsDycinon : TabletsBase
{
    scope=2;
    displayName="#syb_dycinon_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=240;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsIrovit : TabletsBase
{
    scope=2;
    displayName="#syb_irovit_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=120;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsTardiferon : TabletsBase
{
    scope=2;
    displayName="#syb_tardiferon_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=180;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsHeferol : TabletsBase
{
    scope=2;
    displayName="#syb_heferol_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=220;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_sepia_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsSorbiferDurulis : TabletsBase
{
    scope=2;
    displayName="#syb_surbifer_durulis_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=300;
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=300;
    overdosedIncrement=0.15;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsPotassiumIodide : TabletsBase
{
    scope=2;
    displayName="#syb_potassium_iodide";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medRadioprotectionLevel=1;
    medRadioprotectionTimer=60;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsPotassiumHexacyanoferrate : TabletsBase
{
    scope=2;
    displayName="#syb_potassium_hexacyanoferrate";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medRadioprotectionLevel=1;
    medRadioprotectionTimer=90;
    overdosedIncrement=0.3;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_black_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsCystamine : TabletsBase
{
    scope=2;
    displayName="#syb_cystamine";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medRadioprotectionLevel=1;
    medRadioprotectionTimer=120;
    overdosedIncrement=0.3;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsB190 : TabletsBase
{
    scope=2;
    displayName="#syb_b190";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medRadioprotectionLevel=1;
    medRadioprotectionTimer=140;
    overdosedIncrement=0.3;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsMexamine : TabletsBase
{
    scope=2;
    displayName="#syb_mexamine";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medRadioprotectionLevel=2;
    medRadioprotectionTimer=30;
    overdosedIncrement=0.6;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAgteminol : TabletsBase
{
    scope=2;
    displayName="#syb_agteminol";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntidepresantLevel=1;
    medAntidepresantTimer=60;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAdepress : TabletsBase
{
    scope=2;
    displayName="#syb_adepress";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntidepresantLevel=1;
    medAntidepresantTimer=70;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_sepia_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsActaparoxetine : TabletsBase
{
    scope=2;
    displayName="#syb_aktaparoksetyn";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntidepresantLevel=1;
    medAntidepresantTimer=40;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsAmitriptyline : TabletsBase
{
    scope=2;
    displayName="#syb_amitriptilin";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntidepresantLevel=1;
    medAntidepresantTimer=100;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};

class TabletsVenlafaxine : TabletsBase
{
    scope=2;
    displayName="#syb_venlafaxyn";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntidepresantLevel=1;
    medAntidepresantTimer=90;
    overdosedIncrement=0.2;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base.rvmat", "SyberiaScripts\data\medical\tablets_base_damage.rvmat", "SyberiaScripts\data\medical\tablets_base_destruct.rvmat");
    TABLETS_ANIM_EVENTS;
};