modded class Cooking
{
    override int CookWithEquipment( ItemBase cooking_equipment, float cooking_time_coef = 1 )
	{
		float cooking_equipment_temp;
		int cooking_state_update = 0;
		bool is_done;
		bool is_empty;
		bool is_burned;
		
		//check cooking conditions
		if ( cooking_equipment == NULL )
		{
			return cooking_state_update;
		}
		
		//manage items in cooking equipment
		CookingMethodType cooking_method = GetCookingMethod( cooking_equipment );
		CargoBase cargo = cooking_equipment.GetInventory().GetCargo();
		bool hasWater = cooking_equipment.IsLiquidPresent() && (cooking_equipment.GetQuantity() / cooking_equipment.GetQuantityMax()) > 0.2;
		if ( cargo.GetItemCount() == 0 )
		{
			is_empty = true;
		}
		//process items
		for ( int i = 0; i < cargo.GetItemCount(); i++ )
		{
			ItemBase item = ItemBase.Cast( cargo.GetItem( i ) );
			Edible_Base item_to_cook = Edible_Base.Cast( item );
			
			if ( item_to_cook && item_to_cook.CanBeCooked() )
			{
				//update food
				cooking_state_update = UpdateCookingState( item_to_cook, cooking_method, cooking_equipment, cooking_time_coef );
				
				//check for done state for boiling and drying
				if ( item_to_cook.IsFoodBoiled() || item_to_cook.IsFoodDried() )
				{
					is_done = true;
				}
				//check for done state fro baking (exclude Lard from baked items)
				else if ( item_to_cook.IsFoodBaked() && item_to_cook.Type() != Lard )		
				{
					is_done = true;
				}
				//check for burned state
				else if ( item_to_cook.IsFoodBurned() )
				{
					is_burned = true;
				}
			}
			else if ( item && item.CanBeDisinfected() )
			{
				cooking_equipment_temp = cooking_equipment.GetTemperature();
				if (hasWater && cooking_equipment_temp >= 100 && Math.RandomFloat01() < (0.1 * cooking_time_coef))
				{
					item.SetCleanness(1);
				}
			}
			else
			{
				if (!hasWater)
				{
					//damage item
					item.DecreaseHealth( "", "", PARAM_BURN_DAMAGE_COEF * 100 );
				}
				
				//add temperature to item
				AddTemperatureToItem( item, NULL, 0 );
			}
			
			if (hasWater)
			{
				item.AddWet( 0.05 * cooking_time_coef );
			}
		}
		
		//manage cooking equipment
		Bottle_Base bottle_base = Bottle_Base.Cast( cooking_equipment );
		if ( bottle_base )
		{
			cooking_equipment_temp = cooking_equipment.GetTemperature();
			bool is_water_boiling;
			
			//handle water boiling
			if ( cooking_equipment_temp >= LIQUID_BOILING_POINT )
			{
				//remove agents
				cooking_equipment.RemoveAllAgents();
				
				if ( cooking_equipment.GetQuantity() > 0 )
				{
					is_water_boiling = true;
					
					//vaporize liquid
					cooking_equipment.AddQuantity( -LIQUID_VAPOR_QUANTITY );
				};
			}
			
			//handle audio visuals
			bottle_base.RefreshAudioVisualsOnClient( cooking_method, is_done, is_empty, is_burned );
		}

		FryingPan frying_pan = FryingPan.Cast( cooking_equipment );
		if ( frying_pan && !bottle_base )
		{
			//handle audio visuals
			frying_pan.RefreshAudioVisualsOnClient( cooking_method, is_done, is_empty, is_burned );
		}
		
		return cooking_state_update;
	}
};