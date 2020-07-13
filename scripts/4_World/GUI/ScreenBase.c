class ScreenBase extends UIScriptedMenu
{
	bool m_visible = false;

	override void OnShow()
	{
		super.OnShow();

		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetMission().GetHud().Show(false);
		GetGame().GetSoundScene().SetSoundVolume(0, 0);

		SetFocus( layoutRoot );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player) player.GetInputController().SetDisabled(true);
		
		m_visible = true;
	}

	override void OnHide()
	{
		super.OnHide();

		GetGame().GetSoundScene().SetSoundVolume(1, 0);
		GetGame().GetInput().ResetGameFocus();
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player) player.GetInputController().SetDisabled(false);

		super.Close();
		m_visible = false;
	}
}