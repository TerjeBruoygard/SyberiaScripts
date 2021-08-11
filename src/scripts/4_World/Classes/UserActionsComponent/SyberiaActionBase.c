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
	
	bool SyberiaActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (target && target.GetObject() && target.GetObject().IsInherited(PlayerBase))
		{
			PlayerBase targetHuman = PlayerBase.Cast( target.GetObject() );
			if (targetHuman && targetHuman.IsNPC())
			{
				return false;
			}
		}
		
		return true;
	}
	
	override bool Can( PlayerBase player, ActionTarget target, ItemBase item, int condition_mask )
	{
		if (!SyberiaActionCondition(player, target, item))
		{
			return false;
		}
		
		return super.Can( player, target, item, condition_mask );
	}
	
	override bool Can( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!SyberiaActionCondition(player, target, item))
		{
			return false;
		}
		
		return super.Can( player, target, item );
	}
};