class PluginSyberiaRpc : PluginBase 
{
	autoptr map<int, ref Param2<Class, string>> m_RegisteredRPCs;
	
    void PluginSyberiaRpc() 
	{
		m_RegisteredRPCs = new map<int, ref Param2<Class, string>>;
        GetDayZGame().Event_OnRPC.Insert(ServerRPCHandler);
    }

    void ~PluginSyberiaRpc() 
	{
		foreach (ref Param2<Class, string> element : m_RegisteredRPCs)
		{
			delete element;
		}
		
        GetDayZGame().Event_OnRPC.Remove(ServerRPCHandler);
    }

    void ServerRPCHandler(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) 
	{
		if (rpc_type == 67993700)
		{
			Param1<int> metaData;
			if (!ctx.Read(metaData))
			{
				return;
			}
			
			ref Param2<Class, string> invoker;
			if (!m_RegisteredRPCs.Find(metaData.param1, invoker))
			{
				SybLog("RPC with ID " + metaData.param1 + " not found.");
				return;
			}
			
			if (invoker.param1)
			{			
				auto invokeData = new Param2<ParamsReadContext, PlayerIdentity>(ctx, sender);				
				GetGame().GameScript.CallFunctionParams(invoker.param1, invoker.param2, null, invokeData);
			}
		}
    }
	
	void RegisterHandler(int id, Class instance, string fnc)
	{
		if (m_RegisteredRPCs.Contains(id))
		{
			m_RegisteredRPCs.Remove(id);
		}
		
		m_RegisteredRPCs.Insert(id, new Param2<Class, string>(instance, fnc));
	}

    void SendToClient(int id, PlayerIdentity identity, ref Param params) 
	{
		if (GetGame().IsServer())
		{		
			auto sendData = new ref array< ref Param >;
			sendData.Insert(new ref Param1<int>( id ));
			sendData.Insert(params);
        	GetGame().RPC(null, 67993700, sendData, true, identity);
		}
    }
	
	void SendToServer(int id, ref Param params) 
	{
		if (GetGame().IsClient())
		{		
			auto sendData = new ref array< ref Param >;
			sendData.Insert(new ref Param1<int>( id ));
			sendData.Insert(params);
        	GetGame().RPC(null, 67993700, sendData, true, null);
		}
    }
	
	void SendToAll(int id, ref Param params) 
	{
		if (GetGame().IsServer())
		{		
			auto sendData = new ref array< ref Param >;
			sendData.Insert(new ref Param1<int>( id ));
			sendData.Insert(params);
        	GetGame().RPC(null, 67993700, sendData, true, null);
		}
    }
}

PluginSyberiaRpc GetSyberiaRPC() 
{
    return PluginSyberiaRpc.Cast(GetPlugin(PluginSyberiaRpc));
}