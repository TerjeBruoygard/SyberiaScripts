class ActionTraderInteract: ActionInteractBase
{
	void ActionTraderInteract()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject;
	}

	override string GetText()
	{
		return "#syb_action_trade";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
		
		if (GetGame().GetUIManager().GetMenu() != NULL) return false;
		if (!player.CanOpenSyberiaUI()) return false;				
		if (target && target.GetObject())
		{
			TraderPoint traderPoint = FindTraderPoint(target.GetObject().GetPosition());
			if (traderPoint && traderPoint.IsTraderReady() && traderPoint.GetTraderObject() == target.GetObject() )
			{
				return true;
			}
		}
			
		return false;
	}
	
	override bool SyberiaActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return true;
	}
	
	TraderPoint FindTraderPoint(vector pos)
	{
		TraderPoint result = null;
		ref array<Object> objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(pos, 0.1, objects, NULL);			
		foreach (Object obj : objects)
		{
			if (obj.IsInherited(TraderPoint))
			{
				result = TraderPoint.Cast(obj);
				break;
			}
		}
		
		delete objects;
		return result;
	}
};