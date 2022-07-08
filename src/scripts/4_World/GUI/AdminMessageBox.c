class AdminMessageBox extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
	string m_text = "";
	float m_timer = 0;
	
	ref ButtonWidget m_adminMsgActionBtn;
	ref MultilineTextWidget m_textWidget;
	EffectSound m_sound;
	
	void AdminMessageBox(string text)
	{
		m_text = text;
		m_dirty = true;
	}

	override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/AdminMessageBox.layout" );
		
		// Init admin message
		m_adminMsgActionBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget("AdminMsgActionBtn") );	
		m_textWidget = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget("AdminMsgContext") );
		m_active = true;
        return layoutRoot;
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		m_timer = m_timer + timeslice;
		
		if (m_dirty)
		{
			m_dirty = false;
			m_textWidget.SetText(m_text);
			GetGame().GetPlayer().PlaySoundSet(m_sound, "adminMessage_SoundSet", 0, 0);
		}
		
		if (!m_active)
		{
			GetGame().GetUIManager().Back();
		}
	}
	
	override void OnShow()
	{
		super.OnShow();

		GetGame().GetInput().ChangeGameFocus(1);

		SetFocus( layoutRoot );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(true);
		player.GetActionManager().EnableActions(false);
	}

	override void OnHide()
	{
		super.OnHide();

		GetGame().GetInput().ResetGameFocus();
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
		player.GetActionManager().EnableActions(true);

		Close();
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{					
			if (w == m_adminMsgActionBtn)
			{				
				if (m_timer > 3)
				{
					m_active = false;
				}
			}
		}
		
		return false;
	}
};