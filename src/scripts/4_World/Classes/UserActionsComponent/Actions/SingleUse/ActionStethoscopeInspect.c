class ActionStethoscopeInspect: ActionInteractBase
{
	void ActionStethoscopeInspect()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTDummy( );
	}

	override string GetText()
	{
		return "#syb_stethoscope_inspect";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetItemInHands()) 
		return false;
		
		Stethoscope itemStatoschope = Stethoscope.Cast(player.GetItemOnSlot("Eyewear"));
		if (!itemStatoschope)
			return false;
		
		PlayerBase ntarget = PlayerBase.Cast( target.GetObject() );
		if( !ntarget ) return false;

		if (!player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_MEDICINE_SHOW_PLAYER_STATE))
		{
			return false;
		}
		
		return true;
	}
};

class ActionStethoscopeInspect_Data
{
	float m_health;
	float m_blood;
	float m_food;
	float m_water;
	float m_temperature;
	float m_sleeping;
	float m_mind;
	float m_overdose;
	int m_cutWounds;
	int m_knifeWounds;
	int m_bulletWounds;
	int m_hematomaWounds;
	int m_pain;
	int m_influenza;
	int m_stomatchPoison;
	int m_radiationSickness;
	bool m_brokenLegs;
	bool m_viscera;
	bool m_sepsis;
	bool m_concussion;
	bool m_virusZ;
};