modded class Screwdriver
{
	override bool IsMeleeFinisher()
	{
		return false;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionMineTreeBark);
	}
}