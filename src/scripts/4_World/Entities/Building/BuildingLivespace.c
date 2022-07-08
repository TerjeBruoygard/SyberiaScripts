class BuildingLivespace extends BuildingSuper
{
	// Local
	bool m_ready = false;
	
	// RPC Synch
	int m_livespaceId;
	string m_livespacePath;
	int m_houseNetId1, m_houseNetId2;
	ref array<int> m_doorLevels = new array<int>;
	ref array<int> m_barricadeLevels = new array<int>;
	ref array<string> m_simpleSelections = new array<string>;
	
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
			
			SetupDoors();
			SetupBarricades();
			
			m_ready = true;			
			SybLog("BuildingLivespace: OnRPC Successfully synched.");
		}
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
		TStringArray levels = new TStringArray;
		for (int i = 0; i < m_doorLevels.Count(); i++) 
		{
			int level = m_doorLevels[i] - 1;
			levels.Clear();
			GetGame().ConfigGetTextArray(m_livespacePath + " Door" + i + " levels", levels);
			
			for (int l = 0; l < levels.Count(); l++)
			{
				int selectionId = FindSimpleHidenSelectionId(levels[l]);
				if (selectionId != -1)
				{
					SetSimpleHiddenSelectionState(selectionId, level == l);
				}
			}
		}
	}
	
	void SetupBarricades()
	{
		TStringArray levels = new TStringArray;
		for (int i = 0; i < m_barricadeLevels.Count(); i++) 
		{
			int level = m_barricadeLevels[i] - 1;
			levels.Clear();
			GetGame().ConfigGetTextArray(m_livespacePath + " Barricade" + i + " levels", levels);
			
			for (int l = 0; l < levels.Count(); l++)
			{
				int selectionId = FindSimpleHidenSelectionId(levels[l]);
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
		if (m_livespacePath == "") return -1;
		if (id == -1) return -1;
		
		int doorId = 0;
		TIntArray linkedDoorIds = new TIntArray;
		while ( GetGame().ConfigIsExisting(m_livespacePath + " Door" + doorId) )
		{
			linkedDoorIds.Clear();
			GetGame().ConfigGetIntArray(m_livespacePath + " Door" + doorId + " linkedDoorIds", linkedDoorIds);
			int equalId = linkedDoorIds.Find(id);			
			if (equalId != -1)
			{
				return linkedDoorIds[equalId];
			}
			
			doorId = doorId + 1;
		}
		
		return -1;
	}
	
	static BuildingLivespace Find(House house, vector pos)
	{
		BuildingLivespace result = null;
		BuildingLivespace iter = null;
		vector localPos = house.WorldToModel(pos);
		vector bbMin, bbMax;
		ref array<Object> objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(house.GetPosition(), 0.1, objects, NULL);
		
		foreach (Object obj : objects)
		{
			iter = BuildingLivespace.Cast(obj);
			if (iter)
			{
				if (iter.m_ready && iter.GetHouse() == house)
				{
					bbMin = GetGame().ConfigGetVector(iter.m_livespacePath + " bboxStart");
					bbMax = GetGame().ConfigGetVector(iter.m_livespacePath + " bboxEnd");
					if (GameHelpers.IntersectBBox(bbMin, bbMax, localPos))
					{
						result = iter;
						break;
					}
				}
			}
		}
		
		delete objects;
		return result;
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		delete m_doorLevels;
		delete m_barricadeLevels;
		delete m_simpleSelections;
	}
};