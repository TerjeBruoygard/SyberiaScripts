modded class InGameMenu extends UIScriptedMenu
{
	protected override void OnClick_Respawn()
	{
		GameRespawn(true);
	}
	
	override void MenuRequestRespawn(UIScriptedMenu menu, bool random)
	{
		GameRespawn(random);
	}
}
