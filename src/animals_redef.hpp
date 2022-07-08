class DZ_LightAI;
class AnimalBase: DZ_LightAI
{
    storageCategory=3;
    knifeDamageModifier=1;
    class Cargo
    {
        itemsCargoSize[]={10,15};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class Animal_GallusGallusDomesticus: AnimalBase
{
    knifeDamageModifier=0.25;
    class Cargo
    {
        itemsCargoSize[]={10,4};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class Animal_GallusGallusDomesticusF: AnimalBase
{
    knifeDamageModifier=0.25;
    class Cargo
    {
        itemsCargoSize[]={10,4};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class Animal_CervusElaphus: AnimalBase
{
    class Cargo
    {
        itemsCargoSize[]={10,20};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class Animal_CervusElaphusF: AnimalBase
{
    class Cargo
    {
        itemsCargoSize[]={10,20};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class Animal_BosTaurus: AnimalBase
{
    knifeDamageModifier=1.5;
    class Cargo
    {
        itemsCargoSize[]={10,40};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class Animal_BosTaurusF: AnimalBase
{
    knifeDamageModifier=1.5;
    class Cargo
    {
        itemsCargoSize[]={10,40};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class Animal_UrsusArctos: AnimalBase
{
    knifeDamageModifier=2.0;
    class Cargo
    {
        itemsCargoSize[]={10,40};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
};

class DeadChicken_ColorBase: Edible_Base
{
    storageCategory=3;
    knifeDamageModifier=0.25;
    class Cargo
    {
        itemsCargoSize[]={10,4};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
    class Skinning
    {
        class ObtainedSteaks
        {
            item="ChickenBreastMeat";
            count=2;
            quantityMinMaxCoef[]={0.5,1};
        };
        class ObtainedFeathers
        {
            item="ChickenFeather";
            count=0;
            quantityMinMaxCoef[]={0.5,1};
            transferToolDamageCoef=1;
        };
        class ObtainedGuts
        {
            item="SmallGuts";
            count=0;
            quantityMinMaxCoef[]={0.5,0.80000001};
        };
        class ObtainedBones
        {
            item="Bone";
            count=1;
            quantityMinMaxCoef[]={0.2,0.30000001};
            transferToolDamageCoef=1;
        };
    };
};

class DeadRabbit: Edible_Base
{
    storageCategory=3;
    knifeDamageModifier=0.25;
    class Cargo
    {
        itemsCargoSize[]={10,4};
        allowOwnedCargoManipulation=1;
        openable=0;
    };
    class Skinning
    {
        class ObtainedSteaks
        {
            item="RabbitLegMeat";
            count=2;
            quantityMinMaxCoef[]={0.5,1};
        };
        class ObtainedPelt
        {
            item="RabbitPelt";
            count=1;
            quantityMinMaxCoef[]={0.5,1};
            transferToolDamageCoef=1;
        };
        class ObtainedGuts
        {
            item="SmallGuts";
            count=0;
            quantityMinMaxCoef[]={0.5,0.80000001};
        };
        class ObtainedBones
        {
            item="Bone";
            count=1;
            quantityMinMaxCoef[]={0.2,0.30000001};
            transferToolDamageCoef=1;
        };
    };
};