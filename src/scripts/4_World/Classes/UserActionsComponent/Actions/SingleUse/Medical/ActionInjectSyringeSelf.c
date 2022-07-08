class ActionInjectSyringeSelf: ActionSingleUseBase
{
	void ActionInjectSyringeSelf()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INJECTION;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}
	
	override bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		ref ItemBase itemCheck = player.GetItemOnSlot("Body");
		if (itemCheck)
		{
			return true;
		}
		
		return false;
	}
	
	override string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "#syb_action_suringe_blocked";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return CheckBlockerActionCondition(player, target, item) && super.ActionCondition(player, target, item);
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "#syb_syringe_use_action";
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		if (action_data.m_MainItem && action_data.m_Player)
		{
			action_data.m_MainItem.OnApply(action_data.m_Player);
		}
		
        action_data.m_MainItem.SetCleanness(0);
		action_data.m_Player.ServerReplaceItemWithNew(new ReplaceItemWithNewLambda(action_data.m_MainItem, "SyringeEmpty", action_data.m_Player));
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		action_data.m_Player.LocalReplaceItemWithNew(new ReplaceItemWithNewLambda(action_data.m_MainItem, "SyringeEmpty", action_data.m_Player));
	}
};