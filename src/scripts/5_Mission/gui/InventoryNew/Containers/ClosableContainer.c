modded class ClosableContainer
{	
	override void Refresh()
	{
		if (!m_Closed && m_Entity)
		{
			if (m_Entity.IsInherited(ItemBase))
			{
				ItemBase item = ItemBase.Cast( m_Entity );
				if (item && item.IsInventoryBlocked())
				{
					m_Closed = true;
					this.OnHide();
					m_Parent.m_Parent.Refresh();
					return;
				}
			}
			else if (m_Entity.IsInherited(ZombieBase))
			{
				ZombieBase zombie = ZombieBase.Cast( m_Entity );
				if (zombie && zombie.IsInventoryBlocked())
				{
					m_Closed = true;
					this.OnHide();
					m_Parent.m_Parent.Refresh();
					return;
				}
			}
		}

		super.Refresh();
	}
};