modded class Edible_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionWashFruitsWell);
		AddAction(ActionWashFruitsWater);
	}
};