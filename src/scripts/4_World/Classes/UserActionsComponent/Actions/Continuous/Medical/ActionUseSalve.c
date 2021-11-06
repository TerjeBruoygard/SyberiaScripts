class ActionUseSalveBase: ActionContinuousBase
{	
	void ApplyUseSalve( ItemBase item, PlayerBase player, bool self) {}
	bool ConditionUseSalve( ItemBase item, PlayerBase player, bool self)
	{
		return player.GetSybStats().m_hematomaHits > 0;
	}
	
	override string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "#syb_block_usesalve";
	}
};

class ActionUseSalveCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(10);
	}
};

class ActionUseSalveSelf: ActionUseSalveBase
{	
	void ActionUseSalveSelf()
	{
		m_CallbackClass = ActionUseSalveCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "#syb_action_usesalve";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return CheckBlockerActionCondition(player, target, item) && super.ConditionUseSalve(item, player, true);		
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
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if(action_data.m_MainItem && target)
		{
			ApplyUseSalve( action_data.m_MainItem, target, true );
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		}
	}
};

class ActionUseSalveTarget: ActionUseSalveBase
{	
	void ActionUseSalveTarget()
	{
		m_CallbackClass = ActionUseSalveCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool HasTarget()
	{
		return true;
	}
		
	override string GetText()
	{
		return "#syb_action_usesalve";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if (player.IsInteractionWithPlayersBlocked())
            return false;
        
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		return CheckBlockerActionCondition(player, target, item) && targetPlayer && super.ConditionUseSalve(item, targetPlayer, false);		
	}
	
	override bool ActionBlockerCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
		if (targetPlayer)
		{
			ref ItemBase itemCheck = targetPlayer.GetItemOnSlot("Body");
			if (itemCheck)
			{
				return true;
			}
		}
		
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if(action_data.m_MainItem && target)
		{
			ApplyUseSalve( action_data.m_MainItem, target, false );
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		}
	}
};