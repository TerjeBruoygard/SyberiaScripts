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
				m_Hud.InitBadgetWidget(NTFKEY_PAIN, badgets, "Pain");
				m_Hud.InitBadgetWidget(NTFKEY_PAINKILLER, badgets, "Painkiller");
				m_Hud.InitBadgetWidget(NTFKEY_ANTIBIOTIC, badgets, "Antibiotic");
				m_Hud.InitBadgetWidget(NTFKEY_STOMATCHHEAL, badgets, "Stomatchheal");
				m_Hud.InitBadgetWidget(NTFKEY_SEPSIS, badgets, "Sepsis");
				m_Hud.InitBadgetWidget(NTFKEY_ZVIRUS, badgets, "ZVirus");
				m_Hud.InitBadgetWidget(NTFKEY_BANDAGE1, badgets, "Bandage1");
				m_Hud.InitBadgetWidget(NTFKEY_BANDAGE2, badgets, "Bandage2");				
				m_Hud.InitBadgetWidget(NTFKEY_HEMOSTATIC, badgets, "Hemostatic");
				m_Hud.InitBadgetWidget(NTFKEY_HEMATOPOIESIS, badgets, "Hematopoiesis");
				m_Hud.InitBadgetWidget(NTFKEY_USESALVE, badgets, "UseSalve");
				m_Hud.InitBadgetWidget(NTFKEY_ADRENALIN, badgets, "Adrenalin");
				m_Hud.InitBadgetWidget(NTFKEY_OVERDOSED, badgets, "Overdosed");
			}
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (player)
		{
			UIScriptedMenu menu = m_UIManager.GetMenu();
			
			if (m_SyberiaAdditionalHud && m_LifeState == EPlayerStates.ALIVE && !player.IsUnconscious() )
			{
				m_SyberiaAdditionalHud.Refresh();	
			}
			
			if (m_Hud)
			{
				m_Hud.DisplayNotifier(NTFKEY_SLEEPING, player.GetSleepingTendency(), player.GetSleepingState());
				m_Hud.DisplayBadge(NTFKEY_BULLETHIT, player.m_bulletHits);
				m_Hud.DisplayBadge(NTFKEY_KNIFEHIT, player.m_knifeHits);
				m_Hud.DisplayBadge(NTFKEY_HEMATOMA, player.m_hematomaHits);
				m_Hud.DisplayBadge(NTFKEY_VISCERADMG, player.m_visceraHit);
				m_Hud.DisplayBadge(NTFKEY_CONCUSSION, player.m_concussionHit);
				m_Hud.DisplayBadge(NTFKEY_PAIN, player.GetCurrentPainLevel());
				m_Hud.DisplayBadge(NTFKEY_PAINKILLER, player.m_painkillerEffect);
				m_Hud.DisplayBadge(NTFKEY_ANTIBIOTIC, player.m_antibioticsEffect);
				m_Hud.DisplayBadge(NTFKEY_STOMATCHHEAL, player.m_stomatchhealEffect);
				m_Hud.DisplayBadge(NTFKEY_SEPSIS, player.HasVisibleSepsis());
				m_Hud.DisplayBadge(NTFKEY_ZVIRUS, player.HasVisibleZVirus());
				m_Hud.DisplayBadge(NTFKEY_BANDAGE1, player.m_bulletBandage1 + player.m_knifeBandage1);
				m_Hud.DisplayBadge(NTFKEY_BANDAGE2, player.m_bulletBandage2 + player.m_knifeBandage2);
				m_Hud.DisplayBadge(NTFKEY_HEMOSTATIC, player.m_bloodHemostaticEffect);
				m_Hud.DisplayBadge(NTFKEY_HEMATOPOIESIS, player.m_hematopoiesisEffect);
				m_Hud.DisplayBadge(NTFKEY_USESALVE, player.m_salveEffect);
				m_Hud.DisplayBadge(NTFKEY_ADRENALIN, player.m_adrenalinEffect);
				m_Hud.DisplayBadge(NTFKEY_OVERDOSED, (int)Math.Floor(Math.Clamp(player.m_overdosedValue, 0, 3)));
			}
			
			OnUpdateAdvMedicineGUI(player, timeslice);
		}
	}
	
	private void OnUpdateAdvMedicineGUI(PlayerBase player, float deltaTime)
	{		
		if (player.m_overdosedValue > 1)
		{
			float overdosedEffect = Math.Clamp(player.m_overdosedValue * 20, 0, 100);
			player.m_painEffectDurationCur = Math.Clamp(player.m_painEffectDurationCur + deltaTime, 0, overdosedEffect);
		}
		else if (player.GetCurrentPainLevel() > 1)
		{			
			player.m_painEffectDurationCur = Math.Clamp(player.m_painEffectDurationCur + deltaTime, 0, player.m_painLevel * 10);
		}
		else if (player.m_concussionHit)
		{
			player.m_painEffectDurationCur = Math.Clamp(player.m_painEffectDurationCur + deltaTime, 0, 10);
		}
		else
		{
			player.m_painEffectDurationCur = Math.Clamp(player.m_painEffectDurationCur - deltaTime, 0, 100);
		}
		
		if (player.m_painEffectDurationCur > 0)
		{
			PPEffects.SetBlurFlashbang(player.m_painEffectDurationCur * 0.01);
		}
		
		if (player.m_painEffectDurationLast > 0 && player.m_painEffectDurationCur == 0)
		{
			PPEffects.SetBlurFlashbang(0);
		}
		
		player.m_painEffectDurationLast = player.m_painEffectDurationCur;
	}
	
	override int GetRespawnModeClient()
	{
		return GameConstants.RESPAWN_MODE_RANDOM;
	}
};