modded class ZombieBase
{
	bool m_isInventoryBlocked = true;
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableBool("m_isInventoryBlocked");
	}
	
	override bool IsInventoryVisible()
	{
		return !m_isInventoryBlocked;
	}
	
	bool IsInventoryBlocked()
	{
		return m_isInventoryBlocked;	
	}
	
	void UnlockInventory()
	{
		m_isInventoryBlocked = false;
		SetSynchDirty();
	}
};