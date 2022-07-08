modded class ColorManager
{
    int GetItemColor( ItemBase item )
	{
		ItemBase dragged_item = ItemBase.Cast( ItemManager.GetInstance().GetDraggedItem() );		
		if ( dragged_item )
			return 0;

		int color = -1;
		if( item && item.IsTemperatureVisible() ) 
		{
			color = GetSyberiaTemperatureColor( item.GetTemperature(), 128 );
		}
		
		return color;
    }
};