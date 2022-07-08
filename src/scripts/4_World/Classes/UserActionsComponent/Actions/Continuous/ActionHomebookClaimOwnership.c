class ActionHomebookClaimOwnershipCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(3.0);
	}
};

class ActionHomebookClaimOwnership: ActionContinuousBase
{
	void ActionHomebookClaimOwnership()
	{
		m_CallbackClass 	= ActionHomebookClaimOwnershipCB;
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override string GetText()
	{
		return "#syb_homebook_action";
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursorNoObject(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		House house;
		if ( target.GetObject() && Class.CastTo(house, target.GetObject()) )
		{
			if (house.IsInherited(BuildingLivespace)) return false;
			if (GetGame().IsServer()) return true;
			
			if (BuildingLivespace.CheckPossibleLivespaceId(house, target.GetCursorHitPos()) != -1)
			{
				if (BuildingLivespace.FindLivespace(house, target.GetCursorHitPos()) == null)
				{
					return true;
				}
			}
		}
		
		return false;
	}
};