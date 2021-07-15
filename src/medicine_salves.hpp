class SalveBase : Inventory_Base
{
    descriptionShort="#syb_salve_desc";
    rotationFlags=17;
    itemSize[]={1,2};
    weight=120;
    quantityBar=1;
    varQuantityInit=5;
    varQuantityMin=0;
    varQuantityMax=5;
    varQuantityDestroyOnMin=1;
    absorbency=0;
    overdosedIncrement=0.01;
    medicalItem=1;
};

class SalveKapsikam : SalveBase
{
    scope=2;
    displayName="#syb_kapsikam_name";
    model="\dz\gear\medical\VitaminBottle.p3d";
    medHematomaHeal=1;
    medHematomaHealTimeSec=300;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\salve_blue_co.paa" };
    ITEM_DAMAGE_SYSTEM(150, "DZ\gear\medical\data\vitamin_bottle.rvmat", "DZ\gear\medical\data\vitamin_bottle_damage.rvmat", "DZ\gear\medical\data\vitamin_bottle_destruct.rvmat");
};

class SalveFinalgon : SalveBase
{
    scope=2;
    displayName="#syb_finalgon_name";
    model="\dz\gear\medical\VitaminBottle.p3d";
    medHematomaHeal=1;
    medHematomaHealTimeSec=600;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\salve_red_co.paa" };
    ITEM_DAMAGE_SYSTEM(150, "DZ\gear\medical\data\vitamin_bottle.rvmat", "DZ\gear\medical\data\vitamin_bottle_damage.rvmat", "DZ\gear\medical\data\vitamin_bottle_destruct.rvmat");
};

class SalveViprosal : SalveBase
{
    scope=2;
    displayName="#syb_viprosal_name";
    model="\dz\gear\medical\VitaminBottle.p3d";
    medHematomaHeal=1;
    medHematomaHealTimeSec=400;
    hiddenSelections[] = {"zbytek"};
    hiddenSelectionsTextures[] = { "SyberiaScripts\data\medical\salve_orange_co.paa" };
    ITEM_DAMAGE_SYSTEM(150, "DZ\gear\medical\data\vitamin_bottle.rvmat", "DZ\gear\medical\data\vitamin_bottle_damage.rvmat", "DZ\gear\medical\data\vitamin_bottle_destruct.rvmat");
};