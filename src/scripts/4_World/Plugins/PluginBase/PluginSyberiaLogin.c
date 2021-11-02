class PluginSyberiaLogin extends PluginBase
{
	autoptr ScreenBase m_screenBase;
	bool m_isRespawnCommited = false;
	
	autoptr StethoscopeMenu m_stethoscopeMenu;
	
	void ~PluginSyberiaLogin()
	{
		if (m_screenBase) m_screenBase.Close();
	}
	
	override void OnInit()
	{
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_RESPAWN_SCREEN_OPEN, this, "RespawnScreen_Open"); 
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_NEWCHAR_SCREEN_OPEN, this, "NewcharScreen_Open");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_EQUIP_SCREEN_OPEN, this, "EquipScreen_Open");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_CREATENEWCHAR_ERROR, this, "NewcharScreen_Error");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_SKILLS_UPDATE, this, "OnSkillsUpdate");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_STETHOSCOPE_INSPECT, this, "OnStethoscopeInspect");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_CURRENT_ZONE_SYNC, this, "OnCurrentZoneSync");
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (!player) 
		{
			return;
		}
				
		if (player.IsGhostBody())
		{
			if (!player.IsAlive() && !m_isRespawnCommited)
			{
				if (m_screenBase) m_screenBase.Close();
				
				m_screenBase = new ScreenBlack();
				GetGame().GetUIManager().CloseAll();
				GetGame().GetUIManager().ShowScriptedMenu( m_screenBase, NULL );
				
				GetGame().RespawnPlayer();
				m_isRespawnCommited = true;
				
				SybLog("Respawn player");
			}
			else if (player.IsAlive() && m_screenBase)
			{
				if (!m_screenBase.m_isShown)
				{
					SybLog("ShowScriptedMenu: " + m_screenBase);
					GetGame().GetUIManager().CloseAll();
					GetGame().GetUIManager().ShowScriptedMenu( m_screenBase, NULL );
					m_isRespawnCommited = false;
				}
			}
		}
		else if (!player.m_skills)
		{
			if (m_screenBase && !m_screenBase.IsInherited(ScreenBlack)) 
			{
				m_screenBase.Close();
			}
			
			if (!m_screenBase)
			{
				m_screenBase = new ScreenBlack();
				GetGame().GetUIManager().CloseAll();
				GetGame().GetUIManager().ShowScriptedMenu( m_screenBase, NULL );
			}
		}
		else
		{
			if (m_screenBase) 
			{
				m_screenBase.Close();
				m_screenBase = null;
				m_isRespawnCommited = false;
			}
		}
	}
	
	void RespawnScreen_Open(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   
		SybLog("PluginSyberiaLogin SYBRPC_RESPAWN_SCREEN_OPEN RPC Received.");
				
		if (m_screenBase) m_screenBase.Close();
		
		Param4<string, int, int, int> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		m_screenBase = new ScreenRespawn(clientData.param1, clientData.param2, clientData.param3, clientData.param4);
	}
	
	void NewcharScreen_Open(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   
		SybLog("PluginSyberiaLogin SYBRPC_NEWCHAR_SCREEN_OPEN RPC Received.");
		
		Param1<ref RpcNewCharContainer> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		
		if (m_screenBase) m_screenBase.Close();
		
		m_screenBase = new ScreenNewchar(clientData.param1);
	}
	
	void EquipScreen_Open(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		SybLog("PluginSyberiaLogin SYBRPC_EQUIP_SCREEN_OPEN RPC Received.");
		
		if (m_screenBase) m_screenBase.Close();
		
		Param1<ref array<ref array<string>>> clientData;
		if ( !ctx.Read( clientData ) ) return;			
		m_screenBase = new ScreenEquip(clientData.param1);
	}
	
	void NewcharScreen_Error(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		SybLog("PluginSyberiaLogin SYBRPC_CREATENEWCHAR_ERROR RPC Received.");
		
		ref ScreenNewchar screenNewChar = ScreenNewchar.Cast(m_screenBase);
		if (screenNewChar)
		{
			screenNewChar.m_isRpcError = true;
		}
	}
	
	void OnSkillsUpdate(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		SybLog("PluginSyberiaLogin SYBRPC_SKILLS_UPDATE RPC Received.");
		
		Param1<ref SkillsContainer> clientData;
		if ( !ctx.Read( clientData ) ) return;	
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());		
		if (player)
		{
			ref SkillsContainer newSkills = clientData.param1;
			int changedSkill = -1;			
			if (player.m_skills)
			{ 
				for (int i = 0; i < SyberiaSkillType.SYBSKILL_TOTALCOUNT; i++)
				{
					if (newSkills.GetSkillValueInt(i) > player.m_skills.GetSkillValueInt(i))
					{
						changedSkill = i;
						break;
					}
				}
				
				delete player.m_skills;
			}
			
			player.m_skills = newSkills;
			
			DayZPlayerImplement playerImpl = player;
			if (playerImpl && playerImpl.m_skillsMenu && playerImpl.m_skillsMenu.m_active)
			{
				playerImpl.m_skillsMenu.m_refresh = true;
				playerImpl.m_skillsMenu.m_dirty = true;
			}
			
			if (changedSkill != -1)
			{
				MissionBaseWorld mission = MissionBaseWorld.Cast( GetGame().GetMission() );
				if (mission)
				{
					string keyName = "<not set>";
					UAInput i1 = GetUApi().GetInputByName("UAToggleSyberiaSkillsMenu");
					GetDayZGame().GetBacklit().HintShow(i1);
					
					i1.SelectAlternative(0); //! select first alternative (which is the primary bind)
					for ( int c = 0; c < i1.BindKeyCount(); c++ )
					{
					  	int _hc = i1.GetBindKey(0);
					  	keyName = GetUApi().GetButtonName(_hc);
					}

					
					string message = "#syb_skill_up_part1 '#syb_skill" + changedSkill + "' #syb_skill_up_part2 " + newSkills.GetSkillValueInt(changedSkill) + ". ";
					message = message + "#syb_skill_up_part3 '" + keyName + "' #syb_skill_up_part4";
					mission.ShowScreenMessage(message, 15 );
				}
			}
		}
	}
	
	void OnStethoscopeInspect(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		Param1<ref ActionStethoscopeInspect_Data> clientData;
		if ( !ctx.Read( clientData ) ) return;	
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());		
		if (player)
		{
			if (m_stethoscopeMenu && m_stethoscopeMenu.m_active)
			{
				m_stethoscopeMenu.m_active = false;
			}
			
			if (GetGame().GetUIManager().GetMenu() != NULL || !player || !player.CanOpenSyberiaUI())
			{
				return;
			}
			
			m_stethoscopeMenu = new StethoscopeMenu(clientData.param1);
			GetGame().GetUIManager().ShowScriptedMenu( m_stethoscopeMenu, NULL );
		}
	}
	
	void CloseStethoscopeMenu()
	{
		if (m_stethoscopeMenu && m_stethoscopeMenu.m_active)
		{
			m_stethoscopeMenu.m_active = false;
		}
	}
	
	void OnCurrentZoneSync(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		Param1<ref array<ref ZoneImplementation>> clientData;
		if ( !ctx.Read( clientData ) ) return;	
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());		
		if (player)
		{
			player.OnZoneChanged(clientData.param1);
		}
	}
};