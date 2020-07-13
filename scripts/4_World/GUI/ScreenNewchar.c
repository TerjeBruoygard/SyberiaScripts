class ScreenNewchar extends ScreenBase
{
	string m_charName;
	int m_totalPoints;
	
	const int m_maxNameLength = 32;
	
	ref EditBoxWidget m_charNameEdit;
	ref ButtonWidget m_NextBtn;
	
	void ScreenNewchar(string charName, int points)
	{
		m_charName = charName;
		m_totalPoints = points;
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

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{
			if (w == m_NextBtn)
			{
				m_NextBtn.Show(false);
				
				auto requestParams = new Param1<string>(m_charNameEdit.GetText()); 
				GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_CREATENEWCHAR_REQUEST, requestParams);
				return true;
			}
		}
		
		return false;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		super.OnChange(w, x, y, finished);
		
		string text;
		if (w.GetName() == m_charNameEdit.GetName()) {
			text = m_charNameEdit.GetText();
			if (text.LengthUtf8() > m_maxNameLength) {
				m_charNameEdit.SetText(text.Substring(0, m_maxNameLength));
			}
			return true;
		}
		
		return false;
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key) {
		string text;
		if (w.GetName() == m_charNameEdit.GetName()) {
			text = m_charNameEdit.GetText();
			if (text.LengthUtf8() >= m_maxNameLength) {
				return true;
			}
		}

		return false;
	}
}