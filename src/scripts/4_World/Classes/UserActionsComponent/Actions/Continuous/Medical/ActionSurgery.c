class ActionSurgeryBase: ActionContinuousBase
{	
	void ApplySurgery( ItemBase item, PlayerBase operator, PlayerBase player, bool self) {}
	bool ConditionSurgery( ItemBase item, PlayerBase player, bool self)
	{
		if ( (GetSyberiaOptions().m_client.m_operateVisceraHimself || !self) && player.GetSybStats().m_visceraHit )
		{
			return true;
		}
		
		return (player.GetSybStats().m_bulletHits > 0) || (player.GetSybStats().m_knifeHits > 0);
	}
	
	override string ActionBlockerText( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return "#syb_surg_blocked";
	}
};

class ActionSurgeryCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(20);
	}
};

class ActionSurgerySelf: ActionSurgeryBase
{	
	void ActionSurgerySelf()
	{
		m_CallbackClass = ActionSurgeryCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
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
		return "#syb_action_surg";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return CheckBlockerActionCondition(player, target, item) && super.ConditionSurgery(item, player, true);		
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
			ApplySurgery( action_data.m_MainItem, target, target, true );
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		}
	}
};

class ActionSurgeryTarget: ActionSurgeryBase
{	
	void ActionSurgeryTarget()
	{
		m_CallbackClass = ActionSurgeryCB;
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
		return "#syb_action_surg";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        if (player.IsInteractionWithPlayersBlocked())
            return false;
        
		PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());	
		return CheckBlockerActionCondition(player, target, item) && targetPlayer && super.ConditionSurgery(item, targetPlayer, false);		
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
		PlayerBase operator = PlayerBase.Cast(action_data.m_Player);		
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());		
		if(action_data.m_MainItem && target)
		{
			ApplySurgery( action_data.m_MainItem, operator, target, false );
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		}
	}
};