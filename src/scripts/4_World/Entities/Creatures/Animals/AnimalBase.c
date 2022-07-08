modded class AnimalBase
{
	private bool m_allowCargoManipulation = false;
	
	override void EEInit()
	{
		super.EEInit();
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	}
	
	override bool CanBeSkinned()
	{
		return super.CanBeSkinned() && GetInventory().IsInventoryLocked() && !IsAlive();
	}
	
	override bool IsSkinned()
	{
		return GetInventory().IsInventoryUnlocked();
	}
	
	override bool IsInventoryVisible()
	{
		return IsSkinned();
	}
	
	override bool CanPutInCargo( EntityAI parent )
	{
		return m_allowCargoManipulation;
	}
	
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		return m_allowCargoManipulation;
	}
	
	override bool CanLoadItemIntoCargo(EntityAI item)
	{
		return m_allowCargoManipulation;
	}
	
	override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{
		return m_allowCargoManipulation;
	}
};