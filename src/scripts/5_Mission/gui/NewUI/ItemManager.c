modded class ItemManager
{
    override void SetIconTemperature( EntityAI item, Widget item_w )
	{
		if ( item_w )
		{
			if ( item && item.IsInherited( ItemBase ) )
			{
				int color = ColorManager.GetInstance().GetItemColor( ItemBase.Cast( item ) );

				if ( color )
				{
					Widget color_widget = item_w.FindAnyWidget( "Color" );
					if (color_widget)
					{
						if( color != -1 )
						{
							color_widget.SetColor( color );
						}
						else
						{
							color_widget.SetColor( ColorManager.BASE_COLOR );
						}
					}
				}
			}
		}
	}
};