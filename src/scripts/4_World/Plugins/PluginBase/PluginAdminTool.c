class PluginAdminTool extends PluginBase
{
	ref AdminToolMenu m_guiMenu = null;
	int m_openNoSpamTimer;
	int m_selectedTabId = 0;
	string m_selectedPlayerUID;
	
	override void OnInit()
	{
		m_openNoSpamTimer = GetGame().GetTime();
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_OPEN, this, "RequestOpen");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_PLAYERINFO, this, "PlayerInfo");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_PLAYERUPDATE, this, "PlayerUpdate");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_SPAWNITEM, this, "SpawnItem");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_CLEARITEMS, this, "ClearItems");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_UPDATEMAP, this, "UpdateMap");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT, this, "Teleport");
	}
	
	bool IsOpen()
	{
		return m_guiMenu && m_guiMenu.m_active;
	}
	
	void Open()
	{
		int deltaTimeLastOpen = GetGame().GetTime() - m_openNoSpamTimer;
		if (deltaTimeLastOpen > 1000)
		{
			m_openNoSpamTimer = GetGame().GetTime();
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_OPEN, new Param1< int >( 0 ) );
		}
	}
	
	void Close()
	{
		if (m_guiMenu)
		{
			m_selectedTabId = m_guiMenu.m_selectedTabId;
			m_selectedPlayerUID = m_guiMenu.m_selectedPlayerUID;
			m_guiMenu.m_active = false;
		}
	}
	
	void RequestOpen( ref ParamsReadContext ctx, ref PlayerIdentity sender )
    { 
		if (GetGame().IsServer() || IsOpen()) return;		
		if (GetGame().GetUIManager().GetMenu() != NULL) return;
		
        if (!m_guiMenu) m_guiMenu = new AdminToolMenu;
		
		Param1< ref PluginAdminTool_OpenContext > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		m_guiMenu.m_selectedTabId = m_selectedTabId;
		m_guiMenu.m_selectedPlayerUID = m_selectedPlayerUID;
		m_guiMenu.UpdateServerContext(serverData.param1);
		GetGame().GetUIManager().ShowScriptedMenu( m_guiMenu, NULL );
	}
	
	void PlayerInfo( ref ParamsReadContext ctx, ref PlayerIdentity sender )
    { 
		if (GetGame().IsServer() || !IsOpen() || !m_guiMenu) return;		
		
		Param1< ref PluginAdminTool_PlayerContextDetails > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		m_guiMenu.UpdatePlayerContext(serverData.param1);
	}
	
	void PlayerUpdate( ref ParamsReadContext ctx, ref PlayerIdentity sender ) {}
	
	void SpawnItem( ref ParamsReadContext ctx, ref PlayerIdentity sender ) {}
	
	void ClearItems( ref ParamsReadContext ctx, ref PlayerIdentity sender ) {}
	
	void UpdateMap( ref ParamsReadContext ctx, ref PlayerIdentity sender ) 
	{
		if (GetGame().IsServer() || !IsOpen() || !m_guiMenu) return;		
		
		Param1< ref PluginAdminTool_MapContext > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		m_guiMenu.UpdateMapTab(serverData.param1);
		delete serverData.param1;
	}
	
	void Teleport( ref ParamsReadContext ctx, ref PlayerIdentity sender ) {}
};

class PluginAdminTool_OpenContext
{
	ref array<ref PluginAdminTool_PlayerContextBase> m_players;
	ref array<ref PluginAdminTool_SpawnerCategories> m_spawnerCategories;
	
	void ~PluginAdminTool_OpenContext()
	{
		if (m_players)
		{
			foreach (ref PluginAdminTool_PlayerContextBase player : m_players) delete player;
			delete m_players;
		}
	}
};

class PluginAdminTool_SpawnerCategories
{
	string m_name;
	string m_preffix;
	string m_class;
};

class PluginAdminTool_PlayerContextBase
{
	string m_uid;
	string m_name;
	string m_nickname;
	bool m_isAdmin;
	bool m_isGhost;
};

class PluginAdminTool_PlayerContextDetails : PluginAdminTool_PlayerContextBase
{
	int m_souls;
	int m_respawnCounter;
	
	ref array<ref PluginAdminTool_PlayerStatContext> m_stats;
	
	ref array<ref PluginAdminTool_PlayerInvContext> m_inv;
	
	void ~PluginAdminTool_PlayerContextDetails()
	{
		if (m_stats)
		{
			foreach (ref PluginAdminTool_PlayerStatContext stat : m_stats) delete stat;
			delete m_stats;
		}
		
		if (m_inv)
		{
			foreach (ref PluginAdminTool_PlayerInvContext inv : m_inv) delete inv;
			delete m_inv;
		}
	}
}

class PluginAdminTool_PlayerStatContext
{
	string m_statName;
	float m_minValue;
	float m_maxValue;
	float m_curValue;
	
	void PluginAdminTool_PlayerStatContext(string statName, float minValue, float maxValue, float curValue)
	{
		m_statName = statName;
		m_minValue = minValue;
		m_maxValue = maxValue;
		m_curValue = curValue;
	}
};

class PluginAdminTool_PlayerInvContext
{
	string m_classname;
	float m_damage;
	int m_curQuantity;
	int m_maxQuantity;
	
	ref array<ref PluginAdminTool_PlayerInvContext> m_attachments;
	ref array<ref PluginAdminTool_PlayerInvContext> m_cargo;
	
	void ~PluginAdminTool_PlayerInvContext()
	{
		if (m_attachments)
		{
			foreach (ref PluginAdminTool_PlayerInvContext a : m_attachments) delete a;
			delete m_attachments;
		}
		
		if (m_cargo)
		{
			foreach (ref PluginAdminTool_PlayerInvContext c : m_cargo) delete c;
			delete m_cargo;
		}
	}
};

class PluginAdminTool_SpawnItemContext
{
	string m_classname;
	float m_health;
	float m_quantity;
	int m_spawnType;
	vector m_cursorPos;
	ref array<string> m_attachments;
	
	void ~PluginAdminTool_SpawnItemContext()
	{
		if (m_attachments) delete m_attachments;
	}
};

class PluginAdminTool_MapContext
{
	ref array<vector> m_playerPositions;
	ref array<string> m_playerNames;
	
	ref array<vector> m_vehiclePositions;
	ref array<string> m_vehicleNames;
	
	void ~PluginAdminTool_MapContext()
	{
		if (m_playerPositions) delete m_playerPositions;
		if (m_playerNames) delete m_playerNames;
		
		if (m_vehiclePositions) delete m_vehiclePositions;
		if (m_vehicleNames) delete m_vehicleNames;
	}
};