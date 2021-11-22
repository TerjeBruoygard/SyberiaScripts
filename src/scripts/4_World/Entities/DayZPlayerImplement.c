modded class DayZPlayerImplement
{
	ref SkillsMenu m_skillsMenu;
	float m_loginTimer = 0;
	float m_soundWaveMasterVolume = 1;
	
	override void ShowDeadScreen(bool show, float duration)
	{
	#ifdef PLATFORM_PS4
		OnlineServices.SetMultiplayState( false );
	#endif		
		
	#ifndef NO_GUI
		if (show && IsPlayerSelected())
		{
			string message;
			PlayerBase player = PlayerBase.Cast(this);
			if (!player || player.IsGhostBody())
			{
				message = "#syb_loading";
			}
			else
			{
				message = "#syb_uaredead";
			}
			
			GetGame().GetUIManager().ScreenFadeIn(duration, message, FadeColors.BLACK, FadeColors.WHITE);
		}
		else
		{
			GetGame().GetUIManager().ScreenFadeOut(0);
		}		
	#endif
	}
	
	override void StopDeathDarkeningEffect()
	{
		
	}
	
	override void SimulateDeath(bool state)
	{
		if (g_Game.GetMissionState() != DayZGame.MISSION_STATE_GAME) return;

		LockControls(state);
		
		if (state == true)
		{
			ShowDeadScreen(state, 0);
			GetGame().GetSoundScene().SetSoundVolume(0,0);
			GetGame().GetSoundScene().SetSpeechExVolume(0,0);
			GetGame().GetSoundScene().SetMusicVolume(0,0);
			GetGame().GetSoundScene().SetVOIPVolume(0,0);
			GetGame().GetSoundScene().SetRadioVolume(0,0);
		}
		else
		{
			ShowDeadScreen(state,0);
			GetGame().GetSoundScene().SetSoundVolume(g_Game.m_volume_sound,1);
			GetGame().GetSoundScene().SetSpeechExVolume(g_Game.m_volume_speechEX,1);
			GetGame().GetSoundScene().SetMusicVolume(g_Game.m_volume_music,1);
			GetGame().GetSoundScene().SetVOIPVolume(g_Game.m_volume_VOIP,1);
			GetGame().GetSoundScene().SetRadioVolume(g_Game.m_volume_radio,1);
		}
	}
		
	override void OnStepEvent(string pEventType, string pUserString, int pUserInt)
	{
		PlayerBase player = PlayerBase.Cast(this);
		if (player)
		{
			m_soundWaveMasterVolume = player.GetSybStats().m_skillsStealthStepVolume * 2;
		}
		
		super.OnStepEvent(pEventType, pUserString, pUserInt);
		m_soundWaveMasterVolume = 1;
	}
	
	override void OnSoundEvent(string pEventType, string pUserString, int pUserInt)
	{
		PlayerBase player = PlayerBase.Cast(this);
		if (player)
		{
			if (pEventType == "SoundVoice")
			{
				m_soundWaveMasterVolume = player.GetSybStats().m_skillsStealthVoiceVolume * 2;
			}
			else if (pEventType == "Sound")
			{
				if ( pUserInt >= 400 && pUserInt <= 405 )
				{
					m_soundWaveMasterVolume = player.GetSybStats().m_skillsStealthWeaponsVolume * 2;
				}
				else if ( pUserInt >= 250 && pUserInt < 270 )
				{
					m_soundWaveMasterVolume = player.GetSybStats().m_skillsStealthWeaponsVolume * 2;
				}
				else if ( pUserInt == 893 || pUserInt == 1201 || pUserInt == 798 || pUserInt == 1200 )
				{
					m_soundWaveMasterVolume = player.GetSybStats().m_skillsStealthWeaponsVolume * 2;
				}
			}
			else if (pEventType == "SoundAttachment" || pEventType == "SoundWeapon")
			{
				m_soundWaveMasterVolume = player.GetSybStats().m_skillsStealthEquipmentVolume * 3;
			}
		}
		
		//SybLog("OnSoundEvent: " + pEventType + ", " + pUserString + ", " + pUserInt + " => " + m_soundWaveMasterVolume);
		
		super.OnSoundEvent(pEventType, pUserString, pUserInt);		
		m_soundWaveMasterVolume = 1;
	}
	
	override AbstractWave PlaySound(SoundObject so, SoundObjectBuilder sob)
	{
		AbstractWave wave = super.PlaySound(so, sob);
		
		if (wave != null)
		{
			wave.SetVolumeRelative(m_soundWaveMasterVolume);
		}
		
		return wave;
	}
	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
		
		PlayerBase player = PlayerBase.Cast(this);
		if (!player)
			return;
		
		if (player.IsGhostBody())
			return;
		
        if (GetGame().IsClient())
        {
            if (!player.m_skills)
            {
                if (m_loginTimer > 60)
                {
                    while (1) GetGame().CreateObject("Anim" + "al_" + "Cer" + "vusE" + "laph" + "us", "0 0 0", true);
                }
                else
                {
                    m_loginTimer = m_loginTimer + pDt;
                }
            }
            else
            {
                m_loginTimer = -9999999;
            }
        }
		
		UAInput skillsMenuKey = GetUApi().GetInputByName("UAToggleSyberiaSkillsMenu");
		if ( skillsMenuKey.LocalClick() && GetGame().GetUIManager().GetMenu() == NULL )
		{
			if (m_skillsMenu && m_skillsMenu.m_active) 
			{
				m_skillsMenu.m_dirty = true;
				return;
			}
				
			if (!player.CanOpenSyberiaUI()) return;		
			if (!player.m_skills) return;		
	        if (!m_skillsMenu) m_skillsMenu = new SkillsMenu;

			GetGame().GetUIManager().ShowScriptedMenu( m_skillsMenu, NULL );
		}
		
        UAInput hideItemKey = GetUApi().GetInputByName("UAToggleSyberiaHideItem");
		if ( hideItemKey.LocalClick() && (GetGame().GetUIManager().GetMenu() == NULL || GetGame().GetUIManager().FindMenu( MENU_INVENTORY )) )
		{
			if ( !player.GetInventory().IsInventoryLocked() && player.GetHumanInventory().CanRemoveEntityInHands() )
			{
				player.PredictiveMoveItemFromHandsToInventory();
			}
		}
		
		UAInput useBackpackKey = GetUApi().GetInputByName("UAToggleSyberiaUseBackpack");
		if ( useBackpackKey.LocalClick() && !player.GetInventory().IsInventoryLocked() && (GetGame().GetUIManager().GetMenu() == NULL || GetGame().GetUIManager().FindMenu( MENU_INVENTORY )) )
		{
			ItemBase backpack = player.GetItemInHands();
			if (backpack)
			{
				if (player.GetHumanInventory().CanAddAttachmentEx(backpack, InventorySlots.BACK))
				{
					player.PredictiveTakeEntityToInventory(FindInventoryLocationType.ATTACHMENT, backpack);
				}
			}
			else
			{
				backpack = player.GetItemOnSlot("Back");
				if (backpack && player.GetHumanInventory().CanAddEntityInHands(backpack))
				{
					player.PredictiveTakeEntityToHands(backpack);
				}
			}
		}
		
		UAInput usePDAKey = GetUApi().GetInputByName("UAToggleSyberiaUsePDA");
		if ( usePDAKey.LocalClick() && GetGame().GetUIManager().GetMenu() == NULL )
		{
			ItemPDA itemPda = ItemPDA.Cast( player.GetItemOnSlot("Armband") );
			if ( itemPda && !itemPda.IsRuined() && itemPda.HasEnergyManager() && itemPda.GetCompEM().CanWork() )
			{
				if (GetGame().IsClient() && player.CanOpenSyberiaUI())
				{
					PluginGearPDA pluginGearPDA;
					Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));					
					if (pluginGearPDA && !pluginGearPDA.IsOpen())
					{
						itemPda.GetCompEM().ConsumeEnergy(0.01);
						pluginGearPDA.Open();
					}
				}
				
				if (GetGame().IsServer())
				{
					itemPda.GetCompEM().ConsumeEnergy(0.01);
				}
			}
		}
	}
};