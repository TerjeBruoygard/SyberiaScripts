class StethoscopeMenu extends UIScriptedMenu
{
	bool m_active = false;

	ref TextListboxWidget m_states;
	ref ActionStethoscopeInspect_Data m_data;
	
	void StethoscopeMenu(ref ActionStethoscopeInspect_Data data)
	{
		m_data = data;
	}
	
	void ~StethoscopeMenu()
	{
		if (m_data) {
			delete m_data;
		}
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
	}

    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/StethoscopeMenu.layout" );
		m_states = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("StatesWidget"));
		
		if (m_data.m_health < 0)
		{
			int id = m_states.AddItem("#syb_stethoscope_menu2", NULL, 0);
			m_states.SetItem(id, "#syb_state_dead", NULL, 1);
			m_states.SetItemColor(id, 1, 0xFFE51400);
			
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if (player && player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_MEDICINE_DEATH_CAUSE))
			{
				SetFloatValue("#syb_stethoscope_menu3", m_data.m_blood, PlayerConstants.SL_BLOOD_CRITICAL, PlayerConstants.SL_BLOOD_LOW, PlayerConstants.SL_BLOOD_NORMAL);
				SetIntValue(  "#syb_stethoscope_menu10", m_data.m_cutWounds);
				SetIntValue(  "#syb_stethoscope_menu11", m_data.m_knifeWounds);
				SetIntValue(  "#syb_stethoscope_menu12", m_data.m_bulletWounds);
				SetIntValue(  "#syb_stethoscope_menu13", m_data.m_hematomaWounds);
				SetBoolValue( "#syb_stethoscope_menu17", m_data.m_brokenLegs);
				SetBoolValue( "#syb_stethoscope_menu18", m_data.m_viscera);
				SetBoolValue( "#syb_stethoscope_menu19", m_data.m_sepsis);
				SetBoolValue( "#syb_stethoscope_menu20", m_data.m_concussion);
				SetBoolValue( "#syb_stethoscope_menu21", m_data.m_virusZ);
			}
		}
		else
		{
			SetFloatValue("#syb_stethoscope_menu2", m_data.m_health, PlayerConstants.SL_HEALTH_CRITICAL, PlayerConstants.SL_HEALTH_LOW, PlayerConstants.SL_HEALTH_NORMAL);
			SetFloatValue("#syb_stethoscope_menu3", m_data.m_blood, PlayerConstants.SL_BLOOD_CRITICAL, PlayerConstants.SL_BLOOD_LOW, PlayerConstants.SL_BLOOD_NORMAL);
			SetFloatValue("#syb_stethoscope_menu4", m_data.m_food, PlayerConstants.SL_ENERGY_CRITICAL, PlayerConstants.SL_ENERGY_LOW, PlayerConstants.SL_ENERGY_NORMAL);
			SetFloatValue("#syb_stethoscope_menu5", m_data.m_water, PlayerConstants.SL_WATER_CRITICAL, PlayerConstants.SL_WATER_LOW, PlayerConstants.SL_WATER_NORMAL);
			SetFloatValue("#syb_stethoscope_menu6", m_data.m_temperature, PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_CRITICAL, PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING, 0);
			SetFloatValue("#syb_stethoscope_menu7", m_data.m_sleeping, GetSyberiaConfig().m_sleepingLevel5, GetSyberiaConfig().m_sleepingLevel4, GetSyberiaConfig().m_sleepingLevel3);
			SetFloatValue("#syb_stethoscope_menu8", m_data.m_mind, GetSyberiaConfig().m_mindstateLevel5, GetSyberiaConfig().m_mindstateLevel4, GetSyberiaConfig().m_mindstateLevel4);
			SetLevelValue("#syb_stethoscope_menu9", (int)m_data.m_overdose);
			SetIntValue(  "#syb_stethoscope_menu10", m_data.m_cutWounds);
			SetIntValue(  "#syb_stethoscope_menu11", m_data.m_knifeWounds);
			SetIntValue(  "#syb_stethoscope_menu12", m_data.m_bulletWounds);
			SetIntValue(  "#syb_stethoscope_menu13", m_data.m_hematomaWounds);
			SetLevelValue("#syb_stethoscope_menu14", m_data.m_pain);
			SetLevelValue("#syb_stethoscope_menu15", m_data.m_influenza);
			SetLevelValue("#syb_stethoscope_menu16", m_data.m_stomatchPoison);
			SetLevelValue("#syb_stethoscope_menu22", m_data.m_radiationSickness);
			SetBoolValue( "#syb_stethoscope_menu17", m_data.m_brokenLegs);
			SetBoolValue( "#syb_stethoscope_menu18", m_data.m_viscera);
			SetBoolValue( "#syb_stethoscope_menu19", m_data.m_sepsis);
			SetBoolValue( "#syb_stethoscope_menu20", m_data.m_concussion);
			SetBoolValue( "#syb_stethoscope_menu21", m_data.m_virusZ);
		}
		
		m_active = true;
        return layoutRoot;
    }
	
	private void SetBoolValue(string name, bool value)
	{
		int id = m_states.AddItem(name, NULL, 0);
		if (value) 
		{
			m_states.SetItem(id, "#syb_state_yes", NULL, 1);
			m_states.SetItemColor(id, 1, 0xFFE51400);
		}
		else 
		{
			m_states.SetItem(id, "#syb_state_no", NULL, 1);
			m_states.SetItemColor(id, 1, 0xFF60A917);
		}
	}
	
	private void SetFloatValue(string name, float value, float crit, float bad, float normal)
	{
		string strvalue = "#syb_state_good";
		int color = 0xFF60A917;
		
		if (value <= crit) 
		{
			strvalue = "#syb_state_critical";
			color = 0xFFE51400;
		}
		
		if (value <= bad) 
		{
			strvalue = "#syb_state_bad";
			color = 0xFFFA6800;
		}
		
		if (value <= normal) 
		{
			strvalue = "#syb_state_normal";
			color = 0xFFE3C800;
		}
		
		int id = m_states.AddItem(name, NULL, 0);
		m_states.SetItem(id, strvalue, NULL, 1);
		m_states.SetItemColor(id, 1, color);
	}
	
	private void SetIntValue(string name, int value)
	{
		int color = 0xFF60A917;
		
		if (value > 0) 
		{
			color = 0xFFE51400;
		}
		
		int id = m_states.AddItem(name, NULL, 0);
		m_states.SetItem(id, value.ToString(), NULL, 1);
		m_states.SetItemColor(id, 1, color);
	}
	
	private void SetLevelValue(string name, int value)
	{
		string strvalue = "#syb_state_none";
		int color = 0xFF60A917;
		
		if (value != 0) 
		{
			strvalue = "#syb_skill_level " + value.ToString();
			
			if (value >= 3) color = 0xFFE51400;
			else if (value >= 2) color = 0xFFFA6800;
			else color = 0xFFE3C800;
		}
		
		int id = m_states.AddItem(name, NULL, 0);
		m_states.SetItem(id, strvalue, NULL, 1);
		m_states.SetItemColor(id, 1, color);
	}

	override void Update(float timeslice)
	{
		super.Update(timeslice);

		if (!m_active)
		{
			GetGame().GetUIManager().Back();
		}
	}

	override void OnShow()
	{
		super.OnShow();

		GetGame().GetInput().ChangeGameFocus(1);

		SetFocus( layoutRoot );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(true);
		player.GetActionManager().EnableActions(false);
	}

	override void OnHide()
	{
		super.OnHide();

		GetGame().GetInput().ResetGameFocus();
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
		player.GetActionManager().EnableActions(true);
		
		Close();
	}
}