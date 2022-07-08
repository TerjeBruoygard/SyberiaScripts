class PlateCarrierVest: Clothing {
    bulletProofProtection = 0.4;
};

class PressVest_ColorBase: Clothing
{
    bulletProofProtection = 0.26;
};

class PoliceVest: Clothing
{
    bulletProofProtection = 0.1;
};

class TraderVest: PressVest_ColorBase
{
    visibilityModifier=0.7;
    hiddenSelectionsTextures[]=
    {
        "SyberiaScripts\data\vests\pressvest_trader_co.paa",
        "SyberiaScripts\data\vests\pressvest_trader_co.paa",
        "SyberiaScripts\data\vests\pressvest_trader_co.paa"
    };
};
