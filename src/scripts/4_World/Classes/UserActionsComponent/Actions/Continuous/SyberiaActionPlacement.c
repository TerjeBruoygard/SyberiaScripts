class SyberiaActionPlacementPreview : ActionTogglePlaceObject { };

class SyberiaActionPlacementReciveData : ActionReciveData
{
	vector m_Position;
	vector m_Orientation;
};

class SyberiaActionPlacementData : ActionData
{
	vector m_Position;
	vector m_Orientation;
};

class SyberiaActionPlacementApplyCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DEFAULT_DEPLOY);
	}
};

class SyberiaActionPlacementApply : ActionContinuousBase
{
	void SyberiaActionPlacementApply()
	{
		m_CallbackClass		= SyberiaActionPlacementApplyCB;
		m_SpecialtyWeight 	= UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONFB_DEPLOY_2HD;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}
	
	override bool HasTarget()
	{
		return false;
	}

	override bool HasProgress()
	{
		return true;
	}
	
	override string GetText()
	{
		return "#deploy_object";
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{
		return true;
	}
	
	override ActionData CreateActionData()
	{
		SyberiaActionPlacementData action_data = new SyberiaActionPlacementData;
		return action_data;
	}
	
	override bool SetupAction(PlayerBase player, ActionTarget target, ItemBase item, out ActionData action_data, Param extra_data = NULL)
	{	
		if ( super.SetupAction(player, target, item, action_data, extra_data ))
		{
			SyberiaActionPlacementData poActionData;
			poActionData = SyberiaActionPlacementData.Cast(action_data);
			if (!GetGame().IsMultiplayer() || GetGame().IsClient() )
			{
				Hologram hologram = player.GetHologramLocal();
				if (hologram)
				{
					poActionData.m_Position = player.GetHologramLocal().GetProjectionPosition();
					poActionData.m_Orientation = player.GetHologramLocal().GetProjectionOrientation();
			
					poActionData.m_Player.SetLocalProjectionPosition( poActionData.m_Position );
					poActionData.m_Player.SetLocalProjectionOrientation( poActionData.m_Orientation );
				}
				else
				{
					return false;
				}
			}
			
			if ( !action_data.m_MainItem )
				return false;
			
			return true;
		}
		
		return false;
	}
	
	override void WriteToContext(ParamsWriteContext ctx, ActionData action_data)
	{
		super.WriteToContext(ctx, action_data);
		
		SyberiaActionPlacementData poActionData;
		poActionData = SyberiaActionPlacementData.Cast(action_data);

		ctx.Write( poActionData.m_Position );
		ctx.Write( poActionData.m_Orientation );
	}
	
	override bool ReadFromContext(ParamsReadContext ctx, out ActionReciveData action_recive_data )
	{
		if( !action_recive_data )
			action_recive_data = new SyberiaActionPlacementReciveData;
		
		super.ReadFromContext(ctx, action_recive_data );
		SyberiaActionPlacementReciveData action_data_po = SyberiaActionPlacementReciveData.Cast(action_recive_data);
		
		vector entity_position = "0 0 0";
		vector entity_orientation = "0 0 0";
		if (!ctx.Read(entity_position))
			return false;
		if (!ctx.Read(entity_orientation))
			return false;
		
		action_data_po.m_Position = entity_position;
		action_data_po.m_Orientation = entity_orientation;
		
		return true;
	}
	
	override void HandleReciveData(ActionReciveData action_recive_data, ActionData action_data)
	{
		super.HandleReciveData(action_recive_data, action_data);
		
		SyberiaActionPlacementReciveData recive_data_po = SyberiaActionPlacementReciveData.Cast(action_recive_data);
		SyberiaActionPlacementData action_data_po = SyberiaActionPlacementData.Cast(action_data);
		
		action_data_po.m_Position = recive_data_po.m_Position;
		action_data_po.m_Orientation = recive_data_po.m_Orientation;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if (player.IsBuildingModeBlocked())
            return false;
        
		//Client
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			if ( player.IsPlacingLocal() )
			{
				if ( !player.GetHologramLocal().IsColliding() )
				{
					if ( item.CanBePlaced(player, player.GetHologramLocal().GetProjectionEntity().GetPosition()) )
					{
						return true;
					}
				}
			}
			return false;
		}
		
		//Server
		return true; 
	}
	
	override void OnStartClient( ActionData action_data )
	{	
		if ( action_data.m_Player.IsPlacingLocal() )
		{
			action_data.m_Player.GetHologramLocal().SetUpdatePosition( false );
		}
	}
	
	override void OnStartServer( ActionData action_data )
	{
		if ( action_data.m_Player.IsPlacingServer() )
		{
			action_data.m_Player.GetHologramServer().SetUpdatePosition( false );
		}
	}
	
	override void OnEndClient( ActionData action_data  )
	{
		if ( action_data.m_Player.IsPlacingLocal() )
		{
			action_data.m_Player.PlacingCompleteLocal();
		}
	}
	
	override void OnEndServer( ActionData action_data ) {}
};