modded class ActionForceConsume
{
	override bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		if (targetPlayer)
		{
			ref ItemBase itemCheck = targetPlayer.GetItemOnSlot("Mask");
			if (itemCheck)
			{
				bool skipMaskCondition = false;
				string itemMaskType = itemCheck.GetType();
				if (itemMaskType.IndexOf("Balaclava3Holes_") == 0)
				{
					skipMaskCondition = true;
				}
				
				if (!skipMaskCondition)
				{
					return true;
				}
			}
			
			itemCheck = targetPlayer.GetItemOnSlot("Headgear");
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
		}
		
		return false;
	}
	
	override string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "#syb_action_forceconsume_blocked_headgear";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return CheckBlockerActionCondition(player, target, item) && super.ActionCondition(player, target, item);
	}
};