modded class ActionTogglePlaceObject
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		bool result = super.ActionCondition(player, target, item);
		if (result)
		{
			if (GetGame().IsClient() && player.GetHologramLocal()) return false;
		}
		
		return result;
	}
};