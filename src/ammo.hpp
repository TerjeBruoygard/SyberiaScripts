class MeleeDamage; 

class MeleeFist: MeleeDamage
{
    class DamageApplied
    {
        type="Melee";
        class Health
        {
            damage=2;
            armorDamage=0.1;
        };
        class Blood
        {
            damage=0;
        };
        class Shock
        {
            damage=5;
        };
    };
};

class MeleeFist_Heavy: MeleeFist
{
    hitAnimation=1;
    class DamageApplied
    {
        type="Melee";
        class Health
        {
            damage=5;
            armorDamage=0.1;
        };
        class Blood
        {
            damage=0;
        };
        class Shock
        {
            damage=15;
        };
    };
};

class MeleeBrassKnuckles: MeleeDamage
{
    class DamageApplied
    {
        type="Melee";
        class Health
        {
            damage=5;
        };
        class Blood
        {
            damage=0;
        };
        class Shock
        {
            damage=15;
        };
    };
};

class MeleeBrassKnuckles_Heavy: MeleeBrassKnuckles
{
    class DamageApplied
    {
        type="Melee";
        class Health
        {
            damage=10;
        };
        class Blood
        {
            damage=0;
        };
        class Shock
        {
            damage=20;
        };
    };
};
