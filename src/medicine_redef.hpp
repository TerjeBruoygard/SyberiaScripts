class PainkillerTablets : Edible_Base
{
    scope=0;
};

class InjectionVial: Inventory_Base
{
    scope=0;
};

class Epinephrine: Inventory_Base
{
    scope=0;
};

class Syringe: Epinephrine
{
    scope=0;
};

class ClearSyringe: Inventory_Base
{
    scope=0;
};

class BloodSyringe: Inventory_Base
{
    scope=0;
};

class Morphine: Inventory_Base
{
    scope=0;
};

class CharcoalTablets: Edible_Base
{
    scope=0;
};

class TetracyclineAntibiotics: Edible_Base
{
    scope=0;
};

class BandageDressing: Inventory_Base
{
    medBloodStop=2;
    medicalItem=1;
};

class Bandana_ColorBase: Clothing
{
    medBloodStop=2;
};

class Rag: Inventory_Base
{
    medBloodStop=2;
    canBeSplit = 1;
    varQuantityInit = 1.0;
    varQuantityMin = 0.0;
    varQuantityMax = 10.0;
    varQuantityDestroyOnMin = 1;
};

class SurgicalGloves_ColorBase: Clothing
{
    medGloves=1;
    varCleannessInit=1;
    medicalItem=1;
};