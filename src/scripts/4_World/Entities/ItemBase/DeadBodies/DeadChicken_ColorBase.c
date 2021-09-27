modded class DeadChicken_ColorBase
{
	override bool CanBeSkinned()
	{
		return true;
	}
	
	override bool IsInventoryVisible()
	{
		return IsSkinned();
	}
	
	override bool IsSkinned()
	{
		return CanBeSkinned() && m_alreadySkinned;
	}
};