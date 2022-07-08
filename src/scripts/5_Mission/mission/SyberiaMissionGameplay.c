modded class MissionGameplay
{
	ref Widget m_AdditionHudRootWidget = null;
	ref SyberiaAdditionalHud m_SyberiaAdditionalHud = null;
	bool m_isAltPressed = false;
	
	override void OnMissionStart()
	{
		SybLog("MissionGameplay OnMissionStart");
		super.OnMissionStart();
		SyberiaPPEffects.ResetAllEffects();
	}
	
	override void OnMissionFinish()
	{
		SybLog("MissionGameplay OnMissionStart");
		super.OnMissionFinish();
		
		delete m_AdditionHudRootWidget;
		delete m_SyberiaAdditionalHud;
		SyberiaPPEffects.ResetAllEffects();
	}
	
	override void OnInit()
	{
		super.OnInit();
		
		SyberiaPPEffects.Init();
		
		if (!m_AdditionHudRootWidget)
		{
			m_AdditionHudRootWidget = GetGame().GetWorkspace().CreateWidgets("SyberiaScripts/layout/AdditionalHud.layout");
			m_AdditionHudRootWidget.Show(false);
			
			if ( !m_SyberiaAdditionalHud )
			{
				ref Widget actionBlocker = m_AdditionHudRootWidget.FindAnyWidget("ActionBlocker");
				m_AdditionHudRootWidget.RemoveChild(actionBlocker);
				
				ref MultilineTextWidget screenInfoWidget = MultilineTextWidget.Cast( m_AdditionHudRootWidget.FindAnyWidget("ScreenInfoWidget") );
				m_AdditionHudRootWidget.RemoveChild(screenInfoWidget);
				
				m_SyberiaAdditionalHud = new SyberiaAdditionalHud(m_HudRootWidget, actionBlocker, screenInfoWidget);
				m_SyberiaAdditionalHud.Init();		
			}
			
			if (m_Hud)
			{
				ref Widget notifications = m_AdditionHudRootWidget.FindAnyWidget("Notifications");				
				m_Hud.InitNotifierWidget(NTFKEY_SLEEPING, notifications, "Sleeping", 1);
				m_Hud.InitNotifierWidget(NTFKEY_MINDSTATE, notifications, "MindState", 2);
				
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
				m_Hud.InitBadgetWidget(NTFKEY_INFLUENZA, badgets, "Influenza");
				m_Hud.InitBadgetWidget(NTFKEY_STOMATCHPOISONING, badgets, "Stomatchpoison");
			}
		}
		
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_SCREEN_MESSAGE, this, "OnScreenMessageRpc");
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
				
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (player)
		{
			SyberiaPPEffects.Update(timeslice);
			
			UIScriptedMenu menu = m_UIManager.GetMenu();
			
			if (m_SyberiaAdditionalHud && m_LifeState == EPlayerStates.ALIVE && !player.IsUnconscious() )
			{
				m_SyberiaAdditionalHud.Refresh(timeslice);	
			}
			
			if (m_Hud)
			{
				m_Hud.DisplayNotifier(NTFKEY_SLEEPING, player.GetSleepingTendency(), player.GetSleepingState());
				m_Hud.DisplayNotifier(NTFKEY_MINDSTATE, player.GetMindStateTendency(), player.GetMindState());
				
				m_Hud.DisplayBadge(NTFKEY_BULLETHIT, player.m_bulletHits);
				m_Hud.DisplayBadge(NTFKEY_KNIFEHIT, player.m_knifeHits);
				m_Hud.DisplayBadge(NTFKEY_HEMATOMA, player.m_hematomaHits);
				m_Hud.DisplayBadge(NTFKEY_VISCERADMG, player.m_visceraHit);
				m_Hud.DisplayBadge(NTFKEY_CONCUSSION, player.m_concussionHit);
				m_Hud.DisplayBadge(NTFKEY_PAIN, player.GetCurrentPainLevel());
				m_Hud.DisplayBadge(NTFKEY_PAINKILLER, player.m_painkillerEffect);
				m_Hud.DisplayBadge(NTFKEY_ANTIBIOTIC, player.m_antibioticsLevel);
				m_Hud.DisplayBadge(NTFKEY_STOMATCHHEAL, player.m_stomatchhealLevel);
				m_Hud.DisplayBadge(NTFKEY_SEPSIS, player.HasVisibleSepsis());
				m_Hud.DisplayBadge(NTFKEY_ZVIRUS, player.HasVisibleZVirus());
				m_Hud.DisplayBadge(NTFKEY_BANDAGE1, player.m_bulletBandage1 + player.m_knifeBandage1);
				m_Hud.DisplayBadge(NTFKEY_BANDAGE2, player.m_bulletBandage2 + player.m_knifeBandage2);
				m_Hud.DisplayBadge(NTFKEY_HEMOSTATIC, player.m_bloodHemostaticEffect);
				m_Hud.DisplayBadge(NTFKEY_HEMATOPOIESIS, player.m_hematopoiesisEffect);
				m_Hud.DisplayBadge(NTFKEY_USESALVE, player.m_salveEffect);
				m_Hud.DisplayBadge(NTFKEY_ADRENALIN, player.m_adrenalinEffect);
				m_Hud.DisplayBadge(NTFKEY_OVERDOSED, (int)Math.Floor(Math.Clamp(player.m_overdosedValue, 0, 3)));
				m_Hud.DisplayBadge(NTFKEY_INFLUENZA, player.m_influenzaLevel);
				m_Hud.DisplayBadge(NTFKEY_STOMATCHPOISONING, player.m_stomatchpoisonLevel);
			}
						
			OnUpdateAdvMedicineGUI(player, timeslice);
			OnUpdateMindstateGUI(player, timeslice);
		}
		
		if (!player || !player.IsAlive())
		{
			if (m_HudRootWidget)
			{
				m_HudRootWidget.Show(false);
			}
		}
	}
	
	private void OnUpdateAdvMedicineGUI(PlayerBase player, float deltaTime)
	{		
		float overdosedEffect = Math.Clamp((player.m_overdosedValue - 1.0) * 0.1, 0, 0.3);
		SyberiaPPEffects.SetOverdosedEffect(overdosedEffect);
		
		float painEffect = Math.Clamp(player.GetCurrentPainLevel() * 0.1, 0, 0.3);
		SyberiaPPEffects.SetPainEffect(painEffect);
		
		float concussionEffect = Math.Clamp(((int)player.m_concussionHit) * 0.1, 0, 0.1);
		SyberiaPPEffects.SetConcussionEffect(concussionEffect);
		
		SyberiaSleepingLevel sleepingLevel = player.GetSleepingProcessLevel();
		float sleepingValue = Math.Clamp((int)sleepingLevel, 0, 1);
		SyberiaPPEffects.SetSleepingEffect(sleepingValue);
		
		if (sleepingLevel == SyberiaSleepingLevel.SYBSL_ENERGED)
		{
			m_SyberiaAdditionalHud.ShowScreenMessage("#syb_nosleep_energed", 2);
		}
		else if (sleepingLevel == SyberiaSleepingLevel.SYBSL_SICK)
		{
			m_SyberiaAdditionalHud.ShowScreenMessage("#syb_nosleep_sick", 2);
		}
		else if (sleepingLevel == SyberiaSleepingLevel.SYBSL_COLD)
		{
			m_SyberiaAdditionalHud.ShowScreenMessage("#syb_nosleep_cold", 2);
		}
		else if (sleepingLevel == SyberiaSleepingLevel.SYBSL_HOT)
		{
			m_SyberiaAdditionalHud.ShowScreenMessage("#syb_nosleep_hot", 2);
		}
	}
	
	private void OnUpdateMindstateGUI(PlayerBase player, float deltaTime)
	{
		if (player.GetMindStateValue() < GetSyberiaConfig().m_mindstateLevel4)
		{
			if (Math.RandomFloat01() < deltaTime * 0.05)
			{
				int action = Math.RandomInt(0, 10);
				if (action == 0)
				{
					Weapon_Base weapon;
					WeaponEventBase weapon_event = new WeaponEventTrigger;
					if ( Weapon_Base.CastTo(weapon, player.GetItemInHands()) )
					{
						weapon.ProcessWeaponEvent(weapon_event);
					}
				}
				else
				{
					int emotesCount = player.GetEmoteManager().m_NameEmoteMap.Count();
					int emoteId = Math.RandomInt(0, emotesCount);
					int emoteKey = player.GetEmoteManager().m_NameEmoteMap.GetKey(emoteId);
					if (player.GetEmoteManager().CanPlayEmote(emoteKey))
					{
						player.GetEmoteManager().CreateEmoteCBFromMenu(emoteKey);
					}
				}				 
			}
		}
	}
	
	override int GetRespawnModeClient()
	{
		return GameConstants.RESPAWN_MODE_RANDOM;
	}
	
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if (key == KeyCode.KC_LMENU)
		{
			m_isAltPressed = true;
		}
	}
	
	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		
		if (key == KeyCode.KC_LMENU)
		{
			m_isAltPressed = false;
		}
		
		PluginGearPDA pluginGearPDA;
		if ( key == KeyCode.KC_ESCAPE )
		{	
			Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
			if (pluginGearPDA && pluginGearPDA.IsOpen())
			{
				pluginGearPDA.Close();
			}
		}
		else if ( key == KeyCode.KC_RETURN )
		{
			Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
			if (pluginGearPDA && pluginGearPDA.IsOpen())
			{
				pluginGearPDA.m_GearPDAMenu.m_externalSendEvent = true;
			}
		}
		
		PluginAdminTool pluginAdminTool;
		if ( m_isAltPressed && key == KeyCode.KC_INSERT )
		{			
			Class.CastTo(pluginAdminTool, GetPlugin(PluginAdminTool));
			if (pluginAdminTool && !pluginAdminTool.IsOpen())
			{
				pluginAdminTool.Open();
			}
		}
		else if ( key == KeyCode.KC_ESCAPE )
		{	
			Class.CastTo(pluginAdminTool, GetPlugin(PluginAdminTool));
			if (pluginAdminTool && pluginAdminTool.IsOpen())
			{
				pluginAdminTool.Close();
			}
		}
		
		DayZPlayerImplement playerClient = DayZPlayerImplement.Cast(GetGame().GetPlayer());
		if (key == KeyCode.KC_ESCAPE && playerClient && playerClient.m_skillsMenu && playerClient.m_skillsMenu.m_active)
		{
			playerClient.m_skillsMenu.m_active = false;
		}
	}

	protected void OnScreenMessageRpc(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		if (!m_SyberiaAdditionalHud) return;
		
		Param1<string> clientData;
       	if ( !ctx.Read( clientData ) ) return;	
		
		ShowScreenMessage(clientData.param1, 8);
	}
	
	override void ShowScreenMessage(string message, float time)
	{
		if (m_SyberiaAdditionalHud)
		{
			m_SyberiaAdditionalHud.ShowScreenMessage(message, time);
		}
	}
};