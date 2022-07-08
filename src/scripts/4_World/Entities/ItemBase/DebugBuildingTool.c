class DebugBuildingManager
{
	static House m_linkedHouse;
	static Shape m_marker;
	static ref array<Object> m_previewObjects = new array<Object>;
	static ref array<Shape> m_previewShapes = new array<Shape>;
	static ref array<Shape> m_rulerShapes = new array<Shape>;
	static vector m_rulerCache;
	
	static House GetLinkedHouse()
	{
		return m_linkedHouse;
	}
	
	static bool IsHouseLinked()
	{
		return m_linkedHouse != null;
	}
	
	static bool IsHouseSame(House house)
	{
		return m_linkedHouse == house;
	}
	
	static void LinkHouse(House house)
	{
		// Cleanup
		while (m_previewObjects.Count() > 0)
		{
			GetGame().ObjectDelete(m_previewObjects.Get(0));
			m_previewObjects.Remove(0);
		}
		
		while (m_previewShapes.Count() > 0)
		{
			m_previewShapes.Get(0).Destroy();
			m_previewShapes.Remove(0);
		}
		
		while (m_rulerShapes.Count() > 0)
		{
			m_rulerShapes.Get(0).Destroy();
			m_rulerShapes.Remove(0);
		}
		
		if (m_marker)
		{
			m_marker.Destroy();
		}
		
		// Misc
		m_rulerCache = "0 0 0";
		m_linkedHouse = house;		
		GetGame().CopyToClipboard(house.GetType());
		
		// Creation
		string configPath = "CfgBuildingInfo " + house.GetType();
		if (GetGame().ConfigIsExisting(configPath))
		{
			int livespaceId = 0;
			while ( GetGame().ConfigIsExisting(configPath + " Livespace" + livespaceId) )
			{
				string livespacePath = configPath + " Livespace" + livespaceId;
				vector bbstart = GetGame().ConfigGetVector(livespacePath + " bboxStart");
				vector bbend = GetGame().ConfigGetVector(livespacePath + " bboxEnd");
				DebugBuildingManager.DrawBBox(bbstart, bbend, m_previewShapes);
				
				Object homebook = GetGame().CreateObjectEx("BuildingHomeBook", house.ModelToWorld(GetGame().ConfigGetVector(livespacePath + " homeBookPos")), ECE_KEEPHEIGHT | ECE_LOCAL);
				if (homebook)
				{
					vector rot = house.GetLocalYawPitchRoll();
					rot[0] = rot[0] + GetGame().ConfigGetFloat(livespacePath + " homeBookRot");
					homebook.SetYawPitchRoll(rot);
					m_previewObjects.Insert(homebook);
					DrawObjectLine(homebook, m_previewShapes);
				}
				
				livespaceId = livespaceId + 1;
			}
		}
	}
	
	static void DrawObjectLine(Object obj, ref array<Shape> shapes)
	{
		Shape line = Debug.DrawLine( obj.GetPosition(), obj.ModelToWorld("0 0.25 0"), 0x994B77BE, ShapeFlags.NOZBUFFER );
		if (line)
		{
			shapes.Insert(line);
		}
	}
	
	static void DrawBBox(vector bbstart, vector bbend, ref array<Shape> shapes)
	{
		ref array<vector> lines = new array<vector>;
		lines.Insert(Vector(bbstart[0], bbstart[1], bbstart[2])); lines.Insert(Vector(bbend[0], bbstart[1], bbstart[2]));
		lines.Insert(Vector(bbend[0], bbstart[1], bbstart[2])); lines.Insert(Vector(bbend[0], bbstart[1], bbend[2]));
		lines.Insert(Vector(bbend[0], bbstart[1], bbend[2])); lines.Insert(Vector(bbstart[0], bbstart[1], bbend[2]));
		lines.Insert(Vector(bbstart[0], bbstart[1], bbend[2])); lines.Insert(Vector(bbstart[0], bbstart[1], bbstart[2]));
		
		lines.Insert(Vector(bbstart[0], bbend[1], bbstart[2])); lines.Insert(Vector(bbend[0], bbend[1], bbstart[2]));
		lines.Insert(Vector(bbend[0], bbend[1], bbstart[2])); lines.Insert(Vector(bbend[0], bbend[1], bbend[2]));
		lines.Insert(Vector(bbend[0], bbend[1], bbend[2])); lines.Insert(Vector(bbstart[0], bbend[1], bbend[2]));
		lines.Insert(Vector(bbstart[0], bbend[1], bbend[2])); lines.Insert(Vector(bbstart[0], bbend[1], bbstart[2]));
		
		lines.Insert(Vector(bbstart[0], bbstart[1], bbstart[2])); lines.Insert(Vector(bbstart[0], bbend[1], bbstart[2]));
		lines.Insert(Vector(bbend[0], bbstart[1], bbstart[2])); lines.Insert(Vector(bbend[0], bbend[1], bbstart[2]));
		lines.Insert(Vector(bbend[0], bbstart[1], bbend[2])); lines.Insert(Vector(bbend[0], bbend[1], bbend[2]));
		lines.Insert(Vector(bbstart[0], bbstart[1], bbend[2])); lines.Insert(Vector(bbstart[0], bbend[1], bbend[2]));
		
		for (int i = 0; i < lines.Count() / 2; i++)
		{
			Shape line = Debug.DrawLine( m_linkedHouse.ModelToWorld(lines[i * 2]), m_linkedHouse.ModelToWorld(lines[(i * 2) + 1]), 0x99F7CA18, ShapeFlags.NOZBUFFER );
			if (line)
			{
				shapes.Insert(line);
			}
		}
	}
	
	static void AddMarker(vector pos)
	{
		if (!m_linkedHouse)
			return;
		
		if (m_marker)
		{
			m_marker.Destroy();
		}
		
		m_marker = Debug.DrawSphere(pos, 0.05);
		
		vector relPos = m_linkedHouse.WorldToModel(pos);
		GetGame().CopyToClipboard(relPos[0].ToString() + ", " + relPos[1].ToString() + ", " + relPos[2].ToString());
	}
	
	static void RelativePos(vector pos)
	{
		vector relPos = m_linkedHouse.WorldToModel(pos);
		GetGame().CopyToClipboard(relPos[0].ToString() + ", " + relPos[1].ToString() + ", " + relPos[2].ToString());
	}
	
	static void RelativeRot(vector rot)
	{
		vector houseRot = m_linkedHouse.GetLocalYawPitchRoll();
		float yaw = houseRot[0] - rot[0];
		GetGame().CopyToClipboard(yaw.ToString());
	}
	
	static void GetDoorID(int componentIndex)
	{
		int doorIndex = m_linkedHouse.GetDoorIndex(componentIndex);
		GetGame().CopyToClipboard(doorIndex.ToString());
	}
	
	static void Ruler(vector pos)
	{
		if (!m_linkedHouse)
			return;
		
		if (m_rulerCache == "0 0 0")
		{
			m_rulerCache = pos;
			while (m_rulerShapes.Count() > 0)
			{
				m_rulerShapes.Get(0).Destroy();
				m_rulerShapes.Remove(0);
			}
			
			Shape m1 = Debug.DrawSphere(pos, 0.05);
			if (m1)
			{
				m_rulerShapes.Insert(m1);
			}
		}
		else
		{
			Shape m2 = Debug.DrawSphere(pos, 0.05);
			if (m2)
			{
				m_rulerShapes.Insert(m2);
			}
			
			Shape m3 = Debug.DrawLine(pos, m_rulerCache, 0x99F7CA18, ShapeFlags.NOZBUFFER);
			if (m3)
			{
				m_rulerShapes.Insert(m3);
			}
			
			GetGame().CopyToClipboard( Math.AbsFloat(pos[0] - m_rulerCache[0]).ToString() + ", " + Math.AbsFloat(pos[1] - m_rulerCache[1]).ToString() + ", " + Math.AbsFloat(pos[2] - m_rulerCache[2]).ToString() );
			m_rulerCache = "0 0 0";
		}
	}
};

class DebugBuildingTool : ItemBase
{	
	int m_currentAction;
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		
		m_currentAction = 0;
		RegisterNetSyncVariableInt("m_currentAction", 0, 99);
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionDebugBuildingToolNext);
		AddAction(ActionDebugBuildingToolLink);
		AddAction(ActionDebugBuildingToolMarker);
		AddAction(ActionDebugBuildingToolObjPos);
		AddAction(ActionDebugBuildingToolObjRot);
		AddAction(ActionDebugBuildingToolDoorID);
		AddAction(ActionDebugBuildingToolSizer);
	}
	
	void NextAction()
	{
		m_currentAction = m_currentAction + 1;
		if (m_currentAction >= 6)
		{
			m_currentAction = 0;
		}
		
		SetSynchDirty();
	}
	
	int GetActionID()
	{
		return m_currentAction;
	}
	
	override bool NameOverride(out string output)
	{
		output = "DBT MOD " + GetActionID();		
		return true;
	}
};