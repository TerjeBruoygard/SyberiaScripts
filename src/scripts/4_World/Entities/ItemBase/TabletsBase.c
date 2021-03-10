class TabletsBase extends Edible_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionForceConsumeSingle);
		AddAction(ActionConsumeSingle);
	}
	
	override bool CanHaveTemperature()
	{
		return false;
	}
};