class BuildingLivespace extends BuildingSuper
{
	// Local
	protected bool m_ready = false;
	protected ref LivespaceData m_data = null;
	protected ref array<string> m_simpleSelections = new array<string>;
	
	// RPC Synch
	ref LivespaceSynchData m_synchData = new LivespaceSynchData;

	
	static BuildingLivespace FindByVanillaDoorIndex(House house, int doorIndex)
	{
		BuildingLivespace result = null;
		BuildingLivespace iter = null;
		vector offset;
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
						if (iter.GetDoorIdByVanillaDoorId(doorIndex) != -1)
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
			Param1<ref LivespaceSynchData> params;
			if (!ctx.Read(params))
				return;
			
			if (m_synchData) delete m_synchData;
			
			m_synchData = params.param1;

			if (m_data == null)
			{
				m_data = new LivespaceData(m_synchData.m_livespacePath);
			}
			
			int marcSelectionId = FindSimpleHidenSelectionId("marc");
			if (marcSelectionId != -1)
			{
				SetSimpleHiddenSelectionState(marcSelectionId, m_data.m_debug);
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
		return House.Cast( GetGame().GetObjectByNetworkId(m_synchData.m_houseNetId1, m_synchData.m_houseNetId2) );
	}
	
	bool IsReady()
	{
		return m_ready;
	}
	
	int GetLivespaceId()
	{
		return m_synchData.m_livespaceId;
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
			int level = m_synchData.m_doorLevels[i] - 1;
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
		for (int i = 0; i < m_synchData.m_barricadeLevels.Count(); i++) 
		{
			ref LivespaceBarricadeData barricadeData = m_data.m_barricades[i];
			int level = m_synchData.m_barricadeLevels[i] - 1;
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
	
	int GetBarricadeLevel(int id)
	{
		return m_synchData.m_barricadeLevels[id];
	}
	
	int GetDoorLevel(int id)
	{
		return m_synchData.m_doorLevels[id];
	}
	
	int GetDoorIdByVanillaDoorId(int id)
	{
		if (!m_ready) return -1;
		if (id == -1) return -1;
		
		for (int i = 0; i < m_data.m_doors.Count(); i++)
		{
			ref LivespaceDoorData doorData = m_data.m_doors[i];	
			if (doorData.m_linkedDoorIds.Find(id) != -1)
			{
				return i;
			}
		}
		
		return -1;
	}
	
	void GetDoorUpgradeProfile(int doorId, ref LivespaceUpgradeProfile profile)
	{
		int doorLevel = GetDoorLevel(doorId);
		string doorUpgradeProfile = GetData().m_doors.Get(doorId).m_upgradeProfile;
		profile.Init("CfgBuildingResources Doors " + doorUpgradeProfile + " Level" + doorLevel.ToString());
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (m_synchData) 
		{
			delete m_synchData;
		}
		
		if (m_simpleSelections) 
		{
			delete m_simpleSelections;
		}
		
		if (m_data != null)
		{
			delete m_data;
		}
	}
	
	static BuildingLivespace FindLivespace(House house, vector pos)
	{
		BuildingLivespace result = null;
		BuildingLivespace iter = null;
		vector localPos = house.WorldToModel(pos);
		vector offset;
		array<Object> objects = new array<Object>;
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
		
		return result;
	}
	
	static int CheckPossibleLivespaceId(House house, vector pos)
	{
		vector localPos = house.WorldToModel(pos);
		vector bbMin, bbMax;
		string configPath = "CfgBuildingInfo " + house.GetType();
		int livespaceId = 0;
		
		while ( GetGame().ConfigIsExisting(configPath + " Livespace" + livespaceId) )
		{
			bbMin = GetGame().ConfigGetVector(configPath + " Livespace" + livespaceId + " bboxStart");
			bbMax = GetGame().ConfigGetVector(configPath + " Livespace" + livespaceId + " bboxEnd");
			
			if (GameHelpers.IntersectBBox(bbMin, bbMax, localPos))
			{
				return livespaceId;
			}
			
			livespaceId = livespaceId + 1;
		}
		
		return -1;
	}
};

class LivespaceSynchData
{
	int m_livespaceId;
	string m_livespacePath;
	int m_houseNetId1, m_houseNetId2;
	ref array<int> m_doorLevels = new array<int>;
	ref array<int> m_barricadeLevels = new array<int>;
	
	void ~LivespaceSynchData()
	{
		if (m_doorLevels) delete m_doorLevels;
		if (m_barricadeLevels) delete m_barricadeLevels;
	}
};

class LivespaceHomebookData
{
	ref array<string> m_owners;
	ref array<string> m_members;
};

class LivespaceData
{
	vector m_bboxStart;
	vector m_bboxEnd;
	string m_classname;
	vector m_offset;
	string m_homebook;
	bool m_debug;
	ref array<ref LivespaceDoorData> m_doors;
	ref array<ref LivespaceBarricadeData> m_barricades;
	
	void LivespaceData(string configPath)
	{
		m_bboxStart = GetGame().ConfigGetVector(configPath + " bboxStart");
		m_bboxEnd = GetGame().ConfigGetVector(configPath + " bboxEnd");
		m_classname = GetGame().ConfigGetTextOut(configPath + " classname");
		m_offset = GetGame().ConfigGetVector(configPath + " offset");
		m_homebook = GetGame().ConfigGetTextOut(configPath + " homebook");
		m_debug = (GetGame().ConfigGetInt(configPath + " debug") == 1);
		
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
	string m_upgradeProfile;
	
	void LivespaceDoorData(string configPath)
	{
		m_linkedDoorIds = new array<int>;
		m_levels = new array<string>;
		m_selfDoorId = GetGame().ConfigGetInt(configPath + " selfDoorId");
		m_outerDoor = GetGame().ConfigGetInt(configPath + " outerDoor") == 1;
		GetGame().ConfigGetIntArray(configPath + " linkedDoorIds", m_linkedDoorIds);
		GetGame().ConfigGetTextArray(configPath + " levels", m_levels);
		
		if (!GetGame().ConfigGetText(configPath + " upgradeProfile", m_upgradeProfile))
		{
			m_upgradeProfile = "Default";
		}
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

class LivespaceUpgradeProfile
{
	private ref TStringArray m_consumablesClass = new TStringArray;
	private ref TFloatArray m_consumablesQuantity = new TFloatArray;

	private ref TStringArray m_toolsClass = new TStringArray;	
	private ref TFloatArray m_toolsDammage = new TFloatArray;
	
	void Init(string cfgPath)
	{
		m_consumablesClass.Clear();
		m_consumablesQuantity.Clear();

		m_toolsClass.Clear();
		m_toolsDammage.Clear();
		
		if (!GetGame().ConfigIsExisting(cfgPath))
		{
			return;
		}
		
		GetGame().ConfigGetTextArray(cfgPath + " consumablesClass", m_consumablesClass);
		GetGame().ConfigGetFloatArray(cfgPath + " consumablesQuantity", m_consumablesQuantity);

		GetGame().ConfigGetTextArray(cfgPath + " toolsClass", m_toolsClass);
		GetGame().ConfigGetFloatArray(cfgPath + " toolsDammage", m_toolsDammage);
	}
	
	void ~LivespaceUpgradeProfile()
	{
		delete m_consumablesClass;
		delete m_consumablesQuantity;
		
		delete m_toolsClass;
		delete m_toolsDammage;
	}
	
	int GetConsumablesCount()
	{
		return m_consumablesClass.Count();
	}
	
	void GetConsumable(int index, out string className, out float quantity)
	{
		className = m_consumablesClass.Get(index);
		quantity = m_consumablesQuantity.Get(index);
	}
	
	int GetToolsCount()
	{
		return m_toolsClass.Count();
	}
	
	void GetTool(int index, out string className, out float damage)
	{
		className = m_toolsClass.Get(index);
		damage = m_toolsDammage.Get(index);
	}
};