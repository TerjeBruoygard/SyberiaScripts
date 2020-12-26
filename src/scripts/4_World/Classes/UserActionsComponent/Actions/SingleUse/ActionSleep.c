class ActionSleep: ActionInteractBase
{
	void ActionSleep()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.OpenHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
	}

	override string GetText()
	{
		return "#syb_action_sleep";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!player || !target) 
		{
			return false;
		}
		
		Object targetObject = target.GetObject();		
		if (!targetObject || vector.Distance(player.GetPosition(), targetObject.GetPosition()) > 0.5)
		{
			return false;
		}
		
		if (GetGame().IsClient())
		{
			array<Object> objectsNear = new array<Object>;
			GetGame().GetObjectsAtPosition3D(targetObject.GetPosition(), 0.5, objectsNear, NULL);
			foreach (Object objNear : objectsNear)
			{
				if (objNear != player && objNear.IsInherited(PlayerBase))
				{
					return false;
				}
			}
		}
		
		return true;
	}
	
	override void OnEndClient( ActionData action_data )
	{
		if (action_data.m_Player.GetEmoteManager())
		{
			action_data.m_Player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_LYINGDOWN);
		}
	}
	
	override void OnEndServer( ActionData action_data ) {}
};