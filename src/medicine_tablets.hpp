#define TABLETS_ANIM_EVENTS()\
class AnimEvents\
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
    rotationFlags=0;
    itemSize[]={1,2};
    varQuantityInit=10;
    varQuantityMin=0;
    varQuantityMax=10;
    varQuantityDestroyOnMin=1;
    weight=20;
    stackedUnit="pills";
    quantityBar=0;
    absorbency=0;
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
    medPainkillerTimeSec=700;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
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
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
};

class TabletsCytramon : TabletsBase
{
    scope=2;
    displayName="#syb_cytramon_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=900;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
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
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
};

class TabletsIbuprofen : TabletsBase
{
    scope=2;
    displayName="#syb_ibuprofen_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medPainkillerLevel=1;
    medPainkillerTimeSec=600;
    medAntibioticLevel=1;
    medAntibioticsTimeSec=400;
    medAntibioticsStrength = 0.8;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_white_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
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
    medAntibioticLevel=1;
    medAntibioticsTimeSec=350;
    medAntibioticsStrength = 0.7;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
};

class TabletsTetracycline : TabletsBase
{
    scope=2;
    displayName="#syb_tetracycline_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medAntibioticLevel=1;
    medAntibioticsTimeSec=900;
    medAntibioticsStrength = 1.0;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_brown_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
};

class TabletsCharcoal : TabletsBase
{
    scope=2;
    displayName="#syb_charcoal_name";
    model="SyberiaScripts\data\medical\tablets.p3d";
    varQuantityInit=10;
    varQuantityMax=10;
    medStomatchhealLevel=1;
    medStomatchhealTimeSec=900;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_black_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\tablets_base");
    TABLETS_ANIM_EVENTS();
};