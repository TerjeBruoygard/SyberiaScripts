class ActionCheckName: ActionInteractBase
{
	void ActionCheckName()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "#syb_inspect_player";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (SYB_CHECK_IDENTITY_MODE == 0)
		{
			return false;
		}
		
		PlayerBase ntarget = PlayerBase.Cast(  target.GetObject() );
		if( ntarget )
		{
			if (SYB_CHECK_IDENTITY_MODE == 1)
			{
				if (!IsFaceClosed(ntarget))
				{
					return true;
				}
			}
			else if (SYB_CHECK_IDENTITY_MODE == 2)
			{
				if (!ntarget.IsAlive() || ntarget.IsUnconscious())
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	private bool IsFaceClosed(PlayerBase player)
	{
		ref ItemBase itemCheck = player.GetItemOnSlot("Mask");
		if (itemCheck)
		{
			return true;
		}
		
		itemCheck = player.GetItemOnSlot("Headgear");
		if (itemCheck)
		{
			string configPathNoMask = "CfgVehicles " + itemCheck.GetType() +  " noMask";
			if (GetGame().ConfigIsExisting(configPathNoMask))
			{
				if (GetGame().ConfigGetInt(configPathNoMask) == 1)
				{
					return true;
				}
			}
		}
		
		return false;
	}
}