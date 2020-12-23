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
	
	override string GetDeploySoundset()
	{
		return "sbegDeploy_SoundSet";
	}
	
	override string GetLoopDeploySoundset()
	{
		return "sbegDeployLoop_SoundSet";
	}
};

class SleepingBagPlaced_BaseColor : BaseBuildingBase
{

};