class AdminToolMenu extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
		
	int m_selectedTabId = 0;
	ref array<ref Widget> m_tabButtons;
	ref array<ref Widget> m_tabBodies;
	ref PluginAdminTool_OpenContext m_context;
	
	// Players
	ref PluginAdminTool_PlayerContextDetails m_playerContext;
	ref Widget m_playersDataRefresh;
	ref Widget m_playersDataDelete;
	ref Widget m_playersDataKick;
	ref Widget m_playersDataTeleportToPlayer;
	ref Widget m_playersDataTeleportPlayerToMe;
	ref TextListboxWidget m_playersListBox;
	ref TextListboxWidget m_playersDataInfo;
	ref TextListboxWidget m_playersDataStats;
	ref TextListboxWidget m_playersDataInv;
	ref TextWidget m_playersStatEditText;
	ref EditBoxWidget m_playersStatEditBox;		
	ref TextWidget m_playersMsgEditText;
	ref EditBoxWidget m_playersMsgEditBox;	
	ref ButtonWidget m_playersMsgApply;	
	ref Widget m_playersStatApply;
	string m_selectedPlayerUID;
	
	// Spawner
	static ref map<string, ref array<string>> m_cachedConfigItems = new map<string, ref array<string>>;
	static ref map<string, ref array<string>> m_cachedAttachments = new map<string, ref array<string>>;
	ref TextListboxWidget m_spawnerCategoryListBox;
	ref TextListboxWidget m_spawnerItemsListBox;
	ref TextWidget m_spawnerFilterEditText;
	ref EditBoxWidget m_spawnerFilterEditBox;
	ref SliderWidget m_spawnerSliderHealth;
	ref SliderWidget m_spawnerSliderQuantity;
	ref XComboBoxWidget m_spawnerTypeSelect;
	ref CheckBoxWidget m_spawnerFillProxies;
	ref TextListboxWidget m_spawnerProxySlotSelect;
	ref TextListboxWidget m_spawnerProxySlotType;
	ref ButtonWidget m_spawnButton;
	ref ButtonWidget m_spawnerClear;
	static int m_spawnerSelectedCategory = 0;
	static int m_spawnerSelectedItem = 0;
	static float m_spawnerSelectedHealth = 100;
	static float m_spawnerSelectedQuantity = 100;
	static float m_spawnerSelectedSpawnType = 0;
	static bool m_spawnerFillProxiesChecked = false;
	static int m_spawnerProxySlotSelectedAttachment = -1;
	static string m_spawnerFilterCache = "";
	static ref array<int> m_spawnerProxySlotsSelections = new array<int>;
	
	// Map
	ref MapWidget m_mapWidget;
	static vector m_mapPos = "0 0 0";
	static float m_mapScale = 0.1;
	
	// Freecam
	ref CheckBoxWidget m_toolsFreeCamToggle;
	static bool m_toolsFreeCamToggleChecked = false;
	
	// Esp
	ref CheckBoxWidget m_toolsEspPlayers;
	ref CheckBoxWidget m_toolsEspDeadBodies;
	ref CheckBoxWidget m_toolsEspVehicles;
	ref SliderWidget m_toolsEspSliderDist1;	
	ref CheckBoxWidget m_toolsEspLoot;
	ref SliderWidget m_toolsEspSliderDist2;	
	ref TextWidget m_toolsEspFilterText;
	ref EditBoxWidget m_toolsEspFilterBox;
	ref array<ref CheckBoxWidget> m_toolsEspLootCategories;
	static bool m_toolsEspPlayersChecked = false;
	static bool m_toolsEspDeadBodiesChecked = false;
	static bool m_toolsEspVehiclesChecked = false;
	static bool m_toolsEspLootChecked = false;
	static float m_toolsEspSliderDist1Value = 1000;
	static float m_toolsEspSliderDist2Value = 100;
	static string m_toolsEspFilterValue = "";
	static ref array<bool> m_toolsEspLootCategoriesSelections = null;
	static ref array<string> m_toolsEspLootCategoriesNames = null;
	static ref array<typename> m_toolsEspLootCategoriesFilter = null;
	static ref array<int> m_toolsEspLootCategoriesColor = null;
	
	// Objects
	ref ButtonWidget m_toolsObjectsRefresh;
	ref ButtonWidget m_toolsObjectsDelete;
	ref TextListboxWidget m_toolsObjectsList;
	ref array<ref ButtonWidget> m_toolsObjectsCtls;
	ref array<ref TextWidget> m_toolsObjectsInfo;
	
	void AdminToolMenu()
	{
		m_tabButtons = new array<ref Widget>;
		m_tabBodies = new array<ref Widget>;
		m_toolsObjectsCtls = new array<ref ButtonWidget>;
		m_toolsObjectsInfo = new array<ref TextWidget>;
	}
	
	void ~AdminToolMenu()
	{
		delete m_tabButtons;
		delete m_tabBodies;
		
		if (m_toolsObjectsCtls) delete m_toolsObjectsCtls;
		if (m_toolsObjectsInfo) delete m_toolsObjectsInfo;
		if (m_context) delete m_context;
		if (m_playerContext) delete m_playerContext;
		if (m_toolsEspLootCategories) delete m_toolsEspLootCategories;

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
	}

	void UpdateServerContext(ref PluginAdminTool_OpenContext context)
	{
		if (m_context) delete m_context;
		m_context = context;
		m_dirty = true;		
	}
	
	void UpdatePlayerContext(ref PluginAdminTool_PlayerContextDetails context)
	{
		if (m_playerContext) delete m_playerContext;
		m_playerContext = context;
		m_dirty = true;		
	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/AdminToolMenu.layout" );		
		
		// Players tab
		m_playersListBox = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PlayersListBox"));
		m_playersDataInfo = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PlayersDataInfoList"));
		m_playersDataStats = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PlayersDataStatsList"));
		m_playersDataInv = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PlayersDataInv"));
		m_playersDataRefresh = layoutRoot.FindAnyWidget("PlayersDataRefresh");		
		m_playersDataDelete = layoutRoot.FindAnyWidget("PlayersDataDelete");
		m_playersDataKick = layoutRoot.FindAnyWidget("PlayersDataKick");
		m_playersDataTeleportToPlayer = layoutRoot.FindAnyWidget("PlayersDataTeleportToPlayer");
		m_playersDataTeleportPlayerToMe = layoutRoot.FindAnyWidget("PlayersDataTeleportPlayerToMe");		
		m_playersStatEditText = TextWidget.Cast(layoutRoot.FindAnyWidget("PlayersStatEditText"));
		m_playersStatEditBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlayersStatEditBox"));		
		m_playersMsgEditText = TextWidget.Cast(layoutRoot.FindAnyWidget("PlayersMsgEditText"));
		m_playersMsgEditBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlayersMsgEditBox"));		
		m_playersStatApply = layoutRoot.FindAnyWidget("PlayersDataStatsApply");
		m_playersMsgApply = ButtonWidget.Cast(layoutRoot.FindAnyWidget("PlayersMsgApply"));
		
		// Spawner tab
		m_spawnerCategoryListBox = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("SpawnerCategoryListBox"));
		m_spawnerItemsListBox = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("SpawnerItemsListBox"));
		m_spawnerFilterEditText = TextWidget.Cast(layoutRoot.FindAnyWidget("SpawnerFilterEditText"));
		m_spawnerFilterEditBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SpawnerFilterEditBox"));			
		m_spawnerSliderHealth = SliderWidget.Cast(layoutRoot.FindAnyWidget("SpawnerSliderHealth"));
		m_spawnerSliderQuantity = SliderWidget.Cast(layoutRoot.FindAnyWidget("SpawnerSliderQuantity"));
		m_spawnerTypeSelect = XComboBoxWidget.Cast(layoutRoot.FindAnyWidget("SpawnerTypeSelect"));
		m_spawnerFillProxies = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("SpawnerFillProxies"));
		m_spawnerProxySlotSelect = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("SpawnerProxySlotSelect"));
		m_spawnerProxySlotType = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("SpawnerProxySlotType"));
		m_spawnButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("SpawnerAction"));
		m_spawnerClear = ButtonWidget.Cast(layoutRoot.FindAnyWidget("SpawnerClear"));
		
		m_spawnerSliderHealth.SetCurrent(m_spawnerSelectedHealth);
		m_spawnerSliderQuantity.SetCurrent(m_spawnerSelectedQuantity);
		m_spawnerTypeSelect.SetCurrentItem( m_spawnerSelectedSpawnType );
		m_spawnerFillProxies.SetChecked( m_spawnerFillProxiesChecked );
		m_spawnerFilterEditText.SetText( m_spawnerFilterCache );
		m_spawnerFilterEditBox.SetText( m_spawnerFilterCache );
		
		InitItemsConfig("CfgVehicles");
		InitItemsConfig("CfgWeapons");
		InitItemsConfig("CfgMagazines");
		
		// Map
		m_mapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("MapPreview"));
		m_mapWidget.SetMapPos(m_mapPos);	
		m_mapWidget.SetScale(m_mapScale);
		
		// Freecam
		m_toolsFreeCamToggle = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ToolsFreeCamToggle"));
		m_toolsFreeCamToggle.SetChecked( m_toolsFreeCamToggleChecked );
		
		// Esp
		m_toolsEspPlayers = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspPlayers"));
		m_toolsEspDeadBodies = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspDeadBodies"));
		m_toolsEspVehicles = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspVehicles"));
		m_toolsEspSliderDist1 = SliderWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspSliderDist1"));
		m_toolsEspLoot = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspLoot"));
		m_toolsEspSliderDist2 = SliderWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspSliderDist2"));
		m_toolsEspFilterText = TextWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspFilterText"));
		m_toolsEspFilterBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ToolsEspFilterBox"));
		
		if (!m_toolsEspLootCategoriesSelections)
		{
			m_toolsEspLootCategoriesSelections = new array<bool>;
			m_toolsEspLootCategoriesFilter = new array<typename>;
			m_toolsEspLootCategoriesNames = new array<string>;
			m_toolsEspLootCategoriesColor = new array<int>;
			InitEspLootFilter("Food", Edible_Base, ARGB(255, 27, 161, 226));
			InitEspLootFilter("Base Building", BaseBuildingBase, ARGB(255, 109,135,100));
			InitEspLootFilter("Rifles", Rifle_Base, ARGB(255, 162,0,37));
			InitEspLootFilter("Pistols", Pistol_Base, ARGB(255, 162,0,37));
			InitEspLootFilter("Magazines", Magazine_Base, ARGB(255, 162,0,37));
			InitEspLootFilter("Containers", Container_Base, ARGB(255, 130,90,44));
			InitEspLootFilter("Tablets", TabletsBase, ARGB(255, 244,94,208));
			InitEspLootFilter("Ampouls", SyberiaMedicineAmpoule, ARGB(255, 244,104,208));
			InitEspLootFilter("Injectors", InjectorBase, ARGB(255, 244,114,208));
			InitEspLootFilter("Clothing", ClothingBase, ARGB(255, 27,161,226));
			InitEspLootFilter("Books", ItemBook, ARGB(255, 106,0,255));
			InitEspLootFilter("Others", ItemBase, ARGB(255, 147, 255, 0));
		}
		
		m_toolsEspLootCategories = new array<ref CheckBoxWidget>;
		for (int toolsEspLootCatId = 0; toolsEspLootCatId < m_toolsEspLootCategoriesSelections.Count(); toolsEspLootCatId++)
		{
			ref CheckBoxWidget tesplw = CheckBoxWidget.Cast( layoutRoot.FindAnyWidget("ToolsEspLootCt" + toolsEspLootCatId) );
			if (tesplw)
			{
				tesplw.SetText( m_toolsEspLootCategoriesNames.Get(toolsEspLootCatId) );
				m_toolsEspLootCategories.Insert( tesplw );
			}
		}
		
		m_toolsEspPlayers.SetChecked( m_toolsEspPlayersChecked );
		m_toolsEspDeadBodies.SetChecked( m_toolsEspDeadBodiesChecked );
		m_toolsEspVehicles.SetChecked( m_toolsEspVehiclesChecked );
		m_toolsEspLoot.SetChecked( m_toolsEspLootChecked );
		m_toolsEspSliderDist1.SetCurrent( m_toolsEspSliderDist1Value );
		m_toolsEspSliderDist2.SetCurrent( m_toolsEspSliderDist2Value );
		m_toolsEspFilterText.SetText( m_toolsEspFilterValue );
		m_toolsEspFilterBox.SetText( m_toolsEspFilterValue );
		for (int toolsEspLootCatId2 = 0; toolsEspLootCatId2 < m_toolsEspLootCategories.Count(); toolsEspLootCatId2++)
		{
			m_toolsEspLootCategories.Get(toolsEspLootCatId2).SetChecked( m_toolsEspLootCategoriesSelections.Get(toolsEspLootCatId2) );
		}
			
		// Objects
		m_toolsObjectsRefresh = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ToolsObjectsRefresh"));
		m_toolsObjectsDelete = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ToolsObjectsDelete"));
		m_toolsObjectsList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ToolsObjectsList"));
		m_toolsObjectsInfo.Clear();
		m_toolsObjectsCtls.Clear();
		for (int axisId = 1; axisId <= 6; axisId++)
		{
			string axisName = "X";
			if (axisId == 2) axisName = "Y";
			else if (axisId == 3) axisName = "Z";
			else if (axisId == 4) axisName = "Yaw";
			else if (axisId == 5) axisName = "Pitch";
			else if (axisId == 6) axisName = "Roll";
			
			m_toolsObjectsInfo.Insert(TextWidget.Cast(layoutRoot.FindAnyWidget("ToolsCtlText" + axisId)));
			for (int axisMode = 1; axisMode <= 6; axisMode++)
			{
				m_toolsObjectsCtls.Insert(ButtonWidget.Cast(layoutRoot.FindAnyWidget("Button" + axisName + axisMode)));
			}
		}
		
		SelectCurrentObject();
		
		// Common tabs
		m_tabButtons.Clear();
		m_tabButtons.Insert(layoutRoot.FindAnyWidget("PlayersTabBtn"));
		m_tabButtons.Insert(layoutRoot.FindAnyWidget("SpawnerTabBtn"));
		m_tabButtons.Insert(layoutRoot.FindAnyWidget("MapTabBtn"));
		m_tabButtons.Insert(layoutRoot.FindAnyWidget("EspTabBtn"));
		
		m_tabBodies.Clear();
		m_tabBodies.Insert(layoutRoot.FindAnyWidget("PlayersTabBody"));
		m_tabBodies.Insert(layoutRoot.FindAnyWidget("SpawnerTabBody"));
		m_tabBodies.Insert(layoutRoot.FindAnyWidget("MapTabBody"));
		m_tabBodies.Insert(layoutRoot.FindAnyWidget("EspTabBody"));
		
		m_active = true;
        return layoutRoot;
    }
	
	void InitEspLootFilter(string name, typename filter, int color)
	{
		m_toolsEspLootCategoriesSelections.Insert( true );
		m_toolsEspLootCategoriesFilter.Insert( filter );
		m_toolsEspLootCategoriesNames.Insert( name );
		m_toolsEspLootCategoriesColor.Insert( color );
		
	}
	
	void InitItemsConfig(string preffix)
	{
		if (!m_cachedConfigItems.Contains(preffix))
		{
			ref array<string> classes = new array<string>;
			GameHelpers.GetAllClasses(preffix, classes);
			m_cachedConfigItems.Insert(preffix, classes);
			classes.Sort();
		}		
	}
	
	void UpdateSliderValue(SliderWidget w, string text, float max)
	{
		float value = (w.GetCurrent() / w.GetMax()) * max;
		TextWidget tw = TextWidget.Cast(w.GetChildren());
		
		string fullText = text;
		if (fullText != "") fullText = fullText + ": ";
		tw.SetText(fullText + "(" + value + "/" + max + ")");
	}
	
	void UpdateSpawnerItemPreview()
	{
		string classname;
		int row = m_spawnerItemsListBox.GetSelectedRow();
		if (row == -1) return;
		m_spawnerItemsListBox.GetItemText(row, 0, classname);
		if (classname == "") return;
		
		string preffix = GameHelpers.FindItemPreffix(classname);
		string path = preffix + " " + classname;
		UpdateSliderValue(m_spawnerSliderHealth, "Health", 100);
		
		float quantityMax = 0;		
		if (GetGame().IsKindOf(classname, "Inventory_Base"))
		{
			quantityMax = GetGame().ConfigGetFloat(path + " varQuantityMax");
		}
		else if (GetGame().IsKindOf(classname, "Magazine_Base"))
		{
			quantityMax = GetGame().ConfigGetFloat(path + " count");
		}
		
		UpdateSliderValue(m_spawnerSliderQuantity, "Quantity", quantityMax);
				
		m_spawnerProxySlotSelect.ClearItems();
		m_spawnerProxySlotType.ClearItems();		
		
		array<string> attachments = new array<string>;
		GetGame().ConfigGetTextArray(path + " attachments", attachments);
		if (attachments.Count() != m_spawnerProxySlotsSelections.Count())
		{
			m_spawnerProxySlotsSelections.Clear();
			foreach (string attachment : attachments)
			{
				if (m_spawnerFillProxiesChecked) m_spawnerProxySlotsSelections.Insert(1);
				else m_spawnerProxySlotsSelections.Insert(0);
			}
		}
		
		foreach (string attachment2 : attachments)
		{
			m_spawnerProxySlotSelect.AddItem(attachment2, null, 0);
		}
		
		if (m_spawnerProxySlotSelectedAttachment < 0 || m_spawnerProxySlotSelectedAttachment >= attachments.Count())
			m_spawnerProxySlotSelectedAttachment = 0;
		
		if (attachments.Count() > 0)
			m_spawnerProxySlotSelect.SelectRow(m_spawnerProxySlotSelectedAttachment);
		
		UpdateSpawnerSelectedProxy();
	}
	
	void UpdateSpawnerSelectedProxy()
	{
		if (m_spawnerProxySlotSelectedAttachment < 0 || m_spawnerProxySlotSelectedAttachment >= m_spawnerProxySlotSelect.GetNumItems())
			return;
		
		int rowId = 0;
		string selectedAttachment;
		m_spawnerProxySlotSelect.GetItemText(m_spawnerProxySlotSelectedAttachment, 0, selectedAttachment);
		
		m_spawnerProxySlotType.AddItem("<EMPTY>", null, 0);
		
		ref array<string> attachmentsList = GetAllAttachments(selectedAttachment);		
		foreach (string attachmentClassname : attachmentsList)
		{
			rowId = m_spawnerProxySlotType.AddItem(attachmentClassname, null, 0);
			m_spawnerProxySlotType.SetItem(rowId, GameHelpers.GetItemDisplayName(attachmentClassname), null, 1);
			m_spawnerProxySlotType.SetItemColor(rowId, 1, ARGBF(1, 0.5, 1.0, 0.6));
		}
		
		int selectedItemId = m_spawnerProxySlotsSelections.Get(m_spawnerProxySlotSelectedAttachment);
		if (selectedItemId < 0 || selectedItemId > m_spawnerProxySlotType.GetNumItems())
			selectedItemId = 0;
		
		m_spawnerProxySlotsSelections.Set(m_spawnerProxySlotSelectedAttachment, selectedItemId);
		m_spawnerProxySlotType.SelectRow(selectedItemId);
	}
	
	private ref array<string> GetAllAttachments(string selectedAttachment)
	{
		ref array<string> attachmentsList = null;
		if (m_cachedAttachments.Contains(selectedAttachment))
		{
			attachmentsList = m_cachedAttachments.Get(selectedAttachment);
		}
		else
		{
			attachmentsList = new array<string>;
			GameHelpers.GetAllAttachments(selectedAttachment, attachmentsList);
			m_cachedAttachments.Insert(selectedAttachment, attachmentsList);
		}
		return attachmentsList;
	}
	
	void UpdateCurrentTab()
	{
		for (int i = 0; i < m_tabBodies.Count(); i++)
		{
			m_tabBodies.Get(i).Show(i == m_selectedTabId);
		}
		
		if (m_selectedTabId == 0)
		{
			RefreshPlayersTab();
		}
		else if (m_selectedTabId == 1)
		{
			RefreshSpawnerTab();
		}
		else if (m_selectedTabId == 2)
		{
			RequestMapTab();
		}
	}
	
	void RequestMapTab()
	{
		GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_UPDATEMAP, new Param1< int >( 0 ) );	
	}
	
	void UpdateMapTab(ref PluginAdminTool_MapContext context)
	{
		m_mapWidget.ClearUserMarks();		
		
		int corpseCount = context.m_bodiesPositions.Count();	
		for (int cid = 0; cid < corpseCount; cid++)
		{
			string corpseName = context.m_bodiesNames.Get(cid);
			m_mapWidget.AddUserMark(context.m_bodiesPositions.Get(cid), corpseName, ARGB(255, 128, 93, 128), "SyberiaScripts\\data\\gui\\Markers\\corpse.paa");
		}
		
		int vehiclesCount = context.m_vehiclePositions.Count();	
		for (int vid = 0; vid < vehiclesCount; vid++)
		{
			string carName = context.m_vehicleNames.Get(vid);
			carName = GameHelpers.GetItemDisplayName(carName) + " (" + carName + ")";
			m_mapWidget.AddUserMark(context.m_vehiclePositions.Get(vid), carName, ARGB(255, 255, 216, 0), "SyberiaScripts\\data\\gui\\Markers\\car.paa");
		}
		
		int playersCount = context.m_playerPositions.Count();
		for (int pid = 0; pid < playersCount; pid++)
		{
			m_mapWidget.AddUserMark(context.m_playerPositions.Get(pid), context.m_playerNames.Get(pid), ARGB(255, 255, 0, 0), "SyberiaScripts\\data\\gui\\Markers\\player.paa");
		}
	}
	
	void RefreshSpawnerTab()
	{
		int rowId;
		m_spawnerCategoryListBox.ClearItems();
		foreach (ref PluginAdminTool_SpawnerCategories category : m_context.m_spawnerCategories)
		{
			m_spawnerCategoryListBox.AddItem(category.m_name, category, 0);
		}
		
		if (m_spawnerSelectedCategory < 0) m_spawnerSelectedCategory = 0;		
		m_spawnerCategoryListBox.SelectRow(m_spawnerSelectedCategory);

		ref PluginAdminTool_SpawnerCategories filter;
		m_spawnerCategoryListBox.GetItemData(m_spawnerSelectedCategory, 0, filter);
		m_spawnerItemsListBox.ClearItems();
			
		if (!filter || !m_cachedConfigItems.Contains(filter.m_preffix))
			return;

		string displayName;
		bool anyBaseClass = (filter.m_class == "*");
		bool emptyTextFilter = (m_spawnerFilterCache.LengthUtf8() == 0);
		foreach (string classname : m_cachedConfigItems.Get(filter.m_preffix))
		{
			if (anyBaseClass || GetGame().IsKindOf(classname, filter.m_class))
			{
				displayName = GetGame().ConfigGetTextOut(filter.m_preffix + " " + classname + " displayName");
				if (emptyTextFilter || GameHelpers.StringContainsCaseInsensetive(classname, m_spawnerFilterCache) || GameHelpers.StringContainsCaseInsensetive(displayName, m_spawnerFilterCache))
				{
					rowId = m_spawnerItemsListBox.AddItem(classname, null, 0);
					m_spawnerItemsListBox.SetItem(rowId, displayName, null, 1);
					m_spawnerItemsListBox.SetItemColor(rowId, 1, ARGBF(1, 0.5, 1.0, 0.6));
				}
			}
		}
		
		if (m_spawnerSelectedItem < 0) m_spawnerSelectedItem = 0;
		if (m_spawnerSelectedItem >= m_spawnerItemsListBox.GetNumItems()) m_spawnerSelectedItem = 0;		
		if (m_spawnerItemsListBox.GetNumItems() > 0) m_spawnerItemsListBox.SelectRow(m_spawnerSelectedItem);
	}
	
	void RefreshPlayersTab()
	{		
		m_playersListBox.ClearItems();
		int curPlayerRowId = -1;
		int rowId;
		foreach (ref PluginAdminTool_PlayerContextBase playerContext : m_context.m_players)
		{
			rowId = m_playersListBox.AddItem(playerContext.m_name, NULL, 0);
			m_playersListBox.SetItem(rowId, playerContext.m_nickname, NULL, 1);
			m_playersListBox.SetItem(rowId, playerContext.m_group, NULL, 2);
			if (playerContext.m_isGhost) 
			{
				m_playersListBox.SetItemColor(rowId, 0, ARGBF(1, 0.8, 0.8, 0.8));
				m_playersListBox.SetItemColor(rowId, 1, ARGBF(1, 0.8, 0.8, 0.8));
			}
			else if (playerContext.m_isAdmin) 
			{
				m_playersListBox.SetItemColor(rowId, 0, ARGBF(1, 1, 0.741, 0.101));
				m_playersListBox.SetItemColor(rowId, 1, ARGBF(1, 1, 0.741, 0.101));
			}
			else
			{
				m_playersListBox.SetItemColor(rowId, 0, ARGBF(1, 0.039, 0.760, 0.207));
				m_playersListBox.SetItemColor(rowId, 1, ARGBF(1, 0.039, 0.760, 0.207));
			}			
			
			if (m_selectedPlayerUID == playerContext.m_uid)
			{
				curPlayerRowId = rowId;				
			}
		}	
		
		int selectedRowPlayerStats = m_playersDataStats.GetSelectedRow();
		
		m_playersDataInfo.ClearItems();
		m_playersDataStats.ClearItems();
		m_playersDataInv.ClearItems();
		if (m_playerContext && curPlayerRowId >= 0)
		{
			m_playersListBox.SelectRow(curPlayerRowId);			
			m_playersDataInfo.SetItem(m_playersDataInfo.AddItem("UID:", null, 0), m_playerContext.m_uid, null, 1);
			m_playersDataInfo.SetItem(m_playersDataInfo.AddItem("Name:", null, 0), m_playerContext.m_name, null, 1);
			m_playersDataInfo.SetItem(m_playersDataInfo.AddItem("Nickname:", null, 0), m_playerContext.m_nickname, null, 1);
			m_playersDataInfo.SetItem(m_playersDataInfo.AddItem("Souls:", null, 0), m_playerContext.m_souls.ToString(), null, 1);
			m_playersDataInfo.SetItem(m_playersDataInfo.AddItem("Respawns:", null, 0), m_playerContext.m_respawnCounter.ToString(), null, 1);
			m_playersDataInfo.SetItem(m_playersDataInfo.AddItem("Position:", null, 0), m_playerContext.m_position.ToString(), null, 1);
			
			if (m_playerContext.m_stats)
			{
				foreach (ref PluginAdminTool_PlayerStatContext curStat : m_playerContext.m_stats)
				{
					rowId = m_playersDataStats.AddItem(curStat.m_statName, null, 0);
					m_playersDataStats.SetItem(rowId, curStat.m_curValue.ToString(), null, 1);
					m_playersDataStats.SetItem(rowId, curStat.m_minValue.ToString(), null, 2);
					m_playersDataStats.SetItem(rowId, curStat.m_maxValue.ToString(), null, 3);
				}
				
				if (selectedRowPlayerStats >= 0)
				{
					m_playersDataStats.SelectRow(selectedRowPlayerStats);
				}
			}
			
			if (m_playerContext.m_inv)
			{
				foreach (ref PluginAdminTool_PlayerInvContext item : m_playerContext.m_inv)
				{
					AddPlayersInvItem(item, 0, 0);
				}
			}
		}
		else if (m_selectedPlayerUID.Length() > 0)
		{
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_PLAYERINFO, new Param1< string >( m_selectedPlayerUID ) );	
		}
	}
	
	void AddPlayersInvItem(ref PluginAdminTool_PlayerInvContext item, int tabSpace, int type)
	{
		string displayName = GameHelpers.GetItemDisplayName(item.m_classname) + " (" + item.m_classname + ")";
		int lineColor = ARGBF(1, 1, 1, 1);
		if (type == 0)
		{
			displayName = "===== " + displayName + " =====";
		}
		else if (type == 1)
		{
			lineColor = ARGBF(1, 0.937, 0.768, 0.321);
		}
		else if (type == 2)
		{
			lineColor = ARGBF(1, 0.321, 0.937, 0.439);
		}
		
		for (int i = 0; i < tabSpace; i++)
		{
			displayName = "    " + displayName;
		}
		
		int rowId = m_playersDataInv.AddItem(displayName, null, 0);
		
		string quantity = item.m_curQuantity.ToString() + "/" + item.m_maxQuantity.ToString();	
		m_playersDataInv.SetItem(rowId, quantity, null, 1);
		m_playersDataInv.SetItemColor(rowId, 0, lineColor);
		
		int dmgColor = ARGBF(1, 1 - Math.Clamp(item.m_damage, 0, 1), Math.Clamp(item.m_damage, 0, 1), 0 );
		m_playersDataInv.SetItemColor(rowId, 1, dmgColor);
		
		foreach (ref PluginAdminTool_PlayerInvContext itemAttachment : item.m_attachments)
		{
			AddPlayersInvItem(itemAttachment, tabSpace + 1, 1);
		}
		
		foreach (ref PluginAdminTool_PlayerInvContext itemCargo : item.m_cargo)
		{
			AddPlayersInvItem(itemCargo, tabSpace + 1, 2);
		}
	}
	
	private void RefreshObjectsList()
	{
		int lastSelected = m_toolsObjectsList.GetSelectedRow();
		
		m_toolsObjectsList.ClearItems();
		
		DayZPlayer player = GetGame().GetPlayer();
		vector pos = GetGame().GetCurrentCameraPosition();
		array<Object> objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(pos, 15, objects, null);
		foreach (Object obj : objects)
		{
			if (!obj.HasNetworkID())
				continue;
			
			if (obj.IsBush() || obj.IsTree() || obj.IsRock())
				continue;
			
			if (obj == player)
				continue;
			
			if (obj.GetType() == "")
				continue;
			
			int dist = (int)vector.Distance(pos, obj.GetPosition());
			m_toolsObjectsList.AddItem(obj.GetType() + " (" + dist + "m)", obj, 0);
		}
		
		if (lastSelected >= 0 && lastSelected < m_toolsObjectsList.GetNumItems())
		{
			m_toolsObjectsList.SelectRow(lastSelected);
		}
		else if (m_toolsObjectsList.GetNumItems() > 0)
		{
			m_toolsObjectsList.SelectRow(0);
		}
	}
	
	private void SelectCurrentObject()
	{
		int row = m_toolsObjectsList.GetSelectedRow();
		vector pos = "0 0 0";
		vector rot = "0 0 0";
		
		if (row != -1)
		{
			Object obj;
			m_toolsObjectsList.GetItemData(row, 0, obj);
			
			if (obj)
			{
				pos = obj.GetPosition();
				rot = obj.GetOrientation();
			}
		}
		
		m_toolsObjectsInfo.Get(0).SetText( pos[0].ToString() );
		m_toolsObjectsInfo.Get(1).SetText( pos[1].ToString() );
		m_toolsObjectsInfo.Get(2).SetText( pos[2].ToString() );
		m_toolsObjectsInfo.Get(3).SetText( rot[0].ToString() );
		m_toolsObjectsInfo.Get(4).SetText( rot[1].ToString() );
		m_toolsObjectsInfo.Get(5).SetText( rot[2].ToString() );
	}
	
	private void MoveCurrentObject(int axis, int value)
	{
		int row = m_toolsObjectsList.GetSelectedRow();
		if (row == -1) return;
		
		Object obj;
		m_toolsObjectsList.GetItemData(row, 0, obj);		
		if (!obj) return;
		
		float fval = 0;
		if (value == 0) fval = -0.001;
		if (value == 1) fval = -0.1;
		if (value == 2) fval = -1;
		if (value == 3) fval = 1;
		if (value == 4) fval = 0.1;
		if (value == 5) fval = 0.001;		
		GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_OBJMOVE, new Param3<Object, int, float>( obj, axis, fval ) );
	}
	
	private void DeleteCurrentObject()
	{
		int row = m_toolsObjectsList.GetSelectedRow();
		if (row == -1) return;
		
		Object obj;
		m_toolsObjectsList.GetItemData(row, 0, obj);		
		if (!obj) return;
		GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_OBJDEL, new Param1<Object>( obj ) );		
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(RefreshObjectsList, 250, false);
	}
	
	private void SpawnCurrentItemRequest()
	{
		string classname;
		int row = m_spawnerItemsListBox.GetSelectedRow();

		if (row == -1) return;
		m_spawnerItemsListBox.GetItemText(row, 0, classname);
		
		if (classname == "") return;
		
		int spawnType = m_spawnerTypeSelect.GetCurrentItem();
		vector cursorPos = "0 0 0";
		if (spawnType == 2 && !GameHelpers.GetCursorPos(cursorPos)) return;
		
		PluginAdminTool_SpawnItemContext m_context = new PluginAdminTool_SpawnItemContext;
		m_context.m_classname = classname;
		m_context.m_health = m_spawnerSliderHealth.GetCurrent();
		m_context.m_quantity = m_spawnerSliderQuantity.GetCurrent();
		m_context.m_spawnType = spawnType;
		m_context.m_cursorPos = cursorPos;
		m_context.m_attachments = new array<string>;
		
		string proxySlotName;
		for (int sid = 0; sid < m_spawnerProxySlotSelect.GetNumItems(); sid++)
		{
			m_spawnerProxySlotSelect.GetItemText(sid, 0, proxySlotName);
			ref array<string> allAttachments = GetAllAttachments(proxySlotName);				
			int attachmentId = m_spawnerProxySlotsSelections.Get(sid) - 1;
			if (attachmentId >= 0 && attachmentId < allAttachments.Count())
			{
				string attachmentName = allAttachments.Get(attachmentId);
				m_context.m_attachments.Insert(attachmentName);
			}
		}
		
		GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_SPAWNITEM, new Param1< ref PluginAdminTool_SpawnItemContext >( m_context ));
	}

	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_dirty)
		{
			UpdateCurrentTab();
			m_dirty = false;
		}
		
		if (m_selectedTabId == 3)
		{
			SelectCurrentObject();
		}
		
		if (!m_active)
		{
			m_mapPos = m_mapWidget.GetMapPos();
			m_mapScale = m_mapWidget.GetScale();			
			GetGame().GetUIManager().Back();
		}
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{
			foreach (ref Widget pageBtn : m_tabButtons)
			{
				if (w == pageBtn)
				{
					m_selectedTabId = m_tabButtons.Find(pageBtn);
					m_dirty = true;
					return true;
				}
			}
			
			if (w == m_playersDataRefresh)
			{
				if (m_selectedPlayerUID.Length() > 0)
				{
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_PLAYERINFO, new Param1< string >( m_selectedPlayerUID ) );	
				}
			}
			
			if (w == m_playersDataDelete)
			{
				if (m_selectedPlayerUID.Length() > 0)
				{
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_DELETE_CHARACTER, new Param1< string >( m_selectedPlayerUID ) );	
				}
			}
			
			if (w == m_playersDataKick)
			{
				if (m_selectedPlayerUID.Length() > 0)
				{
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_KICK, new Param1< string >( m_selectedPlayerUID ) );	
				}
			}
			
			if (w == m_playersDataTeleportToPlayer)
			{
				if (m_selectedPlayerUID.Length() > 0)
				{
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT_TO_PLAYER, new Param1< string >( m_selectedPlayerUID ) );	
				}
			}
			
			if (w == m_playersDataTeleportPlayerToMe)
			{
				if (m_selectedPlayerUID.Length() > 0)
				{
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT_PLAYER_TO_ME, new Param1< string >( m_selectedPlayerUID ) );	
				}
			}
			
			if (w == m_playersStatApply)
			{
				int selectedRow = m_playersDataStats.GetSelectedRow();
				if (m_selectedPlayerUID.Length() > 0 && selectedRow >= 0)
				{
					string statName, statMinStr, statMaxStr, statNewValStr;
					m_playersDataStats.GetItemText(selectedRow, 0, statName);
					m_playersDataStats.GetItemText(selectedRow, 2, statMinStr);
					m_playersDataStats.GetItemText(selectedRow, 3, statMaxStr);
					statNewValStr = m_playersStatEditBox.GetText();
					
					float statMin = statMinStr.ToFloat();
					float statMax = statMaxStr.ToFloat();
					float statVal = statNewValStr.ToFloat();
					
					statVal = Math.Clamp(statVal, statMin, statMax);					
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_PLAYERUPDATE, new Param3< string, string, float >( m_selectedPlayerUID, statName, statVal ) );
				}
			}
			
			if (w == m_playersMsgApply)
			{
				if (m_selectedPlayerUID.Length() > 0)
				{
					string msgStr = m_playersMsgEditBox.GetText();				
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_MESSAGE, new Param2< string, string >( m_selectedPlayerUID, msgStr ) );
				}
			}
			
			if (w == m_spawnButton)
			{
				SpawnCurrentItemRequest();
			}
			
			if (w == m_spawnerClear)
			{
				GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_CLEARITEMS, new Param1< int >( 0 ) );
			}
			
			if (w == m_toolsObjectsRefresh)
			{
				RefreshObjectsList();
			}
			
			if (w == m_toolsObjectsDelete)
			{
				DeleteCurrentObject();
			}
			
			ButtonWidget wb = ButtonWidget.Cast(w);
			if (wb)
			{
				int toolsObjectsCtlsIndex = m_toolsObjectsCtls.Find(wb);
				if (toolsObjectsCtlsIndex != -1)
				{
					int axis = (int)(toolsObjectsCtlsIndex / 6);
					int btnid = (int)(toolsObjectsCtlsIndex % 6);
					MoveCurrentObject(axis, btnid);
				}
			}
		}
		
		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int  column,	int  oldRow, int  oldColumn)
	{
		if (w == m_playersListBox)
		{
			if (row >= 0 && row < m_context.m_players.Count())
			{
				string uid = m_context.m_players.Get(row).m_uid;
				if (uid != m_selectedPlayerUID)
				{
					m_selectedPlayerUID = uid;
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_PLAYERINFO, new Param1< string >( uid ) );
				}			
			}
		}
		
		if (w == m_playersDataStats)
		{
			string valueText;
			if (row >= 0)
			{
				m_playersDataStats.GetItemText(row, 1, valueText);
				m_playersStatEditText.SetText(valueText);
				m_playersStatEditBox.SetText(valueText);
			}
		}
		
		if (w == m_spawnerCategoryListBox && oldRow != row)
		{
			m_dirty = true;
			if (m_spawnerSelectedCategory != row)
			{
				m_spawnerSelectedCategory = row;
				m_spawnerSelectedItem = 0;
				m_spawnerProxySlotsSelections.Clear();
				m_spawnerProxySlotSelectedAttachment = -1;
			}
		}
		
		if (w == m_spawnerItemsListBox && oldRow != row)
		{
			if (m_spawnerSelectedItem != row)
			{
				m_spawnerSelectedItem = row;
				m_spawnerProxySlotsSelections.Clear();
				m_spawnerProxySlotSelectedAttachment = -1;
			}
			UpdateSpawnerItemPreview( );
		}
		
		if (w == m_spawnerProxySlotSelect && row != m_spawnerProxySlotSelectedAttachment)
		{
			m_spawnerProxySlotSelectedAttachment = row;
			UpdateSpawnerItemPreview( );
		}
		
		if (w == m_spawnerProxySlotType && m_spawnerProxySlotSelectedAttachment >= 0 && m_spawnerProxySlotSelectedAttachment < m_spawnerProxySlotsSelections.Count())
		{
			m_spawnerProxySlotsSelections.Set(m_spawnerProxySlotSelectedAttachment, row);
		}
		
		return super.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		if (button == MouseState.LEFT)
		{
			if (w == m_spawnerItemsListBox)
			{
				SpawnCurrentItemRequest( );
			}
			
			if (w == m_mapWidget)
			{
				PluginAdminTool adminTool = PluginAdminTool.Cast(GetPlugin(PluginAdminTool));
				vector worldPos = MapPositionToWorldPosition();
				if (m_toolsFreeCamToggleChecked && adminTool.m_freeCam)
				{					
					adminTool.m_freeCam.SetPosition(worldPos);
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT, new Param2< vector, int >( worldPos, 1 ) );
				}
				else
				{
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT, new Param2< vector, int >( worldPos, 3 ) );
				}
			}
		}
		
		return super.OnDoubleClick(w, x, y, button);
	}
	
	private vector MapPositionToWorldPosition()
	{
		vector screenPos;
		vector result;
		vector dir;
		vector from;
		vector to;
		dir = GetGame().GetPointerDirection();
	    from = GetGame().GetCurrentCameraPosition();
	    to = from + ( dir * 1000 );
		screenPos = GetGame().GetScreenPos( to );
	    result = m_mapWidget.ScreenToMap( screenPos );
	    return result;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		string text;
		if (w == m_playersStatEditBox) {			
			text = m_playersStatEditBox.GetText();
			m_playersStatEditText.SetText(text);			
		}
		else if (w == m_playersMsgEditBox) {			
			text = m_playersMsgEditBox.GetText();
			m_playersMsgEditText.SetText(text);			
		}
		else if (w == m_spawnerFilterEditBox) {
			text = m_spawnerFilterEditBox.GetText();
			m_spawnerFilterEditText.SetText(text);	
			m_spawnerFilterCache = text;
			m_dirty = true;
		}
		else if (w == m_spawnerSliderHealth || w == m_spawnerSliderQuantity) {
			m_spawnerSelectedHealth = m_spawnerSliderHealth.GetCurrent();
			m_spawnerSelectedQuantity = m_spawnerSliderQuantity.GetCurrent();
			UpdateSpawnerItemPreview( );
		}
		else if (w == m_spawnerTypeSelect) {
			m_spawnerSelectedSpawnType = m_spawnerTypeSelect.GetCurrentItem();
			UpdateSpawnerItemPreview( );
		}
		else if (w == m_spawnerFillProxies) {
			m_spawnerFillProxiesChecked = m_spawnerFillProxies.IsChecked();
			m_spawnerProxySlotsSelections.Clear();
			UpdateSpawnerItemPreview( );
		}
		else if (w == m_toolsFreeCamToggle && m_toolsFreeCamToggle.IsChecked() != m_toolsFreeCamToggleChecked)
		{
			PluginAdminTool pluginAdminTool = PluginAdminTool.Cast( GetPlugin(PluginAdminTool) );
			if (pluginAdminTool)
			{
				vector camPos = "0 0 0";
				m_toolsFreeCamToggleChecked = m_toolsFreeCamToggle.IsChecked();
				if (!m_toolsFreeCamToggleChecked)
				{
					if (pluginAdminTool.m_freeCam)
					{
						SybLog("!!!!!!!!!! DBG1");
						camPos = pluginAdminTool.m_freeCam.GetPosition();
					}
					else if (GetGame().GetPlayer())
					{
						SybLog("!!!!!!!!!! DBG2");
						camPos = GetGame().GetPlayer().GetPosition();
					}
				}
				
				GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_FREECAM, new Param2< bool, vector >( m_toolsFreeCamToggleChecked, camPos ) );
			}
		}
		else if (w == m_toolsEspSliderDist1)
		{
			UpdateSliderValue(m_toolsEspSliderDist1, "", m_toolsEspSliderDist1.GetMax());
			m_toolsEspSliderDist1Value = m_toolsEspSliderDist1.GetCurrent();
		}
		else if (w == m_toolsEspSliderDist2)
		{
			UpdateSliderValue(m_toolsEspSliderDist2, "", m_toolsEspSliderDist2.GetMax());
			m_toolsEspSliderDist2Value = m_toolsEspSliderDist2.GetCurrent();
		}
		else if (w == m_toolsEspPlayers || w == m_toolsEspVehicles || w == m_toolsEspDeadBodies || w == m_toolsEspLoot)
		{
			m_toolsEspPlayersChecked = m_toolsEspPlayers.IsChecked();
			m_toolsEspVehiclesChecked = m_toolsEspVehicles.IsChecked();
			m_toolsEspDeadBodiesChecked = m_toolsEspDeadBodies.IsChecked();
			m_toolsEspLootChecked = m_toolsEspLoot.IsChecked();
		}
		else if (w == m_toolsEspFilterBox) 
		{			
			text = m_toolsEspFilterBox.GetText();
			m_toolsEspFilterText.SetText(text);	
			m_toolsEspFilterValue = text;		
		}
		
		for (int toolsEspLootCatId = 0; toolsEspLootCatId < 12; toolsEspLootCatId++)
		{
			if (w == m_toolsEspLootCategories.Get(toolsEspLootCatId))
			{
				m_toolsEspLootCategoriesSelections.Set(toolsEspLootCatId, m_toolsEspLootCategories.Get(toolsEspLootCatId).IsChecked());
			}
		}
		
		return super.OnChange(w, x, y, finished);
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
}