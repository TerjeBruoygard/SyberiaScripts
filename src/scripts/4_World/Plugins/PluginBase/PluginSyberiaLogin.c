class PluginSyberiaLogin extends PluginBase
{
	autoptr ScreenBase m_screenBase;
	bool m_isRespawnCommited = false;
	
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
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);

		PlayerBase player = GetGame().GetPlayer();
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
			if (player.m_skills)
			{ 
				delete player.m_skills;
			}
			
			player.m_skills = clientData.param1;
			
			DayZPlayerImplement playerImpl = DayZPlayerImplement.Cast(player);
			if (playerImpl && playerImpl.m_skillsMenu && playerImpl.m_skillsMenu.m_active)
			{
				playerImpl.m_skillsMenu.m_refresh = true;
				playerImpl.m_skillsMenu.m_dirty = true;
			}
		}
	}
};