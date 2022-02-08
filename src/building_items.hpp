#define BUILDING_ITEMS_DMGSYS class DamageSystem { \
    class GlobalHealth { \
        class Health { hitpoints=1000; }; \
    }; \
    class GlobalArmor { \
        class Projectile { \
            class Health { damage=0; }; \
            class Blood { damage=0; }; \
            class Shock { damage=0; }; \
        }; \
        class Melee { \
            class Health { damage=0; }; \
            class Blood { damage=0; }; \
            class Shock { damage=0; }; \
        }; \
        class FragGrenade { \
            class Health { damage=0; }; \
            class Blood { damage=0; }; \
            class Shock { damage=0; }; \
        }; \
    }; \
}

class ItemHomebook: Inventory_Base
{
    scope = 2;
    title = "#syb_homebook_name";
    displayName = "#syb_homebook_name";
    descriptionShort = "#syb_homebook_desc";
    model="\DZ\gear\containers\christmasbox1.p3d";
    itemSize[]={2,2};
    weight=250;
    ITEM_DAMAGE_SYSTEM(50, "", "", "");
};