modded class ZombieBase extends DayZInfected
{
	override bool IsInventoryVisible()
	{
		return GetInventory().IsInventoryUnlocked();
	}
};