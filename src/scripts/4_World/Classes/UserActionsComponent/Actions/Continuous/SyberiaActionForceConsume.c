modded class ActionForceConsume
{
	override bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		return targetPlayer && targetPlayer.IsFaceBlocked(true);
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