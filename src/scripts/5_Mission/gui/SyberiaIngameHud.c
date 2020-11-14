modded class IngameHud
{
	protected ref Widget m_panelSleepingStatus;
	
	void InitSleepingNotifier(ref Widget sleepingWidget)
	{
		m_panelSleepingStatus = sleepingWidget;
		InitNotifierWidget(NTFKEY_SLEEPING, sleepingWidget);
	}
	
	protected void InitNotifierWidget(int id, ref Widget notifierWidget)
	{
		string name = notifierWidget.GetName();
		m_StatesWidgetNames.Set( id, name );
		
		Widget defaultNotifiersPanel = m_HudPanelWidget.FindAnyWidget("NotifiersPanel");
		Widget defaultBadgesSpacer = m_HudPanelWidget.FindAnyWidget("BadgesSpacer");
		Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
		
		int widgetOffsetX = 150;
		int widgetWidth = 35;
		
		float x, y;
		defaultNotifiersPanel.GetSize(x, y);
		defaultNotifiersPanel.SetSize(x + widgetWidth, y);
		
		defaultNotifiersPanel.AddChild(notifierWidget);
		notifierWidget.SetPos(widgetOffsetX, 0);
		notifierWidget.Show(true);
		
		defaultBadgesSpacer.GetPos(x, y);
		defaultBadgesSpacer.SetPos(x + widgetWidth, y);
		
		defaultBadgesPanel.GetPos(x, y);
		defaultBadgesPanel.SetPos(x + widgetWidth, y);
		
		ref ImageWidget imagew = notifierWidget.FindAnyWidget("Icon" + name); 
		m_StatesWidgets.Set(id, imagew);
		for ( int i = 0; i < 5; i++ )
		{
			imagew.LoadImageFile( i, "SyberiaScripts/data/gui/" + name + "/icon" + i + ".paa");
		}		
	}
}