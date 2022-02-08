class ActionOpenHomebook: ActionInteractBase
{
	void ActionOpenHomebook()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
		
		if (GetGame().GetUIManager().GetMenu() != NULL) return false;
		if (!player.CanOpenSyberiaUI()) return false;				
		if (!target) return false;
		if (!target.GetObject()) return false;
		
		BuildingLivespace livepsace;
		if (!BuildingLivespace.CastTo(livepsace, target.GetObject())) return false;
		if (!livepsace.IsReady()) return false;
		
		array<string> selections = new array<string>;
		livepsace.GetActionComponentNameList(target.GetComponentIndex(), selections);
		for (int s = 0; s < selections.Count(); s++)
		{
			if ( selections[s] == livepsace.GetData().m_homebook )
			{
				return IsInReach(player, target, UAMaxDistances.DEFAULT);
			}
		}
			
		return false;
	}
	
	override bool SyberiaActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return true;
	}
};