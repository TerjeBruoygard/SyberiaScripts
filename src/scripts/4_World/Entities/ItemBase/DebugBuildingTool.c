class DebugBuildingManager
{
	static House m_linkedHouse;
	static Shape m_linkedHouseShape;
	static Shape m_marker;
	
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
		if (m_linkedHouseShape)
		{
			m_linkedHouseShape.Destroy();
		}
		
		if (m_marker)
		{
			m_marker.Destroy();
		}
		
		m_linkedHouse = house;		
		
		vector minMax[2];
		if (house.ClippingInfo(minMax) > 0)
		{
			minMax[0] = house.ModelToWorld(minMax[0]);
			minMax[1] = house.ModelToWorld(minMax[1]);
			m_linkedHouseShape = Debug.DrawBox(minMax[0], minMax[1], 0x1FFFFF4A);
			if (m_linkedHouseShape)
			{
				m_linkedHouseShape.SetDirection(house.GetDirection());
			}
		}
		
		GetGame().CopyToClipboard(house.GetType());
	}
	
	static void AddMarker(vector pos)
	{
		if (!m_linkedHouseShape)
			return;
		
		if (m_marker)
		{
			m_marker.Destroy();
		}
		
		m_marker = Debug.DrawSphere(pos, 0.05);
		
		vector relPos = m_linkedHouse.WorldToModel(pos);
		GetGame().CopyToClipboard("[" + relPos[0] + ", " + relPos[1] + ", " + relPos[2] + "]");
	}
	
	static void RelativePos(vector pos)
	{
		vector relPos = m_linkedHouse.WorldToModel(pos);
		GetGame().CopyToClipboard("[" + relPos[0] + ", " + relPos[1] + ", " + relPos[2] + "]");
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
	}
	
	void NextAction()
	{
		m_currentAction = m_currentAction + 1;
		if (m_currentAction >= 3)
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