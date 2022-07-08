#define AMPOUL_ANIM_EVENT()\
class AnimEvents\
{\
    class SoundWeapon\
    {\
        class pickUpItem\
        {\
            soundSet="injectionvial_pickup_SoundSet";\
            id=797;\
        };\
    };\
}

class SyberiaMedicineAmpoule : Inventory_Base
{
    descriptionShort="#syb_ampoule_desc";
    itemSize[]={2,2};
    weight=100;
    quantityBar=1;
    varQuantityInit=150;
    varQuantityMin=0;
    varQuantityMax=150;
    varQuantityDestroyOnMin=1;
    absorbency=0;
    hiddenSelections[]=
    {
        "zbytek"
    };
};

class AmpouleAlcohol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_alcohol_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medHemologicShock=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpouleNovocain : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_novocaine_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=1500; // 25 minutes
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};