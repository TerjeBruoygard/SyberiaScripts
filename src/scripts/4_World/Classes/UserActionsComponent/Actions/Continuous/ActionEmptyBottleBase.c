modded class ActionEmptyBottleBase
{
    override bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return (item && item.IsTemperatureVisible() && item.GetTemperature() < 0);
	}
	
	override string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "#syb_action_empty_blocked_temp";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return CheckBlockerActionCondition(player, target, item) && super.ActionCondition(player, target, item);
	}
};