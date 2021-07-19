modded class DayZPlayerImplement
{
	ref SkillsMenu m_skillsMenu;
	float m_loginTimer = 0;
	
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
	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
		
		PlayerBase player = PlayerBase.Cast(this);
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
		if ( skillsMenuKey.LocalClick() )
		{
			if (m_skillsMenu && m_skillsMenu.m_active) 
			{
				m_skillsMenu.m_dirty = true;
				return;
			}
				
			if (GetGame().GetUIManager().GetMenu() != NULL) return;
			if (!player.CanOpenSyberiaUI()) return;		
			if (!player.m_skills) return;		
	        if (!m_skillsMenu) m_skillsMenu = new SkillsMenu;

			GetGame().GetUIManager().ShowScriptedMenu( m_skillsMenu, NULL );
		}
		
        UAInput hideItemKey = GetUApi().GetInputByName("UAToggleSyberiaHideItem");
		if ( hideItemKey.LocalClick() )
		{
			if ( !player.GetInventory().IsInventoryLocked() && player.GetHumanInventory().CanRemoveEntityInHands() )
			{
				player.PredictiveMoveItemFromHandsToInventory();
			}
		}
	}
};