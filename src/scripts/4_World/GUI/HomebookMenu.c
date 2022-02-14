class HomebookMenu extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
	ref array<string> m_tabsMapping;
	int m_currentTab = 0;
	int m_currentDoor = 0;
	
	ref ScrollWidget m_doorsListPanel, m_doorsItemsPanel;
	ref array<ref Widget> m_doorWidgetsCache = new array<ref Widget>;
	ref array<ref Widget> m_doorItemsWidgetsCache = new array<ref Widget>;
	ref TextWidget m_doorsSelectedName, m_doorsSelectedState, m_doorsSelectedLevel, m_doorsSelectedHealth;
	
	BuildingLivespace m_livespace;
	ref LivespaceHomebookData m_data;

	void HomebookMenu(BuildingLivespace livespace, ref LivespaceHomebookData data)
	{
		m_livespace = livespace;
		m_data = data;
		m_tabsMapping = new array<string>;
	}
	
	void ~HomebookMenu()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
		delete m_tabsMapping;
		delete m_doorWidgetsCache;
		delete m_doorItemsWidgetsCache;
	}

    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/HomebookMenu.layout" );

		m_tabsMapping.Insert("General");
		m_tabsMapping.Insert("Doors");
		m_tabsMapping.Insert("Barricades");
		m_tabsMapping.Insert("Members");
		
		m_doorsListPanel = ScrollWidget.Cast(layoutRoot.FindAnyWidget( "DoorsListPanel" ));
		m_doorsSelectedName = TextWidget.Cast(layoutRoot.FindAnyWidget( "DoorsSelectedName" ));
		m_doorsSelectedState = TextWidget.Cast(layoutRoot.FindAnyWidget( "DoorsSelectedState" ));
		m_doorsSelectedLevel = TextWidget.Cast(layoutRoot.FindAnyWidget( "DoorsSelectedLevel" ));
		m_doorsSelectedHealth = TextWidget.Cast(layoutRoot.FindAnyWidget( "DoorsSelectedHealth" ));
		m_doorsItemsPanel = ScrollWidget.Cast(layoutRoot.FindAnyWidget( "DoorsItemsPanel" ));
		
		m_active = true;
		m_dirty = true;
        return layoutRoot;
    }

	override void Update(float timeslice)
	{
		super.Update(timeslice);

		if (m_dirty)
		{
			UpdateCurrentTab();
			m_dirty = false;
		}

		if (!m_active)
		{
			GetGame().GetUIManager().Back();
		}
	}
	
	private void UpdateCurrentTab()
	{
		for (int i = 0; i < m_tabsMapping.Count(); i++) {
			string name = m_tabsMapping.Get(i);
			Widget buttonBack = layoutRoot.FindAnyWidget( "Menu" + name + "Background" );
			Widget contentPanel = layoutRoot.FindAnyWidget( "Content" + name );
			if (i == m_currentTab) {
				buttonBack.SetColor(GetColorTabActive());
				contentPanel.Show(true);
				
				if (name == "Doors") {
					InitDoorsTab();
				}
			}
			else {
				buttonBack.SetColor(GetColorTabInactive());
				contentPanel.Show(false);
			}
		}
	}
	
	private void InitDoorsTab()
	{
		foreach (ref Widget w1 : m_doorWidgetsCache)
		{
			w1.Unlink();
		}
		m_doorWidgetsCache.Clear();
		m_doorsListPanel.VScrollToPos01(0);
		
		ref array<ref LivespaceDoorData> doorsData = m_livespace.GetData().m_doors;
		for (int i = 0; i < doorsData.Count(); i++)
		{
			ref LivespaceDoorData doorData = doorsData.Get(i);
			int doorLevel = m_livespace.GetDoorLevel(i);
			InitDoorItem(i, doorData, doorLevel);
		}
	}
	
	private void InitDoorItem(int index, ref LivespaceDoorData doorData, int doorLevel)
	{		
		ref Widget itemWidget = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/HomebookMenuItemDoor.layout" );		
		m_doorsListPanel.AddChild(itemWidget);
				
		float w, h;
		float contentWidth = m_doorsListPanel.GetContentWidth();
		itemWidget.GetSize(w, h);
		itemWidget.SetPos(0, (h + 2) * index);
		itemWidget.SetSize(contentWidth, h);
		
		ref ButtonWidget actionButton = ButtonWidget.Cast( itemWidget.FindAnyWidget( "ItemActionButton" ) );
		actionButton.SetUserID(1000 + index);
		
		string doorState;
		ref ImageWidget widgetIcon = ImageWidget.Cast( itemWidget.FindAnyWidget( "ItemIcon" ) );
		if (m_livespace.IsDoorOpen(doorData.m_selfDoorId)) {
			widgetIcon.LoadImageFile(0, "SyberiaScripts/data/gui/Homebook/icon_unlocked.paa");
			doorState = "State: Opened";		
		}
		else {
			widgetIcon.LoadImageFile(0, "SyberiaScripts/data/gui/Homebook/icon_locked.paa");
			doorState = "State: Closed";		
		}		

		string doorName = "Door " + (index + 1);
		if (doorData.m_outerDoor) {
			doorName = " (Outer)";
		}
		else {
			doorName = " (Inner)";
		}
		
		string doorHealth = "100%";
				
		ref TextWidget widgetTextName = TextWidget.Cast( itemWidget.FindAnyWidget( "ItemNameWidget" ) );
		widgetTextName.SetText(doorName);	
		
		ref TextWidget widgetTextLevel = TextWidget.Cast( itemWidget.FindAnyWidget( "ItemLevelWidget" ) );
		widgetTextLevel.SetText("Level " + doorLevel);	
		
		ref TextWidget widgetTextHealth = TextWidget.Cast( itemWidget.FindAnyWidget( "ItemHealthWidget" ) );
		widgetTextHealth.SetColor(ARGB(255, 0, 200, 0));
		widgetTextHealth.SetText("100%");
		
		if (m_currentDoor == index)
		{
			m_doorsSelectedName.SetText(doorName);
			m_doorsSelectedLevel.SetText("Level: " + doorLevel);
			m_doorsSelectedState.SetText(doorState);
			m_doorsSelectedHealth.SetText("Health: " + doorHealth);
			
			foreach (ref Widget w1 : m_doorItemsWidgetsCache)
			{
				w1.Unlink();
			}
			m_doorItemsWidgetsCache.Clear();
			m_doorsItemsPanel.VScrollToPos01(0);
		}
	}
	
	private int GetColorTabInactive()
	{
		return ARGB(200, 25, 25, 25);
	}
	
	private int GetColorTabActive()
	{
		return ARGB(225, 14, 14, 14);
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		for (int i = 0; i < m_tabsMapping.Count(); i++) {
			if (w.GetName() == "Menu" + m_tabsMapping.Get(i) + "Btn") {
				m_currentTab = i;
				m_dirty = true;
			}
		}
		
		int userId = w.GetUserID();
		if (userId >= 1000 && userId < 2000) {
			m_currentDoor = userId - 1000;
			m_dirty = true;
		}
		
		/*if (w == m_activatePerkBtn)
		{
			
		}*/
		
		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int  column,	int  oldRow, int  oldColumn)
	{
		return super.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
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
};