modded class Cooking
{
	override void ProcessItemToCook(notnull ItemBase pItem, ItemBase cookingEquip, Param2<CookingMethodType, float> pCookingMethod, out Param2<bool, bool> pStateFlags)
	{
		Inventory_Base item_to_disinfect = Inventory_Base.Cast(pItem);
		bool hasWater = cookingEquip.IsLiquidPresent() && (cookingEquip.GetQuantity() / cookingEquip.GetQuantityMax()) > 0.2;
		if ( item_to_disinfect && item_to_disinfect.CanBeDisinfected() )
		{
			float cooking_equipment_temp = cookingEquip.GetTemperature();
			if ( hasWater && cooking_equipment_temp >= 100 )
			{
				item_to_disinfect.SetWet( GameConstants.STATE_DAMP );
				item_to_disinfect.SetTemperature(60);
				item_to_disinfect.RemoveAllAgents();
				item_to_disinfect.SetCleanness( 1 );
				return;
			}
		}		
		
		super.ProcessItemToCook(pItem,  cookingEquip, pCookingMethod, pStateFlags);
	}
};
