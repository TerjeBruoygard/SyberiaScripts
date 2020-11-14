modded class MissionGameplay
{
	ref Widget m_AdditionHudRootWidget = null;
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
		
		delete m_AdditionHudRootWidget;
		delete m_SyberiaAdditionalHud;
	}
	
	override void OnInit()
	{
		if ( m_Initialized )
		{
			return;
		}
		
		super.OnInit();
		
		if (!m_AdditionHudRootWidget)
		{
			m_AdditionHudRootWidget = GetGame().GetWorkspace().CreateWidgets("SyberiaScripts/layout/AdditionalHud.layout");
			m_AdditionHudRootWidget.Show(false);
			
			if ( !m_SyberiaAdditionalHud )
			{
				ref Widget actionBlocker = m_AdditionHudRootWidget.FindAnyWidget("ActionBlocker");
				m_AdditionHudRootWidget.RemoveChild(actionBlocker);
				m_SyberiaAdditionalHud = new SyberiaAdditionalHud(m_HudRootWidget, actionBlocker);
				m_SyberiaAdditionalHud.Init();		
			}
			
			if (m_Hud)
			{
				ref Widget panelSleepingStatus = m_AdditionHudRootWidget.FindAnyWidget("Sleeping");
				m_AdditionHudRootWidget.RemoveChild(panelSleepingStatus);
				m_Hud.InitSleepingNotifier(panelSleepingStatus);
			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		UIScriptedMenu menu = m_UIManager.GetMenu();
		
		if (m_SyberiaAdditionalHud && player && m_LifeState == EPlayerStates.ALIVE && !player.IsUnconscious() )
		{
			m_SyberiaAdditionalHud.Refresh();	
		}
		
		if (m_Hud && player)
		{
			m_Hud.DisplayNotifier(NTFKEY_SLEEPING, player.GetSleepingTendency(), player.GetSleepingState());
		}
	}
};