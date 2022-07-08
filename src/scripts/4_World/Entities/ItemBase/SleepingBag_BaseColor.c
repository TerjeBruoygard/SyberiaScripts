class SleepingBag_BaseColor : ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(SyberiaActionPlacementPreview);
		AddAction(SyberiaActionPlacementApply);
	}

	override bool DoPlacingHeightCheck()
	{
		return true;
	}
	
	override float HeightCheckOverride()
	{
		return 0.5;
	}
};

class SleepingBagPlaced_BaseColor : BaseBuildingBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionFoldBaseBuildingObject);
	}
	
	protected override string GetConstructionKitType()
	{
		return GetGame().ConfigGetTextOut("CfgVehicles " + GetType() + " packedName");
	}
	
	override ItemBase CreateConstructionKit()
	{
		ItemBase result = super.CreateConstructionKit();
		if (result)
		{
			float health = GetHealth01("", "");
			result.SetHealth01("", "", health);
		}
		return result;
	}
};