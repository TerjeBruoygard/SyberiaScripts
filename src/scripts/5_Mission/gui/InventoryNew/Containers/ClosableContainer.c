modded class ClosableContainer
{
	override void ShowContent( bool force_show = false )
	{
		if (m_Entity)
		{
			if (m_Entity.IsInherited(ItemBase))
			{
				ItemBase item = ItemBase.Cast( m_Entity );
				if (item && item.IsInventoryBlocked())
				{
					super.HideContent(force_show);
					return;
				}
			}
			
			if (m_Entity.IsInherited(ZombieBase))
			{
				ZombieBase zombie = ZombieBase.Cast( m_Entity );
				if (zombie && zombie.IsInventoryBlocked())
				{
					super.HideContent(force_show);
					return;
				}
			}
		}
		
		super.ShowContent(force_show);
	}
};