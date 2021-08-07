class ActionSearchTargetInventoryCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(3);
	}
};

class ActionSearchTargetInventory : ActionContinuousBase
{
	void ActionSearchTargetInventory()
	{
		m_CallbackClass = ActionSearchTargetInventoryCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTDummy;
	}

	override string GetText()
	{
		return "#syb_search_target_inv";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;
		if( !target.GetObject() ) return false;
		if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;
		if (player.GetItemInHands()) return false;
		
		EntityAI targetEntity = EntityAI.Cast( target.GetObject() );
		if ( !targetEntity ) return false;
		if (targetEntity.IsAlive()) return false;
		if (targetEntity.IsInventoryVisible()) return false;

		return targetEntity.IsZombie();
	}
};