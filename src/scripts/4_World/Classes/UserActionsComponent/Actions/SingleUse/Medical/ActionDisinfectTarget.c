modded class ActionDisinfectSelf
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetItemOnSlot("Gloves"))
			return false;
		
		return true;
	}
	
	override string GetText()
	{
		return "#syb_disinfect_hands";
	}
};

modded class ActionDisinfectTarget
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if (player.IsInteractionWithPlayersBlocked())
            return false;

		if (target && target.GetObject())
		{
			PlayerBase other = PlayerBase.Cast( target.GetObject() );
			if (other.GetItemOnSlot("Gloves"))
			{
				return false;
			}
		}
		
		return true;
	}
	
	override string GetText()
	{
		return "#syb_disinfect_hands";
	}
}