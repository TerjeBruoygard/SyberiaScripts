class ScreenNewchar extends UIScriptedMenu
{
	bool m_visible;
	string m_charName;
	int m_totalPoints;
	
	ref EditBoxWidget m_charNameEdit;
	ref ButtonWidget m_NextBtn;
	
	void ScreenNewchar(string charName, int points)
	{
		m_charName = charName;
		m_totalPoints = points;
		m_visible = false;
	}
	
	void ~ScreenNewchar()
	{

	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenNewchar.layout" );

		m_charNameEdit = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "CharNameEdit" ) );

		m_NextBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "NextBtn" ) );
		
		
		m_charNameEdit.SetText(m_charName);
		
        return layoutRoot;
    }
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
	}

	override void OnShow()
	{
		SybLog("ScreenNewchar OnShow");
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
		SybLog("ScreenNewchar OnHide");
		super.OnHide();

		GetGame().GetSoundScene().SetSoundVolume(1, 0);
		GetGame().GetInput().ResetGameFocus();
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player) player.GetInputController().SetDisabled(false);

		super.Close();
		m_visible = false;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		return false;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		super.OnChange(w, x, y, finished);
		return false;
	}
}