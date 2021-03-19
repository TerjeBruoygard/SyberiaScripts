modded class Cooking
{
    override int CookWithEquipment( ItemBase cooking_equipment, float cooking_time_coef = 1 )
	{
		int result = super.CookWithEquipment(cooking_equipment, cooking_time_coef);
		
		CargoBase cargo = cooking_equipment.GetInventory().GetCargo();
		bool hasWater = cooking_equipment.IsLiquidPresent() && (cooking_equipment.GetQuantity() / cooking_equipment.GetQuantityMax()) > 0.2;
		for ( int i = 0; i < cargo.GetItemCount(); i++ )
		{
			ItemBase item = ItemBase.Cast( cargo.GetItem( i ) );
			SyringeDirty syringeDirtyItem = SyringeDirty.Cast( item );			
			if ( syringeDirtyItem )
			{
				if (hasWater)
				{
					item.AddHealth( "", "", PARAM_BURN_DAMAGE_COEF * 100 );
					
					float temperature = item.GetTemperature();
					if (temperature > 70 && Math.RandomFloat01() < (0.05 * cooking_time_coef))
					{
						cooking_equipment.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, new ReplaceItemWithNewLambda(item, "SyringeEmpty", NULL));
					}
				}
			}
			
			SyringeEmpty syringeEmptyItem = SyringeEmpty.Cast( item );
			if ( hasWater && !syringeEmptyItem.IsRuined() && syringeEmptyItem )
			{
				item.AddHealth( "", "", PARAM_BURN_DAMAGE_COEF * 100 );
			}
			
			if ( hasWater && item && !item.IsRuined() && GetGame().ConfigGetInt("CfgVehicles " + item.GetType() + " medGloves") == 1)
			{
				item.AddHealth( "", "", PARAM_BURN_DAMAGE_COEF * 100 );
			}
		}
		
		return result;
	}
};