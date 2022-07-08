class TraderPoint extends BuildingSuper
{
    // Local
	bool m_ready = false;
	
	// RPC Synch
	int m_traderId;
	int m_objectNetId1, m_objectNetId2;
    
    override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsClient())
		{
			RPCSingleParam(SyberiaERPC.SYBERPC_SYNCH_TRADER_POINT_SERVER, new Param1<int>(0), true);
		}
	}
    
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
        if (rpc_type == SyberiaERPC.SYBERPC_SYNCH_TRADER_POINT_CLIENT)
		{
            Param3<int, int, int> params;
			if (!ctx.Read(params))
				return;
			
			m_traderId = params.param1;
			m_objectNetId1 = params.param2;
			m_objectNetId2 = params.param3;
            m_ready = true;
            
        }
	}
    
	bool IsTraderReady()
	{
		return m_ready;
	}
	
    int GetTraderId()
	{
		if (!m_ready) return -1;
		return m_traderId;
	}
    
    Object GetTraderObject()
	{
		if (!m_ready) return null;
		return GetGame().GetObjectByNetworkId(m_objectNetId1, m_objectNetId2);
	}
}