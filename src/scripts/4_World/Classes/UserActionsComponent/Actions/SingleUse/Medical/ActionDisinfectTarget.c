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
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Player.SetBloodyHands(false);
		super.OnFinishProgressServer(action_data);
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
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());		
		if( target )
		{
			target.SetBloodyHands(false);
		}
		
		super.OnFinishProgressServer(action_data);
	}
}