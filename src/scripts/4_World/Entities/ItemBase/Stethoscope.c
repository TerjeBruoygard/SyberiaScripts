class Stethoscope extends Clothing
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionPlugStethoscope);
	}
};