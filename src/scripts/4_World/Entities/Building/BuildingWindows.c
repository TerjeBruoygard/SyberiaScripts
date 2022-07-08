class BuildingWindowBase extends BuildingLeveledElement
{
    int m_windowId = -1;

	override void EEInit()
	{
		super.EEInit();
		
		RegisterNetSyncVariableInt("m_windowId", 0, 255);
	}
	
	int GetWindowId()
	{
		return m_windowId;
	}
};


// TYPE 1
class BuildingWindow_T1_L1 extends BuildingWindowBase
{
};

class BuildingWindow_T1_L2 extends BuildingWindowBase
{
};

class BuildingWindow_T1_L3 extends BuildingWindowBase
{
};

class BuildingWindow_T1_L4 extends BuildingWindowBase
{
};

class BuildingWindow_T1_L5 extends BuildingWindowBase
{
};


// TYPE 2
class BuildingWindow_T2_L1 extends BuildingWindowBase
{
};

class BuildingWindow_T2_L2 extends BuildingWindowBase
{
};

class BuildingWindow_T2_L3 extends BuildingWindowBase
{
};

class BuildingWindow_T2_L4 extends BuildingWindowBase
{
};

class BuildingWindow_T2_L5 extends BuildingWindowBase
{
};