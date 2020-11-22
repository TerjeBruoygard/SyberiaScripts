class SurgicalKit extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionSurgeryTarget);
		AddAction(ActionSurgerySelf);
	}
};