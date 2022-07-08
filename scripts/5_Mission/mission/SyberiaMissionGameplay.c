modded class MissionGameplay
{
	ref SyberiaAdditionalHud m_SyberiaAdditionalHud = null;
	
	override void OnMissionStart()
	{
		SybLog("MissionGameplay OnMissionStart");
		super.OnMissionStart();
	}
	
	override void OnMissionFinish()
	{
		SybLog("MissionGameplay OnMissionStart");
		super.OnMissionFinish();
		
		delete m_SyberiaAdditionalHud;
	}
	
	override void OnInit()
	{
		if ( m_Initialized )
		{
			return;
		}
		
		super.OnInit();
		
		SybLog("MissionGameplay OnInit");
		if ( !m_SyberiaAdditionalHud )
		{
			m_SyberiaAdditionalHud = new SyberiaAdditionalHud(m_HudRootWidget);
			m_SyberiaAdditionalHud.Init();		
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		Man player = GetGame().GetPlayer();
		UIScriptedMenu menu = m_UIManager.GetMenu();
		
		if (player && m_LifeState == EPlayerStates.ALIVE && !player.IsUnconscious() )
		{
			if (m_SyberiaAdditionalHud)
			{
				if ( menu == NULL )
				{
					m_SyberiaAdditionalHud.Refresh();
				}
				else
				{
					m_SyberiaAdditionalHud.Hide();
				}		
			}
		}
	}
};