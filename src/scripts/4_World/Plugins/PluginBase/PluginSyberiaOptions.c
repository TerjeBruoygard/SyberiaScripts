class PluginSyberiaOptions extends PluginBase
{
	int m_clientCharacterId = -1;
	ref PluginSyberiaOptions_Client m_client;
	
	override void OnInit()
	{
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_CLIENT_OPTIONS, this, "OnReceiveClientOptions");
	}
	
	protected void OnReceiveClientOptions(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		Param2<ref PluginSyberiaOptions_Client, int> clientData;
       	if ( !ctx.Read( clientData ) ) return;	
		
		m_client = clientData.param1;
		m_clientCharacterId = clientData.param2;
	}
	
	void ~PluginSyberiaOptions()
	{
		if (m_client) delete m_client;
	}
};

class PluginSyberiaOptions_Client
{
	int m_checkIdentityMode = 1;
	bool m_operateVisceraHimself = 0;
	int m_skillLevelSize = 1000;
	int m_skillLevelModifier = 200;
};

PluginSyberiaOptions GetSyberiaOptions() 
{
    return PluginSyberiaOptions.Cast(GetPlugin(PluginSyberiaOptions));
}