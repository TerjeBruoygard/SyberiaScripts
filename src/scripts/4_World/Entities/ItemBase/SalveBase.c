class SalveBase : Inventory_Base
{
    override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionUseSalveTarget);
		AddAction(ActionUseSalveSelf);
	}
};