#define AMPOUL_ANIM_EVENT class AnimEvents\
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
    itemSize[]={1,2};
    weight=100;
    quantityBar=1;
    varQuantityInit=4;
    varQuantityMin=0;
    varQuantityMax=4;
    varQuantityDestroyOnMin=0;
    stackedUnit="percentage";
    absorbency=0;
    overdosedIncrement=0.25;
    medicalItem=1;
    hiddenSelections[]=
    {
        "zbytek"
    };
};

class AmpouleAlcohol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_alcohol_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medHemologicShock=1;
    overdosedIncrement=4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleHihlofos : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_dihlofos_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medHemologicShock=1;
    overdosedIncrement=4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleCypermetrin : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_cypermetrin_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medHemologicShock=1;
    overdosedIncrement=4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleDiazinon : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_diazinon_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medHemologicShock=1;
    overdosedIncrement=4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleArsenic : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_arsenic_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medHemologicShock=1;
    overdosedIncrement=4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleNovocain : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_novocaine_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=1500; // 25 minutes
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleIrineks : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_irineks_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=600; // 25 minutes
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleNimesulid : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_nimesulid_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=1600; // 25 minutes
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleKetoprofen : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_ketoprofen_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=1800;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpoulePropofol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_propofol_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=800;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleTiopental : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_tiopental_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=600;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleKetamin : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_ketamin_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=300;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpoulePropanidid : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_propanidid_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=400;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleGexobarbital : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_gexobarbital_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=2;
    medPainkillerTimeSec=800;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleSodiumOxybutirate : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_sodium_oxybutirate_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medPainkillerLevel=3;
    medPainkillerTimeSec=1200;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};





class AmpouleMetoclopramid : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_metoclopramid_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medStomatchhealLevel=2;
    medStomatchhealTimeSec=600;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleZerukal : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_zerukal_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medStomatchhealLevel=2;
    medStomatchhealTimeSec=800;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleKetorol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_ketorol_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medStomatchhealLevel=2;
    medStomatchhealTimeSec=1000;
    medPainkillerLevel=1;
    medPainkillerTimeSec=1200;
    medAntibioticLevel=2;
    medAntibioticsTimeSec=1200;
    medAntibioticsStrength=2.0;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleDiklofenak : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_diklofenak_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=2;
    medAntibioticsTimeSec=1100;
    medAntibioticsStrength=2.5;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleHeptral : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_heptral_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medStomatchhealLevel=2;
    medStomatchhealTimeSec=1200;
    overdosedIncrement=0.3;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};




class AmpouleCylaspen : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_cylaspen_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=2;
    medAntibioticsTimeSec=600;
    medAntibioticsStrength=2.0;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleGrimipenem : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_grimipenem_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=2;
    medAntibioticsTimeSec=500;
    medAntibioticsStrength=1.8;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleZeftriaxon : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_zeftriaxon_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=2;
    medAntibioticsTimeSec=600;
    medAntibioticsStrength=1.8;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleErytromicyn : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_erytromicyn_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=2;
    medAntibioticsTimeSec=1000;
    medAntibioticsStrength=2.0;
    overdosedIncrement=0.45;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleFlemoclav : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_flemoclav_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=3;
    medAntibioticsTimeSec=1400;
    medAntibioticsStrength=2.5;
    overdosedIncrement=0.45;
    medRemoveSepsis=1;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleOcsacylin : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_ocsacylin_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=3;
    medAntibioticsTimeSec=300;
    medAntibioticsStrength=2.7;
    overdosedIncrement=0.5;
    medRemoveSepsis=1;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleImipenem : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_imipenem_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=3;
    medAntibioticsTimeSec=1200;
    medAntibioticsStrength=3.0;
    overdosedIncrement=0.55;
    medRemoveSepsis=1;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleAmoksivan : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_amoksivan_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntibioticLevel=3;
    medAntibioticsTimeSec=1400;
    medAntibioticsStrength=3.0;
    overdosedIncrement=0.6;
    medRemoveSepsis=1;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};



class AmpouleZivirol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_zvirus_antidot_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medRemoveZVirus=1;
    overdosedIncrement=1.8;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleMeksidol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_meksidol_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medConcussionHeal=1;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleActovegin : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_actovegin_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medConcussionHeal=1;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleNeiroks : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_neiroks_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medConcussionHeal=1;
    overdosedIncrement=0.5;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};



class AmpoulePeklitakcel : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_peklitakcel_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medHematomaHeal=1;
    medHematomaHealTimeSec=900;
    overdosedIncrement=0.2;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleNonacogAlpha : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_nonacog_alpha_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=600;
    overdosedIncrement=0.3;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleAminokaprolSulfat : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_aminokapsulfat_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=600;
    overdosedIncrement=0.3;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleVikasol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_vikasol_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=800;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleEtamzilat : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_etamzilat_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=1400;
    overdosedIncrement=0.5;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpoulePerftoran : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_perftoran_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=300;
    overdosedIncrement=0.3;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleMaltofer : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_maltofer_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=600;
    overdosedIncrement=0.3;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleErytropoenin : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_erytropoenin_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medBloodHematopoiesis=1;
    medBloodHematopoiesisTimeSec=900;
    medBloodHemostatic=1;
    medBloodHemostaticTimeSec=900;
    overdosedIncrement=0.5;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};


class AmpouleAdrenalin05 : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_adrenalin05_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAdrenalinLevel=1;
    medAdrenalinTimeSec=900;
    overdosedIncrement=0.2;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleAdrenalin10 : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_adrenalin10_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAdrenalinLevel=2;
    medAdrenalinTimeSec=600;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleAdrenalin30 : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_adrenalin30_name";
    model="\dz\gear\medical\injectionvial.p3d";
    medAdrenalinLevel=3;
    medAdrenalinTimeSec=300;
    overdosedIncrement=0.6;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpoulePentacin : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_pentacin";
    model="\dz\gear\medical\injectionvial.p3d";
    medRadioprotectionLevel=2;
    medRadioprotectionTimer=300;
    overdosedIncrement=0.6;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleCarboxyme : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_carboxyme";
    model="\dz\gear\medical\injectionvial.p3d";
    medRadioprotectionLevel=2;
    medRadioprotectionTimer=300;
    overdosedIncrement=0.6;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleMetralindol : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_metralyndol";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntidepresantLevel=2;
    medAntidepresantTimer=300;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_green_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleActaparoxetine : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_aktaparoksetyn";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntidepresantLevel=2;
    medAntidepresantTimer=400;
    overdosedIncrement=0.4;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};

class AmpouleAmitriptyline : SyberiaMedicineAmpoule
{
    scope=2;
    displayName="#syb_amitriptilin";
    model="\dz\gear\medical\injectionvial.p3d";
    medAntidepresantLevel=2;
    medAntidepresantTimer=600;
    overdosedIncrement=0.5;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\ampoule_yellow_co.paa" };
    ITEM_DAMAGE_SYSTEM(50, "DZ\gear\medical\data\InjectionVial.rvmat", "DZ\gear\medical\data\InjectionVial_damage.rvmat", "DZ\gear\medical\data\InjectionVial_destruct.rvmat");
    AMPOUL_ANIM_EVENT;
};