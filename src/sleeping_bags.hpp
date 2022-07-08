class SleepingBag_BaseColor : Inventory_Base {
    scope=0;
    displayName="#syb_sbag_packed_name";
    descriptionShort="#syb_sbag_packed_desc";
    model="SyberiaScripts\data\sleeping\sbag_packed.p3d";
    weight=500;
    itemSize[]={2,3};
    repairableWithKits[]={5,6};
    rotationFlags=17;
    repairCosts[]={30,25};
    absorbency=0.3;
    itemBehaviour=2;
    hologramName="SleepingBagPlacing";
    hiddenSelections[]=
    {
        "body"
    };
};

class SleepingBagPlaced_BaseColor : BaseBuildingBase {
    displayName="#syb_sbag_packed_name";
    descriptionShort="#syb_sbag_packed_desc";
    model="SyberiaScripts\data\sleeping\sbag_placed.p3d";
    weight=500;
    rotationFlags=2;
    bounding="BSphere";
    overrideDrawArea="3.0";
    forceFarBubble="true";
    handheld="false";
    slopeTolerance=0.15;
    yawPitchRollLimit[]={12,12,12};
    hiddenSelections[]=
    {
        "body"
    };
    placedSound="SleepingBagPlaced_SoundEmitter";
    foldingSound="SleepingBagPlaced_SoundEmitter";
    sleepingSound="SleepingBagPlaced_SoundEmitter";
    physLayer="item_large";
    carveNavmesh=0;
    varTemperatureInit=25;
    varTemperatureMin=25;
    varTemperatureMax=25;
};

class SleepingBagPlacing : BaseBuildingBase {
    scope=1;
    hologramMaterial="tent_medium";
    hologramMaterialPath="dz\gear\camping\data";
    alignHologramToTerain=1;
    model="SyberiaScripts\data\sleeping\sbag_placed.p3d";
    hiddenSelections[]=
    {
        "body"
    };
};

// BLUE
class SleepingBag_Blue : SleepingBag_BaseColor {
    scope=2;
    placedName="SleepingBagPlaced_Blue";
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\sleeping\sbag_packed_blue.paa"
    };
    ITEM_DAMAGE_SYSTEM(300, "SyberiaScripts\data\sleeping\sbag_packed.rvmat", "SyberiaScripts\data\sleeping\sbag_packed_damage.rvmat", "SyberiaScripts\data\sleeping\sbag_packed_destruct.rvmat");
};

class SleepingBagPlaced_Blue : SleepingBagPlaced_BaseColor {
    scope=2;
    packedName="SleepingBag_Blue";
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\sleeping\sbag_placed_blue.paa"
    };
    ITEM_DAMAGE_SYSTEM(300, "SyberiaScripts\data\sleeping\sbag_placed.rvmat", "SyberiaScripts\data\sleeping\sbag_placed_damage.rvmat", "SyberiaScripts\data\sleeping\sbag_placed_destruct.rvmat");
};

// WOODLAND
class SleepingBag_Woodland : SleepingBag_BaseColor {
    scope=2;
    placedName="SleepingBagPlaced_Woodland";
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\sleeping\sbag_packed_woodland.paa"
    };
    ITEM_DAMAGE_SYSTEM(200, "SyberiaScripts\data\sleeping\sbag_packed.rvmat", "SyberiaScripts\data\sleeping\sbag_packed_damage.rvmat", "SyberiaScripts\data\sleeping\sbag_packed_destruct.rvmat");
};

class SleepingBagPlaced_Woodland : SleepingBagPlaced_BaseColor {
    scope=2;
    packedName="SleepingBag_Woodland";
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\sleeping\sbag_placed_woodland.paa"
    };
    ITEM_DAMAGE_SYSTEM(200, "SyberiaScripts\data\sleeping\sbag_placed.rvmat", "SyberiaScripts\data\sleeping\sbag_placed_damage.rvmat", "SyberiaScripts\data\sleeping\sbag_placed_destruct.rvmat");
};