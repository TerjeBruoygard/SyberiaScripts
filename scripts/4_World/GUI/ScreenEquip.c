class ScreenEquip extends ScreenBase
{
	ref PlayerPreviewWidget m_playerPreview;
	ref ButtonWidget m_StartBtn;
	
	void ScreenEquip()
	{

	}
	
	void ~ScreenEquip()
	{

	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenEquip.layout" );

		m_playerPreview = PlayerPreviewWidget.Cast( layoutRoot.FindAnyWidget( "PlayerPreview" ) );
		m_StartBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "StartBtn" ) );
	
		m_playerPreview.SetPlayer(GetGame().GetPlayer());		
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
			if (w == m_StartBtn)
			{
				m_StartBtn.Show(false);
				
				auto requestParams = new Param1<int>(0); 
				GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_STARTGAME_REQUEST, requestParams);
				return true;
			}
		}
		
		return false;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		super.OnChange(w, x, y, finished);
		return false;
	}
}