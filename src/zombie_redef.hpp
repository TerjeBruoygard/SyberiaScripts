class DayZInfected;
class ZombieBase: DayZInfected
{
    class DamageSystem
    {
        class GlobalHealth
        {
            class Health
            {
                hitpoints=150;
                healthLevels[]=
                {
                    
                    {
                        1,
                        {}
                    },
                    
                    {
                        0.7,
                        {}
                    },
                    
                    {
                        0.5,
                        {}
                    },
                    
                    {
                        0.3,
                        {}
                    },
                    
                    {
                        0,
                        {}
                    }
                };
            };
        };
        class DamageZones
        {
            class Head
            {
                class Health
                {
                    hitpoints=20;
                    transferToGlobalCoef=1;
                };
                class ArmorType
                {
                    class Projectile
                    {
                        class Health
                        {
                            damage=1.5;
                        };
                        class Shock
                        {
                            damage=1.5;
                        };
                    };
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=3;
                        };
                    };
                };
                componentNames[]=
                {
                    "Head",
                    "Neck"
                };
                fatalInjuryCoef=0.1;
                inventorySlots[]=
                {
                    "Headgear",
                    "Mask"
                };
            };
            class Torso
            {
                class Health
                {
                    hitpoints=150;
                    transferToGlobalCoef=1;
                };
                class ArmorType
                {
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=2;
                        };
                    };
                };
                componentNames[]=
                {
                    "Spine1",
                    "Spine3"
                };
                fatalInjuryCoef=-1;
                inventorySlots[]=
                {
                    "Vest",
                    "Body",
                    "Back"
                };
                inventorySlotsCoefs[]={1,1,0.5};
            };
            class LeftArm
            {
                class Health
                {
                    hitpoints=200;
                    transferToGlobalCoef=1;
                };
                class ArmorType
                {
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=2;
                        };
                    };
                };
                componentNames[]=
                {
                    "LeftArm",
                    "LeftForeArm"
                };
                fatalInjuryCoef=-1;
            };
            class RightArm
            {
                class Health
                {
                    hitpoints=200;
                    transferToGlobalCoef=1;
                };
                class ArmorType
                {
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=2;
                        };
                    };
                };
                componentNames[]=
                {
                    "RightArm",
                    "RightForeArm"
                };
                fatalInjuryCoef=-1;
            };
            class LeftLeg
            {
                class Health
                {
                    hitpoints=50;
                    transferToGlobalCoef=0.33000001;
                };
                class ArmorType
                {
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=2;
                        };
                    };
                };
                componentNames[]=
                {
                    "LeftLeg",
                    "LeftUpLeg"
                };
                fatalInjuryCoef=-1;
                inventorySlots[]=
                {
                    "Legs"
                };
            };
            class RightLeg
            {
                class Health
                {
                    hitpoints=50;
                    transferToGlobalCoef=0.33000001;
                };
                class ArmorType
                {
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=2;
                        };
                    };
                };
                componentNames[]=
                {
                    "RightLeg",
                    "RightUpLeg"
                };
                fatalInjuryCoef=-1;
                inventorySlots[]=
                {
                    "Legs"
                };
            };
            class LeftFoot
            {
                class Health
                {
                    hitpoints=50;
                    transferToGlobalCoef=0.1;
                };
                class ArmorType
                {
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=2;
                        };
                    };
                };
                transferToZonesNames[]=
                {
                    "LeftLeg"
                };
                transferToZonesCoefs[]={0.1};
                componentNames[]=
                {
                    "LeftFoot"
                };
                fatalInjuryCoef=-1;
                inventorySlots[]=
                {
                    "Feet"
                };
            };
            class RightFoot
            {
                class Health
                {
                    hitpoints=50;
                    transferToGlobalCoef=0.1;
                };
                class ArmorType
                {
                    class FragGrenade
                    {
                        class Health
                        {
                            damage=2;
                        };
                    };
                };
                transferToZonesNames[]=
                {
                    "RightLeg"
                };
                transferToZonesCoefs[]={0.1};
                componentNames[]=
                {
                    "RightFoot"
                };
                fatalInjuryCoef=-1;
                inventorySlots[]=
                {
                    "Feet"
                };
            };
        };
    };
};