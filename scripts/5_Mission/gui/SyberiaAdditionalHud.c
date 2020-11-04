class SyberiaAdditionalHud
{
	ref Widget m_AdditionHudRootWidget = null;
	ref Widget m_actionBlocker;
	ref TextWidget m_actionBlockerText;
	bool m_actionBlockerVisible;
	
	ref Widget m_mainHud;
	ref GridSpacerWidget m_defaultActionMenu;
		
	bool m_visible;

	void SyberiaAdditionalHud(ref Widget mainHud)
	{
		m_mainHud = mainHud;
		m_AdditionHudRootWidget = null;
		m_actionBlocker = null;
		m_actionBlockerText = null;
		m_visible = false;
		m_actionBlockerVisible = false;
	}
	
	void ~SyberiaAdditionalHud()
	{
		if (m_AdditionHudRootWidget) delete m_AdditionHudRootWidget;
	}

	void Init()
	{
		SybLog("SyberiaAdditionalHud Init");
		
		m_defaultActionMenu = GridSpacerWidget.Cast( m_mainHud.FindAnyWidget("ItemActions") );
		
		m_AdditionHudRootWidget = GetGame().GetWorkspace().CreateWidgets("SyberiaScripts/layout/AdditionalHud.layout");
		m_AdditionHudRootWidget.Show(false);
		
		m_actionBlocker = m_AdditionHudRootWidget.FindAnyWidget("ActionBlocker");
		m_actionBlockerText = TextWidget.Cast( m_actionBlocker.FindAnyWidget("ia_block_interact_action_name") );
		m_AdditionHudRootWidget.RemoveChild(m_actionBlocker);
	}

	void Refresh()
	{
		if( !m_visible ) 
		{
			m_visible = true;
			m_AdditionHudRootWidget.Show(true);
		}
		
		RefreshActionBlocker();
	}
	
	void RefreshActionBlocker()
	{		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		ActionManagerBase actionManager = player.GetActionManager();
		
		int deltaBlocker = GetGame().GetTime() - actionManager.m_ActionBlockerTimeStamp;
		if (actionManager.m_ActionBlockerText.Length() > 0 && deltaBlocker < 200)
		{
			if (!m_actionBlockerVisible) {
				m_defaultActionMenu.AddChild(m_actionBlocker);
				m_actionBlockerVisible = true;
			}
			m_actionBlockerText.SetText(actionManager.m_ActionBlockerText);
		}
		else if (m_actionBlockerVisible)
		{
			m_defaultActionMenu.RemoveChild(m_actionBlocker);
			m_actionBlockerVisible = false;
		}
	}
	
	void Hide()
	{
		if( !m_visible )
			return;
		
		m_visible = false;
		m_AdditionHudRootWidget.Show(false);
	}
}