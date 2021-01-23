modded class ActionDrinkWellContinuous
{
	override bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!target.GetObject() || !target.GetObject().IsWell())
		{
			return false;
		}
		
		return player.IsFaceBlocked(true);
	}
	
	override string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "#syb_action_consume_blocked_headgear";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return CheckBlockerActionCondition(player, target, item) && super.ActionCondition(player, target, item);
	}
};

modded class ActionDrinkPondContinuous
{
	override bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return player.IsFaceBlocked(true);
	}
	
	override string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return CheckBlockerActionCondition(player, target, item) && super.ActionCondition(player, target, item);
	}
};