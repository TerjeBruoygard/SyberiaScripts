class ActionWashFruitsWell: ActionContinuousBase
{
	void ActionWashFruitsWell()
	{
		m_CallbackClass 	= ActionWashHandsWellCB;
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONFB_WASHHANDSWELL;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override string GetText()
	{
		return "#syb_action_wash";
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Edible_Base fruit = Edible_Base.Cast(item);
		if (!fruit)
		{
			return false;
		}
        
        if (!fruit.IsFruit() && !fruit.IsMushroom())
		{
			return false;
		}
		
		return target.GetObject() && target.GetObject().IsWell();
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_MainItem.RemoveAgent(eAgents.FOOD_POISON);
	}
};

class ActionWashFruitsWater: ActionContinuousBase
{
	void ActionWashFruitsWater()
	{
		m_CallbackClass 	= ActionWashHandsWaterCB;
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONFB_WASHHANDSPOND;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override string GetText()
	{
		return "#syb_action_wash";
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTWaterSurface(UAMaxDistances.DEFAULT, UAWaterType.ALL);
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Edible_Base fruit = Edible_Base.Cast(item);
		if (!fruit)
		{
			return false;
		}
        
        if (!fruit.IsFruit() && !fruit.IsMushroom())
		{
			return false;
		}
		
		return true;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_MainItem.RemoveAgent(eAgents.FOOD_POISON);
	}
};