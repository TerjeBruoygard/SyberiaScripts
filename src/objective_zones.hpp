class SyberiaObjectiveZone : HouseNoDestruct
{
    scope=0;
    radius = 0.0;
    height = -1.0;
    enterMessage = "";
    leaveMessage = "";
    leaveTime = 0.0;
    godMode = 0;
    inverseDammage = 0;
    blockBuildingMode = 0;
    blockInteractionWithPlayers = 0;
    radiation = 0.0;
    psi = 0.0;
    gas = 0.0;
    
    class DamageSystem
    {
        class GlobalHealth
        {
            class Health
            {
                hitpoints=1000;
            };
        };
        class GlobalArmor
        {
            class Projectile
            {
                class Health
                {
                    damage=0;
                };
                class Blood
                {
                    damage=0;
                };
                class Shock
                {
                    damage=0;
                };
            };
            class Melee
            {
                class Health
                {
                    damage=0;
                };
                class Blood
                {
                    damage=0;
                };
                class Shock
                {
                    damage=0;
                };
            };
            class FragGrenade
            {
                class Health
                {
                    damage=0;
                };
                class Blood
                {
                    damage=0;
                };
                class Shock
                {
                    damage=0;
                };
            };
        };
    };
};

class SyberiaObjectiveZone_Radiation100 : SyberiaObjectiveZone
{
    scope=1;
    radius=100;
    radiation=1.0;
};

class SyberiaObjectiveZone_PSI100 : SyberiaObjectiveZone
{
    scope=1;
    radius=100;
    psi=1.0;
};

class SyberiaObjectiveZone_Toxic100 : SyberiaObjectiveZone
{
    scope=1;
    radius=100;
    gas=1.0;
};