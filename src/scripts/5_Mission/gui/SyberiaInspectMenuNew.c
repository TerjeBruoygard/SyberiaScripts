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
};