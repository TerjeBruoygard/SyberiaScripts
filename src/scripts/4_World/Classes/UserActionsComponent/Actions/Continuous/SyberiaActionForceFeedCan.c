modded class ActionForceFeedCan
{	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if (player.IsInteractionWithPlayersBlocked())
            return false;
        
		return CheckBlockerActionCondition(player, target, item) && super.ActionCondition(player, target, item);
	}
};