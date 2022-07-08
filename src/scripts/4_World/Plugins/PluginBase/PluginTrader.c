class PluginTrader extends PluginBase
{
	ref SybTraderMenu m_traderMenu;
	
	override void OnInit()
	{
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_OPEN_TRADE_MENU, this, "RpcRequstOpen"); 
	}

	void CloseTraderMenu()
	{
		if (m_traderMenu && m_traderMenu.m_active)
		{
			m_traderMenu.m_active = false;
		}
	}
	
	void RpcRequstOpen(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   
		Param3<int, ref PluginTrader_Traider, ref PluginTrader_Storage> clientData;
       	if ( !ctx.Read( clientData ) ) return;			
		
		if (m_traderMenu && m_traderMenu.m_active)
		{
			m_traderMenu.m_active = false;
		}
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (GetGame().GetUIManager().GetMenu() != NULL || !player || !player.CanOpenSyberiaUI())
		{
			return;
		}
		
		m_traderMenu = new SybTraderMenu;
		m_traderMenu.InitMetadata(clientData.param1, clientData.param2, clientData.param3);
		GetGame().GetUIManager().ShowScriptedMenu( m_traderMenu, NULL );
	}
	
	override void OnDestroy()
	{
		
	}
};

class PluginTrader_Storage
{
    int m_storageMaxSize;
    float m_storageCommission;
    string m_dumpingByAmountAlgorithm;
    float m_dumpingByAmountModifier;
	string m_dumpingByQualityAlgorithm;
    float m_dumpingByQualityModifier;
};

class PluginTrader_Traider
{
	int m_traderId;
    ref array<string> m_purchaseFilter;
    ref array<string> m_saleFilter;
};