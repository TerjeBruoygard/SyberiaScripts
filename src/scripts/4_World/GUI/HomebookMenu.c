class HomebookMenu extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
	ref array<string> m_tabsMapping;
	int m_currentTab = 0;
	
	ref ScrollWidget m_doorsListPanel;
	ref array<ref Widget> m_doorWidgetsCache = new array<ref Widget>;
	
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
	}

    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/HomebookMenu.layout" );

		m_tabsMapping.Insert("General");
		m_tabsMapping.Insert("Doors");
		m_tabsMapping.Insert("Barricades");
		m_tabsMapping.Insert("Members");
		
		m_doorsListPanel = ScrollWidget.Cast(layoutRoot.FindAnyWidget( "DoorsListPanel" ));
		
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
			}
			else {
				buttonBack.SetColor(GetColorTabInactive());
				contentPanel.Show(false);
			}
		}
	}
	
	private void InitDoors()
	{
		foreach (ref Widget w1 : m_doorWidgetsCache)
		{
			w1.Unlink();
		}
		m_doorWidgetsCache.Clear();
		m_buyItemsPanel.VScrollToPos01(0);
		
		ref array<ref LivespaceDoorData> doorsData = livespace.GetData().m_doors;
		for (int i = 0; i < doorsData.Count(); i++)
		{
			ref LivespaceDoorData doorData = doorsData.Get(i);
			int doorLevel = livespace.GetDoorLevel(i);
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
		//actionButton.SetUserData(item);
		//actionButton.SetUserID(1001);
		
		ref ImageWidget widgetIcon = ImageWidget.Cast( itemWidget.FindAnyWidget( "ItemIcon" ) );		
		widgetIcon.LoadImageFile(0, "SyberiaScripts/data/gui/Homebook/icon_door.paa");
		
		ref TextWidget widgetText = TextWidget.Cast( itemWidget.FindAnyWidget( "ItemNameWidget" ) );	
		widgetText.SetText("Outer door " + (index + 1));	
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