modded class InspectMenuNew
{
    override static void UpdateItemInfoTemperature(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		ItemBase item_base = ItemBase.Cast( item );
		if( item_base && item_base.IsTemperatureVisible() )
		{
			float temperature = item_base.GetTemperature();
            if ( temperature > 100 )
            {
                temperature = 100 * Math.Floor( temperature / 100.0 );
            }
			else if ( temperature > 10 )
			{
				temperature = 10 * Math.Floor( temperature / 10.0 );
			}
            else
			{
				temperature = 5 * Math.Floor( temperature / 5.0 );
			}
            
            WidgetTrySetText(root_widget, "ItemTemperatureWidget",  "#inv_inspect_about " + temperature.ToString() +  " " + "#inv_inspect_celsius", GetSyberiaTemperatureColor( temperature, 255 ) );
		}
        else
        {
            WidgetTrySetText(root_widget, "ItemTemperatureWidget", "");
        }
	}
	
	override static void UpdateItemInfoWetness(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		float wetness = 0;
		
		if ( item.IsInherited(ItemBase) )
		{
			ItemBase item_IB = ItemBase.Cast( item );
			if (!item_IB.IsTemperatureVisible() || item_IB.GetTemperature() > 0)
			{
				wetness = item_IB.GetWet();
			}
		}

		if( wetness < GameConstants.STATE_DAMP )
		{
			WidgetTrySetText(root_widget, "ItemWetnessWidget", "");
		}
		else if( wetness >= GameConstants.STATE_DAMP && wetness < GameConstants.STATE_WET )
		{
			WidgetTrySetText(root_widget, "ItemWetnessWidget", "#inv_inspcet_damp", Colors.COLOR_DAMP);
		}
		else if( wetness >= GameConstants.STATE_WET && wetness < GameConstants.STATE_SOAKING_WET )
		{
			WidgetTrySetText( root_widget, "ItemWetnessWidget", "#inv_inspect_wet", Colors.COLOR_WET );
		}
		else if( wetness >= GameConstants.STATE_SOAKING_WET && wetness < GameConstants.STATE_DRENCHED )
		{
			WidgetTrySetText( root_widget, "ItemWetnessWidget", "#inv_inspect_soaking_wet", Colors.COLOR_SOAKING_WET );
		}
		else
		{
			WidgetTrySetText( root_widget, "ItemWetnessWidget", "#inv_inspect_drenched", Colors.COLOR_DRENCHED );
		}
	}
	
	override static void UpdateItemInfoLiquidType(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		
		ItemBase item_base = ItemBase.Cast( item );
		
		if( item_base && item_base.GetQuantity() > 0 && item_base.IsBloodContainer() )
		{
			BloodContainerBase blood_container = BloodContainerBase.Cast( item_base );
			
			if( blood_container.GetBloodTypeVisible() )
			{
				string type;
				bool positive;
				string blood_type_name = BloodTypes.GetBloodTypeName(blood_container.GetLiquidType(), type, positive);
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_blood: " + blood_type_name, Colors.COLOR_LIQUID);
			}
			else
			{
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_blood", Colors.COLOR_LIQUID);
			}
		}
		else if( item_base && item_base.GetQuantity() > 0 && item_base.IsLiquidContainer() )
		{
			int liquid_type = item_base.GetLiquidType();
			int temperature = item_base.GetTemperature();
			switch(liquid_type)
			{
				case LIQUID_WATER:
				{
					if (temperature < 0) WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#syb_liquid_ice", Colors.COLOR_LIQUID);
					else WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_water", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_RIVERWATER:
				{
					if (temperature < 0) WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#syb_liquid_ice", Colors.COLOR_LIQUID);
					else WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_river_water", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_VODKA:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_vodka", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_BEER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_beer", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_GASOLINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_gasoline", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DIESEL:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_diesel", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DISINFECTANT:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_disinfectant", Colors.COLOR_LIQUID);
					break;
				}
	
				case LIQUID_SALINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_saline", Colors.COLOR_LIQUID);
					break;
				}
				
				default:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "ERROR", Colors.COLOR_LIQUID);
					break;
				}
			}
		}
		else
		{
			WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "");
		}
	}
};