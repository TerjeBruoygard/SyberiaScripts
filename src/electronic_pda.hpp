class ItemPDA: Inventory_Base
{
    scope = 2;
    title = "#pda_item_name";
    displayName = "#pda_item_name";
    descriptionShort = "#pda_item_desc";
    model="SyberiaScripts\data\pda\pda.p3d";
    hiddenSelections[]=
    {
        "body"
    };
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\pda\pda_co.paa",
        "SyberiaScripts\data\pda\pda_on_co.paa"
    };
    animClass="ItemPDA";
    itemSize[]={2,2};
    weight=250;
    oldpower=0;
    attachments[]=
    {
        "BatteryD"
    };
    class EnergyManager
    {
        hasIcon=1;
        autoSwitchOff=1;
        energyUsagePerSecond=0.0001;
        plugType=1;
        attachmentAction=1;
        wetnessExposure=0.1;
    };
    ITEM_DAMAGE_SYSTEM(250, "SyberiaScripts\data\pda\pda.rvmat", "SyberiaScripts\data\pda\pda_damage.rvmat", "SyberiaScripts\data\pda\pda_destruct.rvmat");
};