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
				ref Widget notifications = m_AdditionHudRootWidget.FindAnyWidget("Notifications");				
				m_Hud.InitNotifierWidget(NTFKEY_SLEEPING, notifications, "Sleeping");
				
				ref Widget badgets = m_AdditionHudRootWidget.FindAnyWidget("Badgets");
				m_Hud.InitBadgetWidget(NTFKEY_BULLETHIT, badgets, "BulletHit");
				m_Hud.InitBadgetWidget(NTFKEY_KNIFEHIT, badgets, "KnifeHit");
				m_Hud.InitBadgetWidget(NTFKEY_HEMATOMA, badgets, "Hematoma");
				m_Hud.InitBadgetWidget(NTFKEY_VISCERADMG, badgets, "VisceraDamage");
				m_Hud.InitBadgetWidget(NTFKEY_CONCUSSION, badgets, "Concussion");
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
			m_Hud.DisplayBadge(NTFKEY_BULLETHIT, player.m_bulletHits);
			m_Hud.DisplayBadge(NTFKEY_KNIFEHIT, player.m_knifeHits);
			m_Hud.DisplayBadge(NTFKEY_HEMATOMA, player.m_hematomaHits);
			m_Hud.DisplayBadge(NTFKEY_VISCERADMG, player.m_visceraHit);
			m_Hud.DisplayBadge(NTFKEY_CONCUSSION, player.m_concussionHit);
		}
	}
};