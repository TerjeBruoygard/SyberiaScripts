class BuildingLivespace extends BuildingSuper
{
	// Local
	protected bool m_ready = false;
	protected ref LivespaceData m_data = null;
	
	// RPC Synch
	protected int m_livespaceId;
	protected string m_livespacePath;
	protected int m_houseNetId1, m_houseNetId2;
	protected ref array<int> m_doorLevels = new array<int>;
	protected ref array<int> m_barricadeLevels = new array<int>;
	protected ref array<string> m_simpleSelections = new array<string>;
	
	static BuildingLivespace Find(House house, vector pos)
	{
		BuildingLivespace result = null;
		BuildingLivespace iter = null;
		vector localPos = house.WorldToModel(pos);
		vector bbMin, bbMax, offset;
		ref array<Object> objects = new array<Object>;
		string configPath = "CfgBuildingInfo " + house.GetType();
		int livespaceId = 0;
		
		while ( result == null && GetGame().ConfigIsExisting(configPath + " Livespace" + livespaceId) )
		{
			offset = GetGame().ConfigGetVector(configPath + " Livespace" + livespaceId + " offset");
			offset = house.ModelToWorld(offset);
			
			objects.Clear();
			GetGame().GetObjectsAtPosition3D(offset, 0.1, objects, NULL);
			
			foreach (Object obj : objects)
			{
				iter = BuildingLivespace.Cast(obj);
				if (iter)
				{
					if (iter.m_ready && iter.GetHouse() == house)
					{
						if (GameHelpers.IntersectBBox(iter.m_data.m_bboxStart, iter.m_data.m_bboxEnd, localPos))
						{
							result = iter;
							break;
						}
					}
				}
			}
			
			livespaceId = livespaceId + 1;
		}
		
		delete objects;
		return result;
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		ConfigGetTextArray("simpleHiddenSelections", m_simpleSelections);
		
		if (GetGame().IsClient())
		{
			RPCSingleParam(SyberiaERPC.SYBERPC_SYNCH_LIVESPACE_CLIENT, new Param1<int>(0), true);
		}
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		if (rpc_type == SyberiaERPC.SYBERPC_SYNCH_LIVESPACE_SERVER)
		{
			Param6<string, int, int, int, ref array<int>, ref array<int>> params;
			if (!ctx.Read(params))
				return;
			
			if (m_doorLevels) delete m_doorLevels;
			if (m_barricadeLevels) delete m_barricadeLevels;
			
			m_livespacePath = params.param1;
			m_livespaceId = params.param2;
			m_houseNetId1 = params.param3;
			m_houseNetId2 = params.param4;
			m_doorLevels = params.param5;
			m_barricadeLevels = params.param6;
			
			if (m_data == null)
			{
				m_data = new LivespaceData(m_livespacePath);
			}
			
			SetupDoors();
			SetupBarricades();
			
			m_ready = true;			
			SybLog("BuildingLivespace: OnRPC Successfully synched.");
		}
	}
	
	ref LivespaceData GetData()
	{
		return m_data;
	}
	
	House GetHouse()
	{
		if (!m_ready) return null;
		return House.Cast( GetGame().GetObjectByNetworkId(m_houseNetId1, m_houseNetId2) );
	}
	
	int FindSimpleHidenSelectionId(string name)
	{
		return m_simpleSelections.Find(name);
	}
	
	void SetupDoors()
	{
		for (int i = 0; i < m_data.m_doors.Count(); i++) 
		{
			ref LivespaceDoorData doorData = m_data.m_doors[i];
			int level = m_doorLevels[i] - 1;
			for (int l = 0; l < doorData.m_levels.Count(); l++)
			{
				int selectionId = FindSimpleHidenSelectionId(doorData.m_levels[l]);
				if (selectionId != -1)
				{
					SetSimpleHiddenSelectionState(selectionId, level == l);
				}
			}
		}
	}
	
	void SetupBarricades()
	{
		for (int i = 0; i < m_barricadeLevels.Count(); i++) 
		{
			ref LivespaceBarricadeData barricadeData = m_data.m_barricades[i];
			int level = m_barricadeLevels[i] - 1;
			for (int l = 0; l < barricadeData.m_levels.Count(); l++)
			{
				int selectionId = FindSimpleHidenSelectionId(barricadeData.m_levels[l]);
				if (selectionId != -1)
				{
					SetSimpleHiddenSelectionState(selectionId, level == l);
				}
			}
		}
	}
	
	bool CanOpenDoor(PlayerBase player, int vanilaDoorIndex)
	{
		if (!m_ready) return false;
		int doorId = GetDoorIdByVanillaDoorId(vanilaDoorIndex);
		if (doorId == -1) return true;
		
		int level = m_doorLevels[doorId];		
		return level == 0;
	}
	
	bool CanCloseDoor(PlayerBase player, int vanilaDoorIndex)
	{
		return CanOpenDoor(player, vanilaDoorIndex);
	}
	
	int GetDoorIdByVanillaDoorId(int id)
	{
		if (!m_ready) return -1;
		if (id == -1) return -1;
		
		foreach (ref LivespaceDoorData doorData : m_data.m_doors)
		{
			int equalId = doorData.m_linkedDoorIds.Find(id);			
			if (equalId != -1)
			{
				return doorData.m_linkedDoorIds[equalId];
			}
		}
		
		return -1;
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		delete m_doorLevels;
		delete m_barricadeLevels;
		delete m_simpleSelections;
		
		if (m_data != null)
		{
			delete m_data;
		}
	}
};

