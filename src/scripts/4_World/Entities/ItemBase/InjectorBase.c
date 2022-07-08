class InjectorBase : Inventory_Base
{
    override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectInjectorTarget);
		AddAction(ActionInjectInjectorSelf);
	}
};