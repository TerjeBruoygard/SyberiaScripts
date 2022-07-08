modded class ClosableContainer
{
	override void ShowContent( bool force_show = false )
	{
		if (m_Entity)
		{
			ItemBase item = ItemBase.Cast( m_Entity );
			if (item && item.IsInventoryBlocked())
			{
				super.HideContent(force_show);
				return;
			}
		}
		
		super.ShowContent(force_show);
	}
};