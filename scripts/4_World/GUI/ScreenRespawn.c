class ScreenRespawn extends UIScriptedMenu
{
	bool m_visible;
	string m_charName;
	int m_totalSouls;
	int m_priceSouls;
	
	ref TextWidget m_charNameText;
	ref TextWidget m_soulsCounterText;
	ref TextWidget m_soulsPriceText;
	ref ButtonWidget m_respawnBtn;
	ref ButtonWidget m_removeCharBtn;
	
	void ScreenRespawn(string charName, int totalSouls, int priceSouls)
	{
		m_charName = charName;
		m_totalSouls = totalSouls;
		m_priceSouls = priceSouls;
		m_visible = false;
	}
	
	void ~ScreenRespawn()
	{

	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenRespawn.layout" );

		m_charNameText = TextWidget.Cast( layoutRoot.FindAnyWidget( "NameLabel" ) );
		m_soulsCounterText = TextWidget.Cast( layoutRoot.FindAnyWidget( "SoulsCounter" ) );
		m_soulsPriceText = TextWidget.Cast( layoutRoot.FindAnyWidget( "RespPrice" ) );
		
		m_respawnBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "RespawnBtn" ) );
		m_removeCharBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "RemoveCharBtn" ) );
		
		
		m_charNameText.SetText(m_charName);
		m_soulsCounterText.SetText("" + m_totalSouls);
		m_soulsPriceText.SetText("#syb_resp_price " + m_priceSouls);

        return layoutRoot;
    }
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
	}

	override void OnShow()
	{
		SybLog("ScreenRespawn OnShow");
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
		SybLog("ScreenRespawn OnHide");
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