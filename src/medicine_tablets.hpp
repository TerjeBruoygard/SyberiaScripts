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
    medPainkillerTimeSec=900; // 15 minutes
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\tablets_green_co.paa"
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