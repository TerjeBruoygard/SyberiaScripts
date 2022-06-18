class ScreenBase extends UIScriptedMenu
{
	bool m_isShown = false;
	bool m_isClosed = false;

	override void OnShow()
	{
		super.OnShow();

		GetGame().GetInput().ChangeGameFocus(1);
		GetGame().GetSoundScene().SetSoundVolume(0, 0);

		SetFocus( layoutRoot );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player) player.GetInputController().SetDisabled(true);
		
		GetGame().GetMission().GetHud().Show(false);
		GetGame().GetUIManager().ShowCursor(true);
		
		m_isShown = true;
		
		SybLog("Show " + this);
	}

	override void OnHide()
	{
		super.OnHide();

		GetGame().GetSoundScene().SetSoundVolume(1, 0);
		GetGame().GetInput().ResetGameFocus();
		
		GetGame().GetUIManager().ShowCursor(false);
		if (GetGame().GetMission() && GetGame().GetMission().GetHud())
		{
			GetGame().GetMission().GetHud().Show(true);
		}
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player) player.GetInputController().SetDisabled(false);

		m_isClosed = true;
		
		SybLog("Hide " + this);
	}
}