modded class ActionDigInStash
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		bool result = super.ActionCondition( player, target, item );
		
		// Check handdrill skill
		if (result && !player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_SURVIVAL_DIG_ITEMS))
		{
			return false;
		}
		
		return result;
	}
};