class PluginSyberiaLogin extends PluginBase
{
	autoptr ScreenBase screenBase;
	
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
		
		if (screenBase)
		{
			if (!screenBase.m_visible)
			{
				GetGame().GetUIManager().CloseAll();
				GetGame().GetUIManager().ShowScriptedMenu( screenBase, NULL );
				SybLog("PluginSyberiaLogin force enable menu.");
			}
		}
	}
	
	void RespawnScreen_Open(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   
		SybLog("PluginSyberiaLogin SYBRPC_RESPAWN_SCREEN_OPEN RPC Received.");
		
		Param3<string, int, int> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		
		if (screenBase) screenBase.Close();
		
		screenBase = new ScreenRespawn(clientData.param1, clientData.param2, clientData.param3);
		screenBase.Init();
	}
	
	void NewcharScreen_Open(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   
		SybLog("PluginSyberiaLogin SYBRPC_NEWCHAR_SCREEN_OPEN RPC Received.");
		
		Param2<string, int> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		
		if (screenBase) screenBase.Close();
		
		screenBase = new ScreenNewchar(clientData.param1, clientData.param2);
		screenBase.Init();
	}
};