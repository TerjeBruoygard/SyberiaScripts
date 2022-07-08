class PluginSyberiaLogin extends PluginBase
{
	autoptr ScreenBase m_screenBase;
	bool m_isRespawnCommited = false;
	
	void PluginSyberiaLogin()
	{

	}
	
	void ~PluginSyberiaLogin()
	{
		if (m_screenBase) m_screenBase.Close();
	}
	
	override void OnInit()
	{
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_RESPAWN_SCREEN_OPEN, this, "RespawnScreen_Open"); 
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_NEWCHAR_SCREEN_OPEN, this, "NewcharScreen_Open");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_EQUIP_SCREEN_OPEN, this, "EquipScreen_Open");
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);

		PlayerBase player = GetGame().GetPlayer();
		if (!player) return;
		
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
		
		Param3<string, int, int> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		
		if (m_screenBase) m_screenBase.Close();
		
		m_screenBase = new ScreenRespawn(clientData.param1, clientData.param2, clientData.param3);
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
		
		m_screenBase = new ScreenEquip();
	}
};