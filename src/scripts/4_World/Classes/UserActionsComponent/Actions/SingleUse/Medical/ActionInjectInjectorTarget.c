class ActionInjectInjectorTarget: ActionSingleUseBase
{
	void ActionInjectInjectorTarget()
	{
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INJECTIONTARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
	
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if (player.IsInteractionWithPlayersBlocked())
            return false;
        
		return super.ActionCondition(player, target, item);
	}
    
	override string GetText()
	{
		return "#syb_syringe_use_action";
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		if (action_data.m_MainItem && action_data.m_Target.GetObject())
		{
			PlayerBase targetPlayer = PlayerBase.Cast( action_data.m_Target.GetObject() );
			if (targetPlayer)
			{
				action_data.m_MainItem.OnApply(targetPlayer);
			}
		}
	}
	
	override void OnEndServer( ActionData action_data )
	{
		if (action_data.m_WasExecuted && action_data.m_MainItem )
		{
			action_data.m_MainItem.Delete();
		}
	}
	
	override void OnEndClient( ActionData action_data )
	{
		if (action_data.m_WasExecuted && action_data.m_MainItem )
		{
			action_data.m_MainItem.DeleteOnClient();
		}
	}
};