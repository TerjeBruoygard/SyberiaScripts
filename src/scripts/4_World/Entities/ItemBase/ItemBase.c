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
	
	bool IsInventoryBlocked()
	{
		return false;
	}
	
	string GetDisplayPrice()
	{
		float price = GetPrice();
		int intPrice = (int)(price * 100.0);
		return intPrice.ToString();
	}
	
	float GetPrice()
	{
		return 2.4;
	}
};