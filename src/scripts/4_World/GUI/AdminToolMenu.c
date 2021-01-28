class AdminToolMenu extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
	
	int m_selectedTabId = 0;
	string m_selectedPlayerUID;
	
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
		
		// Common tabs
		m_tabButtons.Clear();
		m_tabButtons.Insert(layoutRoot.FindAnyWidget("PlayersTabBtn"));
		m_tabButtons.Insert(layoutRoot.FindAnyWidget("SpawnerTabBtn"));
		m_tabButtons.Insert(layoutRoot.FindAnyWidget("EspTabBtn"));
		
		m_tabBodies.Clear();
		m_tabBodies.Insert(layoutRoot.FindAnyWidget("PlayersTabBody"));
		m_tabBodies.Insert(layoutRoot.FindAnyWidget("SpawnerTabBody"));
		m_tabBodies.Insert(layoutRoot.FindAnyWidget("EspTabBody"));
		
		m_active = true;
        return layoutRoot;
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
		
		return super.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key) {
		return false;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		bool result = super.OnChange(w, x, y, finished);
	
		string text;
		if (w.GetName() == m_playersStatEditBox.GetName()) {			
			text = m_playersStatEditBox.GetText();
			m_playersStatEditText.SetText(text);			
			return true;
		}
		
		return result;
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