modded class MissionGameplay
{
	private ref WatermarkHandler m_watermarkHandler;
	ref Widget m_AdditionHudRootWidget = null;
	ref SyberiaAdditionalHud m_SyberiaAdditionalHud = null;
	ref array<int> m_pressedKeys;
	ref array<ref ToxicZoneView> m_toxicZonesView;
	float m_toxicZoneUpdateTimer;
	bool m_isPveIntruderLast;
	
	override void OnMissionStart()
	{
		SybLog("MissionGameplay OnMissionStart");
		super.OnMissionStart();
		m_pressedKeys = new array<int>;
		m_toxicZoneUpdateTimer = 0;
		m_isPveIntruderLast = false;
		
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_CONCUSSION).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_OVERDOSE).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_PAIN).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_PSI).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_RADIATION).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_SLEEPING).Start();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_CATEYES).Start();
	}
	
	override void OnMissionFinish()
	{
		SybLog("MissionGameplay OnMissionStart");
		super.OnMissionFinish();
		
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_CONCUSSION).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_OVERDOSE).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_PAIN).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_PSI).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_RADIATION).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_SLEEPING).Stop();
		PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_CATEYES).Stop();
		
		delete m_AdditionHudRootWidget;
		delete m_SyberiaAdditionalHud;
		delete m_pressedKeys;
		
		if (m_toxicZonesView)
		{
			foreach (ref ToxicZoneView dtz : m_toxicZonesView)
			{
				delete dtz;
			}
			delete m_toxicZonesView;
		}
	}
	
	override void OnInit()
	{
		super.OnInit();
		
		m_watermarkHandler = new WatermarkHandler();
		
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
				m_Hud.InitBadgetWidget(NTFKEY_RADIATIONSICKNESS, badgets, "RadiationSickness");
				m_Hud.InitBadgetWidget(NTFKEY_RADIOPROTECTION, badgets, "Radioprotection");
				m_Hud.InitBadgetWidget(NTFKEY_DISINFECTED, badgets, "Disinfected");
				m_Hud.InitBadgetWidget(NTFKEY_ANTIDEPRESANT, badgets, "Antidepresant");
			}
		}
		
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_SCREEN_MESSAGE, this, "OnScreenMessageRpc");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_SYNC_TOXIC_ZONES, this, "OnSyncToxicZone");
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
				
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (player && player.GetSybStats())
		{
			if (m_toxicZonesView)
			{
				m_toxicZoneUpdateTimer = m_toxicZoneUpdateTimer - timeslice;
				if (m_toxicZoneUpdateTimer <= 0.0)
				{
					m_toxicZoneUpdateTimer = 5.0;
					foreach (ref ToxicZoneView tzv : m_toxicZonesView)
					{
						tzv.Update(player);
					}
				}
			}
			
			UIScriptedMenu menu = m_UIManager.GetMenu();
			
			if (m_SyberiaAdditionalHud && m_LifeState == EPlayerStates.ALIVE && !player.IsUnconscious() )
			{
				m_SyberiaAdditionalHud.Refresh(timeslice);	
			}
			
			if (m_Hud)
			{
				m_Hud.DisplayNotifier(NTFKEY_SLEEPING, player.GetSleepingTendency(), player.GetSleepingState());
				m_Hud.DisplayNotifier(NTFKEY_MINDSTATE, player.GetMindStateTendency(), player.GetMindState());
				
				m_Hud.DisplayBadge(NTFKEY_BULLETHIT, player.GetSybStats().m_bulletHits);
				m_Hud.DisplayBadge(NTFKEY_KNIFEHIT, player.GetSybStats().m_knifeHits);
				m_Hud.DisplayBadge(NTFKEY_HEMATOMA, player.GetSybStats().m_hematomaHits);
				m_Hud.DisplayBadge(NTFKEY_VISCERADMG, player.GetSybStats().m_visceraHit);
				m_Hud.DisplayBadge(NTFKEY_CONCUSSION, player.GetSybStats().m_concussionHit);
				m_Hud.DisplayBadge(NTFKEY_PAIN, player.GetCurrentPainLevel());
				m_Hud.DisplayBadge(NTFKEY_PAINKILLER, player.GetSybStats().m_painkillerEffect);
				m_Hud.DisplayBadge(NTFKEY_ANTIBIOTIC, player.GetSybStats().m_antibioticsLevel);
				m_Hud.DisplayBadge(NTFKEY_STOMATCHHEAL, player.GetSybStats().m_stomatchhealLevel);
				m_Hud.DisplayBadge(NTFKEY_SEPSIS, player.HasVisibleSepsis());
				m_Hud.DisplayBadge(NTFKEY_ZVIRUS, player.HasVisibleZVirus());
				m_Hud.DisplayBadge(NTFKEY_BANDAGE1, player.GetSybStats().m_bulletBandage1 + player.GetSybStats().m_knifeBandage1);
				m_Hud.DisplayBadge(NTFKEY_BANDAGE2, player.GetSybStats().m_bulletBandage2 + player.GetSybStats().m_knifeBandage2);
				m_Hud.DisplayBadge(NTFKEY_HEMOSTATIC, player.GetSybStats().m_bloodHemostaticEffect);
				m_Hud.DisplayBadge(NTFKEY_HEMATOPOIESIS, player.GetSybStats().m_hematopoiesisEffect);
				m_Hud.DisplayBadge(NTFKEY_USESALVE, player.GetSybStats().m_salveEffect);
				m_Hud.DisplayBadge(NTFKEY_ADRENALIN, player.GetSybStats().m_adrenalinEffect);
				m_Hud.DisplayBadge(NTFKEY_OVERDOSED, player.GetSybStats().m_overdosedLevel);
				m_Hud.DisplayBadge(NTFKEY_INFLUENZA, player.GetSybStats().m_influenzaLevel);
				m_Hud.DisplayBadge(NTFKEY_STOMATCHPOISONING, player.GetSybStats().m_stomatchpoisonLevel);
				m_Hud.DisplayBadge(NTFKEY_RADIATIONSICKNESS, player.GetRadiationSicknessLevel());
				m_Hud.DisplayBadge(NTFKEY_RADIOPROTECTION, player.GetRadioprotectionLevel());
				m_Hud.DisplayBadge(NTFKEY_DISINFECTED, player.HasDisinfectedHands());
				m_Hud.DisplayBadge(NTFKEY_ANTIDEPRESANT, player.GetAntidepresantLevel());
			}
						
			OnUpdateAdvMedicineGUI(player, timeslice);
			OnUpdateMindstateGUI(player, timeslice);
			OnUpdatePveIntruderState(player, timeslice);
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
		float cateyesValue = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STEALTH_CAT_VISSION, 0, 0);
		PPERequester_CatEyes.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_CATEYES)).SetValue(cateyesValue);	
		
		float overdosedEffect = Math.Clamp(((float)player.GetSybStats().m_overdosedLevel - 0.5) * 0.1, 0, 0.3);
		PPERequester_SybOverdose.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_OVERDOSE)).SetOverdosedEffect(overdosedEffect);
		
		float painEffect = Math.Clamp(player.GetCurrentPainLevel() * 0.1, 0, 0.3);
		PPERequester_SybPain.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_PAIN)).SetPainEffect(painEffect);	
		PPERequester_SybRadiation.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_RADIATION)).SetRadiationEffect(player.GetRadiationSicknessLevel());
		
		float concussionEffect = Math.Clamp(((int)player.GetSybStats().m_concussionHit) * 0.1, 0, 0.1);
		PPERequester_SybConcussion.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_CONCUSSION)).SetConcussionEffect(concussionEffect);
		
		SyberiaSleepingLevel sleepingLevel = player.GetSleepingProcessLevel();
		float sleepingValue = Math.Clamp((int)sleepingLevel, 0, 1);
		if (sleepingValue < 0.8 && player.GetSleepingValue() < 1)
		{
			sleepingValue = 0.8;
		}
		
		PPERequester_SybSleeping.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_SLEEPING)).SetSleepingEffect(sleepingValue);	
		PPERequester_SybPSI.Cast(PPERequesterBank.GetRequester(PPERequesterBank.REQ_SYB_PSI)).SetPsiEffect(player.IsInsidePsiZone());
		
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
				int action = Math.RandomInt(0, 8);
				if (action == 0)
				{
					Weapon_Base weapon;
					WeaponEventBase weapon_event = new WeaponEventTrigger;
					if ( Weapon_Base.CastTo(weapon, player.GetItemInHands()) )
					{
						weapon.ProcessWeaponEvent(weapon_event);
					}
				}
				else if (action == 1)
				{
					if (player.GetEmoteManager().CanPlayEmote(EmoteConstants.ID_EMOTE_SUICIDE))
					{
						player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_SUICIDE);
					}
				}
				else
				{
					int emotesCount = player.GetEmoteManager().GetTotalEmotesCount();
					int emoteId = Math.RandomInt(0, emotesCount);
					int emoteKey = player.GetEmoteManager().GetEmoteKeyById(emoteId);
					if (player.GetEmoteManager().CanPlayEmote(emoteKey))
					{
						player.GetEmoteManager().CreateEmoteCBFromMenu(emoteKey);
					}
				}				 
			}
		}
	}
	
	private void OnUpdatePveIntruderState(PlayerBase player, float deltaTime)
	{
		if (player.GetSybStats().m_isPveIntruder && !m_isPveIntruderLast)
		{
			m_isPveIntruderLast = true;
			ShowScreenMessage("#syb_pve_intrude", 10);
		}
		
		if (!player.GetSybStats().m_isPveIntruder && m_isPveIntruderLast)
		{
			m_isPveIntruderLast = false;
		}
	}
	
	override int GetRespawnModeClient()
	{
		return GameConstants.RESPAWN_MODE_RANDOM;
	}
	
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if (m_pressedKeys.Find(key) == -1)
		{
			m_pressedKeys.Insert(key);
		}
		
		PluginAdminTool pluginAdminTool;
		Class.CastTo(pluginAdminTool, GetPlugin(PluginAdminTool));
		if ( pluginAdminTool.m_adminPermissions && pluginAdminTool.m_freeCam )
		{
			pluginAdminTool.m_freeCam.HandleKey(key, true);
		}
	}
	
	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		
		int keyIndex = m_pressedKeys.Find(key);
		if (keyIndex != -1)
		{
			m_pressedKeys.Remove(keyIndex);
			OnKeyClicked(key);
		}
		
		PluginAdminTool pluginAdminTool;
		Class.CastTo(pluginAdminTool, GetPlugin(PluginAdminTool));
		if (pluginAdminTool)
		{
			if ( pluginAdminTool.m_adminPermissions && pluginAdminTool.m_freeCam )
			{
				pluginAdminTool.m_freeCam.HandleKey(key, false);
			}
		}
	}
	
	void OnKeyClicked(int key)
	{
		bool m_isAltPressed = m_pressedKeys.Find(KeyCode.KC_LMENU) != -1;
		
		PluginGearPDA pluginGearPDA;
		PluginSyberiaLogin pluginSyberiaLogin;
		PluginTrader pluginSyberiaTrader;
		if ( key == KeyCode.KC_ESCAPE )
		{	
			Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
			if (pluginGearPDA && pluginGearPDA.IsOpen())
			{
				pluginGearPDA.Close();
			}
			
			Class.CastTo(pluginSyberiaLogin, GetPlugin(PluginSyberiaLogin));
			if (pluginSyberiaLogin)
			{
				pluginSyberiaLogin.CloseStethoscopeMenu();
				pluginSyberiaLogin.CloseHomebookMenu();
			}
			
			Class.CastTo(pluginSyberiaTrader, GetPlugin(PluginTrader));
			if (pluginSyberiaTrader)
			{
				pluginSyberiaTrader.CloseTraderMenu();
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
		Class.CastTo(pluginAdminTool, GetPlugin(PluginAdminTool));
		if (pluginAdminTool)
		{
			if ( m_isAltPressed && key == KeyCode.KC_GRAVE )
			{			
				if (!pluginAdminTool.IsOpen())
				{
					pluginAdminTool.Open();
				}
			}
			else if ( m_isAltPressed && key == KeyCode.KC_T )
			{	
				if (pluginAdminTool.m_adminPermissions)
				{
					pluginAdminTool.TeleportToCursor();
				}
			}
			else if ( key == KeyCode.KC_ESCAPE )
			{	
				if (pluginAdminTool.IsOpen())
				{
					pluginAdminTool.Close();
				}
			}
		}
		
		DayZPlayerImplement playerClient = DayZPlayerImplement.Cast(GetGame().GetPlayer());
		if (key == KeyCode.KC_ESCAPE && playerClient && playerClient.m_skillsMenu && playerClient.m_skillsMenu.m_active)
		{
			playerClient.m_skillsMenu.m_active = false;
		}
	}

	protected void OnScreenMessageRpc(ParamsReadContext ctx, PlayerIdentity sender)
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
	
	override void Pause()
	{
		super.Pause();

		UIScriptedMenu ingameMenu = GetGame().GetUIManager().GetMenu();
		if (ingameMenu && ingameMenu.GetID() == MENU_INGAME)
		{
			ref Widget watermarkWidget = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/WatermarkInGame.layout" );		
			ref Widget watermarkBase = watermarkWidget.FindAnyWidget( "WatermarkBase" );
			ref Widget watermarkBtn = watermarkBase.FindAnyWidget( "WatermarkActionBtn" );
			TextWidget.Cast( watermarkBase.FindAnyWidget( "WatermarkTextWidget5" ) ).SetText(Syberia_Version);
			m_WidgetEventHandler.RegisterOnClick(watermarkBtn, m_watermarkHandler, "OnWatermarkClick");
			watermarkWidget.RemoveChild(watermarkBase);
			ingameMenu.GetLayoutRoot().AddChild(watermarkBase, true);
			delete watermarkWidget;
		}
	}
	
	void OnSyncToxicZone(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<ref array<ref ToxicZone>> clientData;
		if ( !ctx.Read( clientData ) ) return;
		
		if (m_toxicZonesView)
		{
			foreach (ref ToxicZoneView zoneToDelete : m_toxicZonesView)
			{
				delete zoneToDelete;
			}
			delete m_toxicZonesView;
		}
		
		ref array<ref ToxicZone> toxicZonesInfo = clientData.param1;
		m_toxicZonesView = new array<ref ToxicZoneView>;
		if (toxicZonesInfo)
		{
			foreach (ref ToxicZone zone : toxicZonesInfo)
			{
				m_toxicZonesView.Insert(new ToxicZoneView(zone.m_position, zone.m_radius));
			}
		}
	}
};