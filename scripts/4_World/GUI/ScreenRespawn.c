class ScreenRespawn extends ScreenBase
{
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