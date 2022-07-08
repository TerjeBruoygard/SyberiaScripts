modded class ActionInjectTarget
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if (player.IsInteractionWithPlayersBlocked())
            return false;

		return super.ActionCondition(player, target, item);
	}
}