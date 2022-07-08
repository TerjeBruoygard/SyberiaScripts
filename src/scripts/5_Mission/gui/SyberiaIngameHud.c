modded class IngameHud
{
	void InitNotifierWidget(int id, ref Widget baseWidget, string name)
	{
		ref Widget notifierWidget = baseWidget.FindAnyWidget(name);
		baseWidget.RemoveChild(notifierWidget);
		
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
	
	void InitBadgetWidget(int id, ref Widget baseWidget, string name)
	{
		ref Widget badge_widget = baseWidget.FindAnyWidget(name);
		baseWidget.RemoveChild(badge_widget);
		m_Badges.AddChild(badge_widget);
		
		m_BadgesWidgetNames.Set( id, name );
		m_BadgesWidgets.Set( id, badge_widget );
		badge_widget.Show( false );
		m_BadgesWidgetDisplay.Set( id, 0 );
	}
	
	override void DisplayBadge( int key, int value )
	{
		if (m_BadgesWidgetDisplay.Get( key ) == value)
		{
			return;
		}
		
		super.DisplayBadge(key, value);
		
		string badge_name = m_BadgesWidgetNames.Get( key );
		TextWidget w_count = TextWidget.Cast( m_Badges.FindAnyWidget( badge_name + "Count" ) );
		if (w_count)
		{
			w_count.SetText( value.ToString() );
		}
	}
}