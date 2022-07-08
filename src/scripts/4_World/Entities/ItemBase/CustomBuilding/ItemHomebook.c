class ItemHomebook : Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionHomebookClaimOwnership);
	}
};