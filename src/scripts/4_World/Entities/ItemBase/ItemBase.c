modded class ItemBase
{
	override void SetActions()
	{
		super.SetActions();		
		AddAction(ActionCutBookPage);
	}

	bool IsTemperatureVisible()
	{
		return CanHaveTemperature();
	}
	
	bool IsCleanness()
	{
		return m_Cleanness == 1;
	}
};