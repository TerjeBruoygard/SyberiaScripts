class PluginSyberiaLogin extends PluginBase
{
	autoptr ScreenRespawn screenRespawnMenu;
	
	void PluginSyberiaLogin()
	{

	}
	
	void ~PluginSyberiaLogin()
	{

	}
	
	override void OnInit()
	{
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_RESPAWN_SCREEN_OPEN, this, "RespawnScreen_Open"); 
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_NEWCHAR_SCREEN_OPEN, this, "NewcharScreen_Open");
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);
		
		if (screenRespawnMenu)
		{
			if (!screenRespawnMenu.m_visible)
			{
				GetGame().GetUIManager().CloseAll();
				GetGame().GetUIManager().ShowScriptedMenu( screenRespawnMenu, NULL );
				SybLog("PluginSyberiaLogin force enable menu.");
			}
		}
	}
	
	void RespawnScreen_Open(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   
		SybLog("PluginSyberiaLogin SYBRPC_RESPAWN_SCREEN_OPEN RPC Received.");
		
		Param3<string, int, int> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		
		screenRespawnMenu = new ScreenRespawn(clientData.param1, clientData.param2, clientData.param3);
		screenRespawnMenu.Init();
	}
	
	void NewcharScreen_Open(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   
		SybLog("PluginSyberiaLogin SYBRPC_NEWCHAR_SCREEN_OPEN RPC Received.");
		
		Param2<string, int> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		
		screenRespawnMenu = new ScreenNewchar(clientData.param1, clientData.param2);
		screenRespawnMenu.Init();
	}
};