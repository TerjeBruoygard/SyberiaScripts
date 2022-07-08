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
	ref TextListboxWidget m_playersListBox;
	ref TextListboxWidget m_playersDataInfo;
	ref TextListboxWidget m_playersDataStats;
	ref TextListboxWidget m_playersDataInv;
	ref TextWidget m_playersStatEditText;
	ref EditBoxWidget m_playersStatEditBox;
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
	static bool m_spawnerFillProxiesChecked = true;
	static int m_spawnerProxySlotSelectedAttachment = -1;
	static ref array<int> m_spawnerProxySlotsSelections = new array<int>;
	
	// Map
	ref MapWidget m_mapWidget;
	static vector m_mapPos = "0 0 0";
	static float m_mapScale = 0.1;
	
	void AdminToolMenu()
	{
		m_tabButtons = new array<ref Widget>;
		m_tabBodies = new array<ref Widget>;
	}
	
	void ~AdminToolMenu()
	{
		delete m_tabButtons;
		delete m_tabBodies;
		
		if (m_context) delete m_context;
		if (m_playerContext) delete m_playerContext;

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
		m_playersStatEditText = TextWidget.Cast(layoutRoot.FindAnyWidget("PlayersStatEditText"));
		m_playersStatEditBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlayersStatEditBox"));
		m_playersStatApply = layoutRoot.FindAnyWidget("PlayersDataStatsApply");
		
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
		m_spawnerProxySlotSelect.Show(m_spawnerFillProxiesChecked);
		m_spawnerProxySlotType.Show(m_spawnerFillProxiesChecked);
		
		InitItemsConfig("CfgVehicles");
		InitItemsConfig("CfgWeapons");
		InitItemsConfig("CfgMagazines");
		
		// Map
		m_mapWidget = MapWidget.Cast(layoutRoot.FindAnyWidget("MapPreview"));
		m_mapWidget.SetMapPos(m_mapPos);	
		m_mapWidget.SetScale(m_mapScale);
		
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
		tw.SetText(text + ": (" + value + "/" + max + ")");
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
		if (!m_spawnerFillProxiesChecked)
			return;
		
		array<string> attachments = new array<string>;
		GetGame().ConfigGetTextArray(path + " attachments", attachments);
		if (attachments.Count() != m_spawnerProxySlotsSelections.Count())
		{
			m_spawnerProxySlotsSelections.Clear();
			foreach (string attachment : attachments)
			{
				m_spawnerProxySlotsSelections.Insert(0);
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
		
		string selectedAttachment;
		m_spawnerProxySlotSelect.GetItemText(m_spawnerProxySlotSelectedAttachment, 0, selectedAttachment);
		
		int rowId = 0;
		ref array<string> attachmentsList = GetAllAttachments(selectedAttachment);		
		foreach (string attachmentClassname : attachmentsList)
		{
			rowId = m_spawnerProxySlotType.AddItem(attachmentClassname, null, 0);
			m_spawnerProxySlotType.SetItem(rowId, GameHelpers.GetItemDisplayName(attachmentClassname), null, 1);
			m_spawnerProxySlotType.SetItemColor(rowId, 1, ARGBF(1, 0.5, 1.0, 0.6));
		}
		
		int selectedItemId = m_spawnerProxySlotsSelections.Get(m_spawnerProxySlotSelectedAttachment);
		if (selectedItemId < 0 || selectedItemId > attachmentsList.Count())
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
		int playersCount = context.m_playerPositions.Count();
		for (int pid = 0; pid < playersCount; pid++)
		{
			m_mapWidget.AddUserMark(context.m_playerPositions.Get(pid), context.m_playerNames.Get(pid), ARGB(255, 255, 0, 0), "SyberiaScripts\\data\\gui\\Markers\\player.paa");
		}
		
		int vehiclesCount = context.m_vehiclePositions.Count();	
		for (int vid = 0; vid < vehiclesCount; vid++)
		{
			string carName = context.m_vehicleNames.Get(vid);
			carName = GameHelpers.GetItemDisplayName(carName) + " (" + carName + ")";
			m_mapWidget.AddUserMark(context.m_vehiclePositions.Get(vid), carName, ARGB(255, 255, 216, 0), "SyberiaScripts\\data\\gui\\Markers\\car.paa");
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
		string textFilter = m_spawnerFilterEditBox.GetText();
		bool anyBaseClass = (filter.m_class == "*");
		bool emptyTextFilter = (textFilter == "");
		foreach (string classname : m_cachedConfigItems.Get(filter.m_preffix))
		{
			if (anyBaseClass || GetGame().IsKindOf(classname, filter.m_class))
			{
				displayName = GetGame().ConfigGetTextOut(filter.m_preffix + " " + classname + " displayName");
				if (emptyTextFilter || GameHelpers.StringContainsCaseInsensetive(classname, textFilter) || GameHelpers.StringContainsCaseInsensetive(displayName, textFilter))
				{
					rowId = m_spawnerItemsListBox.AddItem(classname, null, 0);
					m_spawnerItemsListBox.SetItem(rowId, displayName, null, 1);
					m_spawnerItemsListBox.SetItemColor(rowId, 1, ARGBF(1, 0.5, 1.0, 0.6));
				}
			}
		}
		
		if (m_spawnerSelectedItem < 0) m_spawnerSelectedItem = 0;
		if (m_spawnerSelectedItem >= m_spawnerItemsListBox.GetNumItems()) m_spawnerSelectedItem = 0;		
		m_spawnerItemsListBox.SelectRow(m_spawnerSelectedItem);
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
	
	private void SpawnCurrentItemRequest()
	{
		string classname;
		int row = m_spawnerItemsListBox.GetSelectedRow();

		if (row == -1) return;
		m_spawnerItemsListBox.GetItemText(row, 0, classname);
		
		if (classname == "") return;
		
		PluginAdminTool_SpawnItemContext m_context = new PluginAdminTool_SpawnItemContext;
		m_context.m_classname = classname;
		m_context.m_health = m_spawnerSliderHealth.GetCurrent();
		m_context.m_quantity = m_spawnerSliderQuantity.GetCurrent();
		m_context.m_spawnType = m_spawnerTypeSelect.GetCurrentItem();
		m_context.m_cursorPos = GameHelpers.GetCursorPos();
		m_context.m_attachments = new array<string>;
		
		if (m_spawnerFillProxies.IsChecked())
		{
			string proxySlotName;
			for (int sid = 0; sid < m_spawnerProxySlotSelect.GetNumItems(); sid++)
			{
				m_spawnerProxySlotSelect.GetItemText(sid, 0, proxySlotName);
				ref array<string> allAttachments = GetAllAttachments(proxySlotName);				
				int attachmentId = m_spawnerProxySlotsSelections.Get(sid);
				if (attachmentId >= 0 && attachmentId < allAttachments.Count())
				{
					string attachmentName = allAttachments.Get(attachmentId);
					m_context.m_attachments.Insert(attachmentName);
				}
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
			
			if (w == m_spawnButton)
			{
				SpawnCurrentItemRequest();
			}
			
			if (w == m_spawnerClear)
			{
				GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_CLEARITEMS, new Param1< int >( 0 ) );
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
				vector worldPos = MapPositionToWorldPosition();
				GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT, new Param1< vector >( worldPos ) );
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
		else if (w == m_spawnerFilterEditBox) {
			text = m_spawnerFilterEditBox.GetText();
			m_spawnerFilterEditText.SetText(text);	
			m_dirty = true;
		}
		else if (w == m_spawnerSliderHealth || w == m_spawnerSliderQuantity) {
			m_spawnerSelectedHealth = m_spawnerSliderHealth.GetCurrent();
			m_spawnerSelectedQuantity = m_spawnerSliderQuantity.GetCurrent();
			UpdateSpawnerItemPreview( );
		}
		else if (w == m_spawnerTypeSelect || w == m_spawnerFillProxies) {
			m_spawnerSelectedSpawnType = m_spawnerTypeSelect.GetCurrentItem();
			m_spawnerFillProxiesChecked = m_spawnerFillProxies.IsChecked();
			m_spawnerProxySlotSelect.Show(m_spawnerFillProxiesChecked);
			m_spawnerProxySlotType.Show(m_spawnerFillProxiesChecked);
			UpdateSpawnerItemPreview( );
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