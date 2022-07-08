class PluginAdminTool extends PluginBase
{
	ref AdminToolMenu m_guiMenu = null;
	AdminFreeCam m_freeCam;
	int m_openNoSpamTimer;
	int m_selectedTabId = 0;
	string m_selectedPlayerUID;
	bool m_adminPermissions = false;
	int m_lastEspLootReload = 0;
	float m_espSynchTimer = 0;
	bool m_espSynchPending = false;	
	ref array<vector> m_lootCachePositions = new array<vector>;
	ref array<string> m_lootCacheNames = new array<string>;
	ref array<int> m_lootCacheColors = new array<int>;
	ref PluginAdminTool_MapContext m_espSynchContext = null;
	
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
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_FREECAM, this, "FreeCam");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_ESPSYNCH, this, "EspSynch");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_OBJMOVE, this, "ObjMove");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_OBJDEL, this, "ObjDel");		
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_DELETE_CHARACTER, this, "PlayerDeleteCharacter");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_KICK, this, "PlayerKick");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT_TO_PLAYER, this, "PlayerTeleportToPlayer");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT_PLAYER_TO_ME, this, "PlayerTeleportToMe");
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ADMINTOOL_MESSAGE, this, "PlayerMessage");
	}
	
	override void OnUpdate(float delta_time)
	{
		if (!m_adminPermissions) return;
		if (!GetGame().IsClient()) return;
	
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (!player || !player.IsAlive())
		{
			m_espSynchPending = false;
			m_adminPermissions = false;
			return;
		}
			
		m_espSynchTimer = m_espSynchTimer + delta_time;
		if (m_espSynchPending) return;		
		if (m_espSynchTimer < 0.2) return;
		
		m_espSynchTimer = 0;
		
		if (AdminToolMenu.m_toolsEspPlayersChecked || AdminToolMenu.m_toolsEspDeadBodiesChecked || AdminToolMenu.m_toolsEspVehiclesChecked)
		{
			m_espSynchPending = true;
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_ESPSYNCH, new Param3< bool, bool, bool >( AdminToolMenu.m_toolsEspPlayersChecked, AdminToolMenu.m_toolsEspDeadBodiesChecked, AdminToolMenu.m_toolsEspVehiclesChecked ) );
		}
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
	
	void TeleportToCursor()
	{
		if (!m_adminPermissions)
			return;
		
		vector cursorPos;
		if (GameHelpers.GetCursorPos(cursorPos))
		{
			if (m_freeCam)
			{
				cursorPos[1] = cursorPos[1] + 0.25;
				m_freeCam.SetPosition(cursorPos);	
			}
			else
			{
				GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT, new Param2< vector, int >( cursorPos, 0 ) );
			}
		}
	}
	
	void RequestOpen( ParamsReadContext ctx, PlayerIdentity sender )
    { 
		if (GetGame().IsServer() || IsOpen()) return;		
		if (GetGame().GetUIManager().GetMenu() != NULL) return;
		
        if (!m_guiMenu) m_guiMenu = new AdminToolMenu;
		
		Param1< ref PluginAdminTool_OpenContext > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		m_adminPermissions = true;
		m_guiMenu.m_selectedTabId = m_selectedTabId;
		m_guiMenu.m_selectedPlayerUID = m_selectedPlayerUID;
		m_guiMenu.UpdateServerContext(serverData.param1);
		GetGame().GetUIManager().ShowScriptedMenu( m_guiMenu, NULL );
	}
	
	void PlayerInfo( ParamsReadContext ctx, PlayerIdentity sender )
    { 
		if (GetGame().IsServer() || !IsOpen() || !m_guiMenu) return;		
		
		Param1< ref PluginAdminTool_PlayerContextDetails > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		m_guiMenu.UpdatePlayerContext(serverData.param1);
	}
	
	void PlayerUpdate( ParamsReadContext ctx, PlayerIdentity sender ) {}
	
	void SpawnItem( ParamsReadContext ctx, PlayerIdentity sender ) {}
	
	void ClearItems( ParamsReadContext ctx, PlayerIdentity sender ) {}
	
	void UpdateMap( ParamsReadContext ctx, PlayerIdentity sender ) 
	{
		if (GetGame().IsServer() || !IsOpen() || !m_guiMenu) return;		
		
		Param1< ref PluginAdminTool_MapContext > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		m_guiMenu.UpdateMapTab(serverData.param1);
	}
	
	void Teleport( ParamsReadContext ctx, PlayerIdentity sender ) {}
	
	void FreeCam( ParamsReadContext ctx, PlayerIdentity sender ) 
	{
		if (!m_adminPermissions) return;
		
		Param2< bool, vector > serverData;
	    if ( !ctx.Read( serverData ) ) return;
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player) return;

		Close();		
		if (m_freeCam)
		{
			m_freeCam.SetActive(false);	
			
			if (m_guiMenu) 
				GetGame().GetUIManager().HideScriptedMenu(m_guiMenu);	
				
			GetGame().ObjectDelete(m_freeCam);
			GetGame().SelectPlayer(null, GetGame().GetPlayer());
			GetGame().GetMission().GetHud().Show( true );
			GetGame().GetInput().ResetGameFocus();
			GetGame().GetUIManager().ShowCursor(false);
			m_freeCam = null;
			
		}
		
		if (serverData.param1)
		{
			vector pos;			
			MiscGameplayFunctions.GetHeadBonePos(player, pos);
			m_freeCam = AdminFreeCam.Cast(g_Game.CreateObject( "AdminFreeCam", pos, true ));
			m_freeCam.SetActive(true);
		}
	}
	
	void EspSynch( ParamsReadContext ctx, PlayerIdentity sender )
	{
		if (!m_adminPermissions) return;
		
		m_espSynchPending = false;
		Param1< ref PluginAdminTool_MapContext > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		if (m_espSynchContext) delete m_espSynchContext;
		m_espSynchContext = serverData.param1;
	}
	
	void ObjMove( ParamsReadContext ctx, PlayerIdentity sender ) { }
	
	void ObjDel( ParamsReadContext ctx, PlayerIdentity sender ) { }
	
	void PlayerDeleteCharacter( ParamsReadContext ctx, PlayerIdentity sender ) { }
	
	void PlayerKick( ParamsReadContext ctx, PlayerIdentity sender ) { }
	
	void PlayerTeleportToPlayer( ParamsReadContext ctx, PlayerIdentity sender ) { }
	
	void PlayerTeleportToMe( ParamsReadContext ctx, PlayerIdentity sender ) { }
	
	void PlayerMessage( ParamsReadContext ctx, PlayerIdentity sender ) 
	{
		Param1< string > serverData;
        if ( !ctx.Read( serverData ) ) return;
		
		GetGame().GetUIManager().CloseAll();
		GetGame().GetUIManager().ShowScriptedMenu(new AdminMessageBox(serverData.param1), NULL);
	}
	
	bool HasAdminPermissions()
	{
		return m_adminPermissions;
	}
	
	void GetEspMarkers(ref array<vector> positions, ref array<string> names, ref array<int> types, ref array<int> colors)
	{
		if (!m_adminPermissions) return;
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player) return;
		
		vector pos;
		if (m_freeCam)
		{
			pos = m_freeCam.GetPosition();
		}
		else
		{
			pos = player.GetPosition();
		}
		
		if (AdminToolMenu.m_toolsEspPlayersChecked && m_espSynchContext)
		{
			for (int pi = 0; pi < m_espSynchContext.m_playerPositions.Count(); pi++)
			{
				vector pvec = m_espSynchContext.m_playerPositions.Get(pi);
				float pdist = vector.Distance(pvec, pos);
				if (pdist < AdminToolMenu.m_toolsEspSliderDist1Value)
				{
					positions.Insert( pvec );
					names.Insert( m_espSynchContext.m_playerNames.Get(pi) + " (" + (int)pdist + "m)" );
					types.Insert( PluginAdminTool_EspType.PLAYER );
					colors.Insert(ARGB(255, 255, 0, 0));
				}
			}
		}
		
		if (AdminToolMenu.m_toolsEspDeadBodiesChecked && m_espSynchContext)
		{
			for (int bi = 0; bi < m_espSynchContext.m_bodiesPositions.Count(); bi++)
			{
				vector bvec = m_espSynchContext.m_bodiesPositions.Get(bi);
				float bdist = vector.Distance(bvec, pos);
				if (bdist < AdminToolMenu.m_toolsEspSliderDist1Value)
				{
					positions.Insert( bvec );
					names.Insert( m_espSynchContext.m_bodiesNames.Get(bi) + " (" + (int)bdist + "m)" );
					types.Insert( PluginAdminTool_EspType.BODY );
					colors.Insert(ARGB(255, 128, 93, 128));
				}
			}
		}
		
		if (AdminToolMenu.m_toolsEspVehiclesChecked && m_espSynchContext)
		{
			for (int vi = 0; vi < m_espSynchContext.m_vehiclePositions.Count(); vi++)
			{
				vector vvec = m_espSynchContext.m_vehiclePositions.Get(vi);
				float vdist = vector.Distance(vvec, pos);
				if (vdist < AdminToolMenu.m_toolsEspSliderDist1Value)
				{
					positions.Insert( vvec );
					names.Insert( m_espSynchContext.m_vehicleNames.Get(vi) + " (" + (int)vdist + "m)" );
					types.Insert( PluginAdminTool_EspType.VEHICLES );
					colors.Insert(ARGB(255, 255, 216, 0));
				}
			}
		}
		
		if (AdminToolMenu.m_toolsEspLootChecked && AdminToolMenu.m_toolsEspLootCategoriesSelections)
		{
			if ( (GetGame().GetTime() - m_lastEspLootReload) > 1000 )
			{
				m_lastEspLootReload = GetGame().GetTime();
				m_lootCachePositions.Clear();
				m_lootCacheNames.Clear();
				m_lootCacheColors.Clear();
				
				bool emptyFilter = AdminToolMenu.m_toolsEspFilterValue == "";
				array<Object> object = new array<Object>;
				GetGame().GetObjectsAtPosition3D(pos, AdminToolMenu.m_toolsEspSliderDist2Value, object, null);
				foreach (Object obj : object)
				{
					for (int ilc = 0; ilc < AdminToolMenu.m_toolsEspLootCategoriesSelections.Count(); ilc++)
					{
						if (!AdminToolMenu.m_toolsEspLootCategoriesSelections.Get(ilc))
							continue;
						
						if (obj.IsInherited( AdminToolMenu.m_toolsEspLootCategoriesFilter.Get(ilc) ))
						{
							if (emptyFilter || GameHelpers.StringContainsCaseInsensetive(obj.GetType(), AdminToolMenu.m_toolsEspFilterValue))
							{
								m_lootCachePositions.Insert( obj.GetPosition() );
								m_lootCacheNames.Insert( obj.GetType() );
								m_lootCacheColors.Insert( AdminToolMenu.m_toolsEspLootCategoriesColor.Get(ilc) );
							}
							
							break;
						}
					}
				}
			}
			
			for (int li = 0; li < m_lootCachePositions.Count(); li++)
			{
				positions.Insert( m_lootCachePositions.Get(li) );
				names.Insert( m_lootCacheNames.Get(li) );
				types.Insert( PluginAdminTool_EspType.LOOT );
				colors.Insert( m_lootCacheColors.Get(li) );
			}
		}
	}
};

enum PluginAdminTool_EspType
{
	PLAYER, BODY, VEHICLES, LOOT
}

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
	string m_group;
	bool m_isAdmin;
	bool m_isGhost;
};

class PluginAdminTool_PlayerContextDetails : PluginAdminTool_PlayerContextBase
{
	int m_souls;
	int m_respawnCounter;
    vector m_position;
	
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
	
	ref array<vector> m_bodiesPositions;
	ref array<string> m_bodiesNames;
	
	ref array<vector> m_vehiclePositions;
	ref array<string> m_vehicleNames;
	
	void ~PluginAdminTool_MapContext()
	{
		if (m_playerPositions) delete m_playerPositions;
		if (m_playerNames) delete m_playerNames;
		
		if (m_bodiesPositions) delete m_bodiesPositions;
		if (m_bodiesNames) delete m_bodiesNames;
		
		if (m_vehiclePositions) delete m_vehiclePositions;
		if (m_vehicleNames) delete m_vehicleNames;
	}
};