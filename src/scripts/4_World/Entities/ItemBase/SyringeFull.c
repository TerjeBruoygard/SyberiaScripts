class SyringeFull extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionEmptySyringe);		
		AddAction(ActionInjectSyringeSelf);
		AddAction(ActionInjectSyringeTarget);
	}
	
	override bool CanBeDisinfected()
	{
		return false;
	}
};