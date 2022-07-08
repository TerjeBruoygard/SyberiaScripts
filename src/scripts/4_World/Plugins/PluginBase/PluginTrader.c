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
			GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_CLOSE_TRADER_MENU, new Param1<int>(m_traderMenu.m_traderId));
			m_traderMenu.m_active = false;		
		}
	}
	
	void RpcRequstOpen(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   		
		if (m_traderMenu && m_traderMenu.m_active)
		{
			m_traderMenu.m_active = false;
		}
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (GetGame().GetUIManager().GetMenu() != NULL || !player || !player.CanOpenSyberiaUI())
		{
			return;
		}
		
		Param3<int, ref PluginTrader_Trader, ref PluginTrader_Data> clientData;
       	if ( !ctx.Read( clientData ) ) return;
		
		m_traderMenu = new SybTraderMenu;
		m_traderMenu.InitMetadata(clientData.param1, clientData.param2, clientData.param3);
		GetGame().GetUIManager().ShowScriptedMenu( m_traderMenu, NULL );
	}
	
	override void OnDestroy()
	{
		
	}
};

class PluginTrader_Trader
{
	int m_traderId;
    ref array<string> m_purchaseFilter;
    ref array<string> m_saleFilter;
	int m_storageMaxSize;
    float m_storageCommission;
    string m_dumpingByAmountAlgorithm;
    float m_dumpingByAmountModifier;
	string m_dumpingByQualityAlgorithm;
    float m_dumpingByQualityModifier;
	
	void ~PluginTrader_Trader()
	{
		if (m_purchaseFilter)
		{
			delete m_purchaseFilter;
		}
		
		if (m_saleFilter)
		{
			delete m_saleFilter;
		}
	}
};

class PluginTrader_Data
{
	ref map<string, float> m_items;
	
	void ~PluginTrader_Data()
	{
		if (m_items)
		{
			delete m_items;
		}
	}
};