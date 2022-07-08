class SyberiaAdditionalHud
{
	ref Widget m_actionBlocker;
	ref TextWidget m_actionBlockerText;
	bool m_actionBlockerVisible;
	
	ref Widget m_mainHud;
	ref GridSpacerWidget m_defaultActionMenu;

	void SyberiaAdditionalHud(ref Widget mainHud, ref Widget actionBlocker)
	{
		m_mainHud = mainHud;
		m_actionBlocker = actionBlocker;
		m_actionBlockerText = null;
		m_actionBlockerVisible = false;
	}
	
	void ~SyberiaAdditionalHud()
	{
		
	}

	void Init()
	{
		// Init action blocker
		m_defaultActionMenu = GridSpacerWidget.Cast( m_mainHud.FindAnyWidget("ItemActions") );
		m_actionBlockerText = TextWidget.Cast( m_actionBlocker.FindAnyWidget("ia_block_interact_action_name") );
	}
	
	void Refresh()
	{
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
}