class LivespaceData
{
	vector m_bboxStart;
	vector m_bboxEnd;
	string m_classname;
	vector m_offset;
	string m_homebook;
	ref array<ref LivespaceDoorData> m_doors;
	ref array<ref LivespaceBarricadeData> m_barricades;
	
	void LivespaceData(string configPath)
	{
		m_bboxStart = GetGame().ConfigGetVector(configPath + " bboxStart");
		m_bboxEnd = GetGame().ConfigGetVector(configPath + " bboxEnd");
		m_classname = GetGame().ConfigGetTextOut(configPath + " classname");
		m_offset = GetGame().ConfigGetVector(configPath + " offset");
		m_homebook = GetGame().ConfigGetTextOut(configPath + " homebook");
		
		m_doors = new array<ref LivespaceDoorData>;
		int doorId = 0;
		while ( GetGame().ConfigIsExisting(configPath + " Door" + doorId) )
		{
			m_doors.Insert( new LivespaceDoorData(configPath + " Door" + doorId) );
			doorId = doorId + 1;
		}
		
		m_barricades = new array<ref LivespaceBarricadeData>;
		int barricadeId = 0;
		while ( GetGame().ConfigIsExisting(configPath + " Barricade" + barricadeId) )
		{
			m_barricades.Insert( new LivespaceBarricadeData(configPath + " Barricade" + barricadeId) );
			barricadeId = barricadeId + 1;
		}
	}
	
	void ~LivespaceData()
	{
		foreach (ref LivespaceDoorData door : m_doors)
		{
			delete door;
		}
		delete m_doors;
		
		foreach (ref LivespaceBarricadeData barricade : m_barricades)
		{
			delete barricade;
		}
		delete m_barricades;
	}
};

class LivespaceDoorData
{
	int m_selfDoorId;
	ref array<int> m_linkedDoorIds;
    bool m_outerDoor;
    ref array<string> m_levels;
	
	void LivespaceDoorData(string configPath)
	{
		m_linkedDoorIds = new array<int>;
		m_levels = new array<string>;
		m_selfDoorId = GetGame().ConfigGetInt(configPath + " selfDoorId");
		m_outerDoor = GetGame().ConfigGetInt(configPath + " outerDoor") == 1;
		GetGame().ConfigGetIntArray(configPath + " linkedDoorIds", m_linkedDoorIds);
		GetGame().ConfigGetTextArray(configPath + " levels", m_levels);
	}
	
	void ~LivespaceDoorData()
	{
		delete m_linkedDoorIds;
		delete m_levels;
	}
};

class LivespaceBarricadeData
{
    ref array<string> m_levels;
	
	void LivespaceBarricadeData(string configPath)
	{
		m_levels = new array<string>;
		GetGame().ConfigGetTextArray(configPath + " levels", m_levels);
	}
	
	void ~LivespaceBarricadeData()
	{
		delete m_levels;
	}
};