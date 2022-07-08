class ActionDebugBuildingToolNext extends ActionContinuousBase
{
	void ActionDebugBuildingToolNext()
	{
		m_CallbackClass = ActionTuneRadioStationCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ITEM_TUNE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_ITEM_TUNE;	
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone;
		m_ConditionItem = new CCINonRuined;
	}
	
	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "Next action";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt)
		{
			dbt.NextAction();
		}
	}
};

class ActionDebugBuildingToolLink extends ActionSingleUseBase
{
	void ActionDebugBuildingToolLink()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM_ONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM_ONCE;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTCursor(UAMaxDistances.BASEBUILDING);
		m_ConditionItem = new CCINonRuined;
	}

	override string GetText()
	{
		return "Link";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
		
		if (!target.GetObject())
			return false;
		
		if (!House.Cast(target.GetObject()))
			return false;
		
		if ( DebugBuildingManager.IsHouseSame(target.GetObject()) ) 
			return false;
		
		DebugBuildingTool dbt = DebugBuildingTool.Cast(item);
		if (!dbt)
			return false;
		
		if (dbt.GetActionID() != 0)
			return false;
		
		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		DebugBuildingManager.LinkHouse( House.Cast(action_data.m_Target.GetObject()) );
	}

	override void OnExecuteServer( ActionData action_data )
	{
		string message = "Linked to '" + action_data.m_Target.GetObject().GetType() + "'";
		GetSyberiaRPC().SendToClient(SyberiaRPC.SYBRPC_SCREEN_MESSAGE, action_data.m_Player.GetIdentity(), new Param1<string>(message));
	}
};

class ActionDebugBuildingToolMarker extends ActionSingleUseBase
{
	void ActionDebugBuildingToolMarker()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "Marker";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
		
		if ( !target ) 
			return false;

		DebugBuildingTool dbt = DebugBuildingTool.Cast(item);
		if (!dbt)
			return false;
		
		if (dbt.GetActionID() != 1)
			return false;

		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		vector hitPos = action_data.m_Target.GetCursorHitPos();
		DebugBuildingManager.AddMarker(hitPos);
	}
};

class ActionDebugBuildingToolObjPos extends ActionSingleUseBase
{
	void ActionDebugBuildingToolObjPos()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor;
	}

	override string GetText()
	{
		return "Relative Pos";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
		
		if ( !target ) 
			return false;
		
		if ( !target.GetObject() ) 
			return false;
		
		if ( DebugBuildingManager.IsHouseSame(target.GetObject()) ) 
			return false;

		DebugBuildingTool dbt = DebugBuildingTool.Cast(item);
		if (!dbt)
			return false;
		
		if (dbt.GetActionID() != 2)
			return false;

		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		vector hitPos = action_data.m_Target.GetObject().GetPosition();
		DebugBuildingManager.RelativePos(hitPos);
	}
};

class ActionDebugBuildingToolSwitchProxies extends ActionSingleUseBase
{
	void ActionDebugBuildingToolSwitchProxies()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "Proxies";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
		
		if ( !target ) 
			return false;
		
		if ( !target.IsProxy() ) 
			return false;
		
		if ( !DebugBuildingManager.IsHouseSame(target.GetParent()) ) 
			return false;

		DebugBuildingTool dbt = DebugBuildingTool.Cast(item);
		if (!dbt)
			return false;
		
		if (dbt.GetActionID() != 3)
			return false;

		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		DebugBuildingManager.SwitchProxies(action_data.m_Target.GetObject());
	}
};