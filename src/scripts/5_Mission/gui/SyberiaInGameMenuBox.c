modded class InGameMenuXbox extends UIScriptedMenu
{
	override void MenuRequestRespawn(UIScriptedMenu menu, bool random)
	{
		GameRetry(random);
	}
}
