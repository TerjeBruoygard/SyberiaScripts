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

class AntiChemInjector: Inventory_Base
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

class PurificationTablets: Edible_Base
{
    medicalItem=1;
};

class IodineTincture: Edible_Base
{
    medicalItem=1;
};

class DisinfectantAlcohol: Edible_Base
{
    medicalItem=1;
};

class DisinfectantSpray: Edible_Base
{
    medicalItem=1;
};

class SalineBag: Inventory_Base
{
    medicalItem=1;
};

class StartKitIV: Inventory_Base
{
    medicalItem=1;
};

class SalineBagIV: Inventory_Base
{
    medicalItem=1;
};

class BloodBagEmpty: Inventory_Base
{
    medicalItem=1;
};

class BloodBagFull: Inventory_Base
{
    medicalItem=1;
};

class BloodBagIV: Inventory_Base
{
    medicalItem=1;
};

class BloodTestKit: Inventory_Base
{
    medicalItem=1;
};