class BuildingDoorBase extends BuildingLeveledElement
{
	int m_doorId = -1;
	int m_linkedDoorId = -1;
	
	override void EEInit()
	{
		super.EEInit();
		
		RegisterNetSyncVariableInt("m_doorId", 0, 255);
		RegisterNetSyncVariableInt("m_linkedDoorId", 0, 255);
	}
};

class BuildingDoor_T1_L1 extends BuildingDoorBase
{
};

class BuildingDoor_T1_L2 extends BuildingDoorBase
{
};

class BuildingDoor_T1_L3 extends BuildingDoorBase
{
};

class BuildingDoor_T1_L4 extends BuildingDoorBase
{
};

class BuildingDoor_T1_L5 extends BuildingDoorBase
{
};