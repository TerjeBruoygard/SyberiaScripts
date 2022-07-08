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
		if (dbt) dbt.NextAction();
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
		
		DebugBuildingTool dbt = DebugBuildingTool.Cast(item);
		if (!dbt)
			return false;
		
		if ( dbt.IsHouseSame(House.Cast(target.GetObject())) ) 
			return false;
		
		if (dbt.GetActionID() != 0)
			return false;
		
		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) dbt.LinkHouse( House.Cast(action_data.m_Target.GetObject()) );
	}

	override void OnExecuteServer( ActionData action_data )
	{
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) 
		{
			dbt.LinkHouse( House.Cast(action_data.m_Target.GetObject()) );
			
			string message = "Linked to '" + action_data.m_Target.GetObject().GetType() + "'";
			GetSyberiaRPC().SendToClient(SyberiaRPC.SYBRPC_SCREEN_MESSAGE, action_data.m_Player.GetIdentity(), new Param1<string>(message));
		}
	}
};

class ActionDebugBuildingToolUpgrade extends ActionSingleUseBase
{
	void ActionDebugBuildingToolUpgrade()
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
		return "Upgrade";
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
		
		if ( !target.GetObject() )
			return false;
		
		if ( !target.GetObject().IsInherited(BuildingLivespace) )
			return false;
		
		int componentIndex = target.GetComponentIndex();
		if ( componentIndex == -1 )
			return false;

		return true;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) dbt.UpgradeElement(BuildingLivespace.Cast(action_data.m_Target.GetObject()), action_data.m_Target.GetComponentIndex());
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
		
		DebugBuildingTool dbt = DebugBuildingTool.Cast(item);
		if (!dbt)
			return false;
		
		if ( dbt.IsHouseSame(House.Cast(target.GetObject())) ) 
			return false;

		if (dbt.GetActionID() != 2)
			return false;

		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		vector hitPos = action_data.m_Target.GetObject().GetPosition();
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) dbt.RelativePos(action_data.m_Target.GetObject(), hitPos);
	}
};

class ActionDebugBuildingToolObjRot extends ActionSingleUseBase
{
	void ActionDebugBuildingToolObjRot()
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
		return "Relative Rot";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
		
		if ( !target ) 
			return false;
		
		if ( !target.GetObject() ) 
			return false;
		
		DebugBuildingTool dbt = DebugBuildingTool.Cast(item);
		if (!dbt)
			return false;
		
		if ( dbt.IsHouseSame(House.Cast(target.GetObject())) ) 
			return false;
		
		if (dbt.GetActionID() != 3)
			return false;

		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		vector rot = action_data.m_Target.GetObject().GetLocalYawPitchRoll();
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) dbt.RelativeRot(rot);
	}
};

class ActionDebugBuildingToolDoorID extends ActionSingleUseBase
{
	void ActionDebugBuildingToolDoorID()
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
		return "Get Door ID";
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
		
		if (dbt.GetActionID() != 4)
			return false;
		
		House house = House.Cast( target.GetObject() );
		if (!house)
			return false;
		
		int doorIndex = house.GetDoorIndex(target.GetComponentIndex());
		if ( doorIndex != -1 )
		{
			return true;
		}

		return false;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt)
		{
			House house = House.Cast( action_data.m_Target.GetObject() );
			int doorIndex = house.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			dbt.GetDoorID(doorIndex);
		}
	}
};

class ActionDebugBuildingToolElementID extends ActionSingleUseBase
{
	void ActionDebugBuildingToolElementID()
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
		return "Element ID";
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
		
		if (dbt.GetActionID() != 5)
			return false;
		
		if ( !target.GetObject() )
			return false;
		
		if ( !target.GetObject().IsInherited(BuildingLivespace) )
			return false;

		int componentIndex = target.GetComponentIndex();
		if ( componentIndex == -1 )
			return false;

		return true;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) dbt.GetElementID(BuildingLivespace.Cast(action_data.m_Target.GetObject()), action_data.m_Target.GetComponentIndex());
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
		
		if (dbt.GetActionID() != 6)
			return false;

		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		vector hitPos = action_data.m_Target.GetCursorHitPos();
		
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) dbt.AddMarker(hitPos);
	}
};

class ActionDebugBuildingToolSizer extends ActionSingleUseBase
{
	void ActionDebugBuildingToolSizer()
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
		return "Ruler";
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
		
		if (dbt.GetActionID() != 7)
			return false;

		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		vector hitPos = action_data.m_Target.GetCursorHitPos();
		DebugBuildingTool dbt = DebugBuildingTool.Cast(action_data.m_MainItem);
		if (dbt) dbt.Ruler(hitPos);
	}
};