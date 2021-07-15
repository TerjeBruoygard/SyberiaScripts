#define INJECTOR_ANIM_EVENTS class AnimEvents\
{\
    class SoundWeapon\
    {\
        class Morphine_spear\
        {\
            soundSet="Morphine_spear_SoundSet";\
            id=201;\
        };\
        class Morphine_out\
        {\
            soundSet="Morphine_out_SoundSet";\
            id=202;\
        };\
    };\
}


class MedContainerSmall: Container_Base
{
    scope=2;
    displayName="#syb_medcontainer_small_name";
    descriptionShort="#syb_medcontainer_small_desc";
    model="\dz\gear\containers\FirstAidKit.p3d";
    rotationFlags=17;
    weight=140;
    itemSize[]={3,3};
    itemsCargoSize[]={6,6};
    allowOwnedCargoManipulation=1;
    randomQuantity=2;
    canBeDigged=1;
    isMeleeWeapon=1;
    
    ITEM_DAMAGE_SYSTEM(80, "DZ\gear\containers\data\FirsAidKit.rvmat", "DZ\gear\containers\data\FirsAidKit_damage.rvmat", "DZ\gear\containers\data\FirsAidKit_destruct.rvmat");

    class AnimEvents
    {
        class SoundWeapon
        {
            class pickUpItem_Light
            {
                soundSet="pickUpCourierBag_Light_SoundSet";
                id=796;
            };
            class pickUpItem
            {
                soundSet="pickUpCourierBag_SoundSet";
                id=797;
            };
        };
    };
};

class MedContainerMedium: Container_Base
{
    scope=2;
    displayName="#syb_medcontainer_middle_name";
    descriptionShort="#syb_medcontainer_middle_desc";
    model="SyberiaScripts\data\medical\medium_first_aid_kit.p3d";
    rotationFlags=17;
    weight=250;
    itemSize[]={4,4};
    itemsCargoSize[]={8,8};
    allowOwnedCargoManipulation=1;
    randomQuantity=2;
    canBeDigged=1;
    isMeleeWeapon=1;
    
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\medium_first_aid_kit.rvmat", "SyberiaScripts\data\medical\medium_first_aid_kit_damage.rvmat", "SyberiaScripts\data\medical\medium_first_aid_kit_destruct.rvmat");

    class AnimEvents
    {
        class SoundWeapon
        {
            class pickUpItem_Light
            {
                soundSet="pickUpCourierBag_Light_SoundSet";
                id=796;
            };
            class pickUpItem
            {
                soundSet="pickUpCourierBag_SoundSet";
                id=797;
            };
        };
    };
};

class MedContainerLarge: Container_Base
{
    scope=2;
    displayName="#syb_medcontainer_large_name";
    descriptionShort="#syb_medcontainer_large_desc";
    model="SyberiaScripts\data\medical\large_first_aid_kit.p3d";
    rotationFlags=17;
    weight=500;
    itemSize[]={5,5};
    itemsCargoSize[]={10,10};
    allowOwnedCargoManipulation=1;
    randomQuantity=2;
    canBeDigged=1;
    isMeleeWeapon=1;
    
    ITEM_DAMAGE_SYSTEM(100, "SyberiaScripts\data\medical\large_first_aid_kit.rvmat", "SyberiaScripts\data\medical\large_first_aid_kit.rvmat", "SyberiaScripts\data\medical\large_first_aid_kit.rvmat");

    class AnimEvents
    {
        class SoundWeapon
        {
            class pickUpItem_Light
            {
                soundSet="pickUpCourierBag_Light_SoundSet";
                id=796;
            };
            class pickUpItem
            {
                soundSet="pickUpCourierBag_SoundSet";
                id=797;
            };
        };
    };
};