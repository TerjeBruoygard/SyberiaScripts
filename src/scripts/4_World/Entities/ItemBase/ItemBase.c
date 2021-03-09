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
};