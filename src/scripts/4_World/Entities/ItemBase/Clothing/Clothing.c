modded class Clothing
{
	override bool CanBeDisinfected()
	{
		return true;
	}

	override bool IsInventoryBlocked()
	{
		if (GetGame().IsClient())
		{
			if (GetSyberiaOptions() && GetSyberiaOptions().m_client && GetSyberiaOptions().m_client.m_blockAccessToBackpack)
			{
				PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
				if (player && player == GetGame().GetPlayer())
				{
					ItemBase back = player.GetItemOnSlot("Back");
					if (back == this)
					{
						return true;
					}
				}
			}
		}
		
		return super.IsInventoryBlocked();
	}
};