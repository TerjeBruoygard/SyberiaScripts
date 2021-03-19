modded class ActionCPR
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		return super.ActionCondition(player, target, item) && player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_MEDICINE_BRING_FROM_UNCUNSION);
	}
};