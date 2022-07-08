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

class AmpouleIrineks : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_irineks_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=600; // 25 minutes
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpouleNimesulid : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_nimesulid_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=1600; // 25 minutes
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_yellow_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpouleKetoprofen : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_ketoprofen_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=1800;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpoulePropofol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_propofol_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=800;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_yellow_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpouleTiopental : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_tiopental_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=1100;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_red_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpouleKetamin : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_ketamin_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=1400;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpouleMeksidol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_meksidol_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medConcussionHeal=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_green_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpoulePeklitakcel : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_peklitakcel_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medHematomaHeal=1;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpouleNonacogAlpha : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_nonacog_alpha_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=600;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};

class AmpoulePerftoran : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_perftoran_name";
    model="SyberiaScripts\data\medical\ampoule.p3d";
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=200;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\medical\ampoule_blue_co.paa"
    };
    ITEM_DAMAGE_SYSTEM(50, "SyberiaScripts\data\medical\ampoule");
    AMPOUL_ANIM_EVENT();
};