class GP5GasMask: Clothing
{
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\masks\gp5gasmask_white_ca.paa",
        "SyberiaScripts\data\masks\gp5gasmask_white_ca.paa",
        "SyberiaScripts\data\masks\gp5gasmask_white_ca.paa",
        
        "\dz\characters\masks\data\GP5GasMask_white_co.paa",
        "\dz\characters\masks\data\GP5GasMask_white_co.paa",
        "\dz\characters\masks\data\GP5GasMask_white_co.paa"
    };
    attachments[]=
    {
        "GasMaskFilter"
    };
};

class AirborneMask: Clothing
{
    hiddenSelectionsTextures[]=
    {
        "\dz\characters\masks\data\airborne_mask_co.paa",
        "\dz\characters\masks\data\airborne_mask_co.paa",
        "\dz\characters\masks\data\airborne_mask_co.paa",
        "",
        "\dz\characters\masks\data\airborne_mask_glass_ca.paa",
        "\dz\characters\masks\data\gp5gasmask_white_co.paa",
    };
    attachments[]=
    {
        "GasMaskFilter"
    };
};

class GP5GasMask_Filter: Inventory_Base
{
    displayName="#syb_gp5_filter_name";
    descriptionShort="#syb_gp5_filter_desc";
    stackedUnit="percentage";
    quantityBar=1;
    varQuantityInit=100;
    varQuantityMin=0;
    varQuantityMax=100;
};