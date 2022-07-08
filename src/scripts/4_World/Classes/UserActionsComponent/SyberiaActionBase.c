modded class ActionBase
{
	bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return false;
	}
	
	string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "";
	}
	
	bool CheckBlockerActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		ActionManagerBase actionManager = player.GetActionManager();
		actionManager.m_ActionBlockerTimeStamp = GetGame().GetTime();
		
		if (ActionBlockerCondition(player, target, item))
		{			
			actionManager.m_ActionBlockerText = ActionBlockerText(player, target, item);
			return false;
		}
		else
		{
			actionManager.m_ActionBlockerText = "";
			return true;
		}
	}
};