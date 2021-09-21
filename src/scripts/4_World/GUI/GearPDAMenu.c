class GearPDAMenu extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
	bool m_updateBtnsPanel = false;
	bool m_visibleBtnsPanel[3] = { true, false, false };

    ref TextListboxWidget m_contactList;
	ref TextWidget m_yourIdText;
	ref EditBoxWidget m_addContactTxt;
	ref ButtonWidget m_addContactBtn;
	ref ButtonWidget m_deleteContactBtn;
	ref TextListboxWidget m_chat;
	ref EditBoxWidget m_message;
	ref ButtonWidget m_send;
	ref TextWidget m_callibrationText;
	ref ButtonWidget m_mute_btn;
	ref TextWidget m_mute_text;
	ref ButtonWidget m_rename_btn;
	ref ButtonWidget m_ban_btn;
	
	ref TextListboxWidget m_groupMembersList;
	ref ButtonWidget m_group_add_btn;
	ref ButtonWidget m_group_del_btn;
	ref EditBoxWidget m_group_input;
	ref TextWidget m_group_help_text;
	
	ref ImageWidget m_page_msg;
	ref ImageWidget m_page_map;
	ref ImageWidget m_page_grp;
	
	ref Widget m_page_buttons_panel;
	ref ButtonWidget m_page_msg_btn;
	ref Widget m_page_msg_back;
	ref ButtonWidget m_page_map_btn;
	ref Widget m_page_map_back;
	ref ButtonWidget m_page_grp_btn;
	ref Widget m_page_grp_back;
	
	ref MapWidget m_map;

	const int m_contactMaxLength = 32;
	const int m_messageMaxLength = 256;
	
	float m_addContactTimeout = 0;
	bool m_addContactStatus = 0;
	
	float m_sendMessageTimeout = 0;
	bool m_sendMessageStatus = 0;
	int m_lastSelectedContact = -1;
	
	bool m_externalSendEvent = false;
	bool m_sendFuncEnabled = true;
	
	bool m_updateGroupManagement = false;
	ref array<ref SyberiaPdaGroupMember> m_group_members = null;
	string m_group_info = "";
	
	void GearPDAMenu()
	{
	}	
	
	void ~GearPDAMenu()
	{
		if (m_group_members) delete m_group_members;
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
	}

    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/GearPDAMenu.layout" );

        m_contactList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "contact_list" ) );
		m_yourIdText = TextWidget.Cast( layoutRoot.FindAnyWidget( "your_id_text" ) );
		m_addContactTxt = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "add_contact_txt" ) );
		m_addContactBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "add_contact_btn" ) );
		m_deleteContactBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "delete_contact_btn" ) );
		m_chat = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "messages_txt" ) );
		m_message = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "send_msg_txt" ) );
		m_send = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "semd_msg_btn" ) );
		m_callibrationText = TextWidget.Cast( layoutRoot.FindAnyWidget( "callibration_txt" ) );
		m_mute_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "mute_btn" ) );
		m_mute_text = TextWidget.Cast( layoutRoot.FindAnyWidget( "mute_btntext" ) );
		m_rename_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "rename_contact_btn" ) );
		m_ban_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ban_contact_btn" ) );
		m_map = MapWidget.Cast( layoutRoot.FindAnyWidget("map_widget") );
		m_page_buttons_panel = layoutRoot.FindAnyWidget("PagesBtnsPanel");
		m_group_help_text = TextWidget.Cast( layoutRoot.FindAnyWidget("group_info") );
		
		m_groupMembersList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "group_members" ) );
		m_group_add_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "add_member_btn" ) );
		m_group_del_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "del_member_btn" ) );
		m_group_input = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "member_id_txt" ) );
		
		m_page_msg = ImageWidget.Cast( layoutRoot.FindAnyWidget( "PagePDA" ) );
		m_page_map = ImageWidget.Cast( layoutRoot.FindAnyWidget( "PageMap" ) );
		m_page_grp = ImageWidget.Cast( layoutRoot.FindAnyWidget( "PageGroups" ) );
		
		m_page_msg_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "pagemsg_btn" ) );
		m_page_map_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "pagemap_btn" ) );
		m_page_grp_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "pagegrp_btn" ) );
		
		m_page_msg_back = layoutRoot.FindAnyWidget( "pagemsg_back" );
		m_page_map_back = layoutRoot.FindAnyWidget( "pagemap_back" );
		m_page_grp_back = layoutRoot.FindAnyWidget( "pagegrp_back" );
		
		UpdateMutedButton();
		UpdateMap();
				
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		
		m_visibleBtnsPanel[1] = pluginGearPDA.m_enableMapPage;
		m_updateBtnsPanel = true;
		
		SelectPdaPage(pluginGearPDA.m_current_page_id);
				
		ref array<int> request = new array<int>();
		for (int i = 0; i < pluginGearPDA.m_contacts.Count(); i++)
		{
			request.Insert(pluginGearPDA.m_contacts[i].m_id);
		}
		
		if (!m_active) 
		{
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_CHECK_CONTACT, new Param1< ref array<int> >( request ) );
			m_yourIdText.SetText("#pda_loading");
			m_message.Enable(false);
			m_send.Enable(false);
			m_sendFuncEnabled = false;
		}
		
		delete request;
		m_active = true;		
        return layoutRoot;
    }
	
	void EnableGroupManagement(ref array<ref SyberiaPdaGroupMember> members, string infoText)
	{
		m_group_members = members;
		m_group_info = infoText;
		m_updateGroupManagement = true;
		m_visibleBtnsPanel[2] = true;
		m_updateBtnsPanel = true;
	}
	
	void UpdateMap()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player) return;
		
		vector pos = player.GetPosition();
		m_map.ClearUserMarks();
		m_map.AddUserMark(pos, "", ARGBF(1, 0.690, 0.152, 0.188), "SyberiaScripts\\data\\pda\\marker.paa");
		m_map.SetScale(0.05);
		
		pos[0] = pos[0] + 160;
		pos[2] = pos[2] - 140;
		
		m_map.SetMapPos(pos);
	}
	
	void SelectPdaPage(int id)
	{
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));		
		pluginGearPDA.m_current_page_id = id;
		
		m_page_msg.Show(false);
		m_page_map.Show(false);
		m_page_grp.Show(false);
		
		m_page_msg_btn.Enable(true);
		m_page_map_btn.Enable(true);
		m_page_grp_btn.Enable(true);
		
		if (id == 0)
		{
			m_page_msg.Show(true);
			m_page_msg_btn.Enable(false);
		}
		else if (id == 1)
		{
			m_page_map.Show(true);
			m_page_map_btn.Enable(false);
		}
		else if (id == 2)
		{
			m_page_grp.Show(true);
			m_page_grp_btn.Enable(false);
		}
	}
	
	void FillContactsList()
	{
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		
		int itemId;
		int rowShift = 0;
		int selectedRow = m_lastSelectedContact;
		m_contactList.ClearItems();
		
		if (pluginGearPDA.m_enableGlobalChat)
		{
			rowShift = rowShift + 1;
			itemId = m_contactList.AddItem("", NULL, 0);
			m_contactList.SetItem(itemId, "#pda_global_chat", NULL, 1);
			m_contactList.SetItem(itemId, "", NULL, 2);
			m_contactList.SetItemColor(itemId, 1, ARGBF(1, 0.588, 0.662, 0.341));
			m_contactList.SetItemColor(itemId, 2, ARGBF(1, 0.588, 0.662, 0.341));
		}
		
		if (pluginGearPDA.m_group_chatName.Length() > 0)
		{
			rowShift = rowShift + 1;
			itemId = m_contactList.AddItem("", NULL, 0);
			m_contactList.SetItem(itemId, pluginGearPDA.m_group_chatName, NULL, 1);
			m_contactList.SetItem(itemId, "", NULL, 2);
			m_contactList.SetItemColor(itemId, 1, ARGBF(1, 0.588, 0.662, 0.341));
			m_contactList.SetItemColor(itemId, 2, ARGBF(1, 0.588, 0.662, 0.341));
		}
				
		for (int i = 0; i < pluginGearPDA.m_contacts.Count(); i++)
		{
			ref PluginGearPDA_Conversation contact = pluginGearPDA.m_contacts[i];
			itemId = m_contactList.AddItem("", NULL, 0);
			m_contactList.SetItem(itemId, contact.m_Name, NULL, 1);
			m_contactList.SetItem(itemId, "" + contact.m_Unreaded, NULL, 2);
			
			if (contact.m_IsBanned)
			{
				m_contactList.SetItemColor(itemId, 1, ARGBF(1, 0.447, 0.352, 0.294));
			}
			else if (pluginGearPDA.m_onlineContacts.Find(contact.m_id) != -1)
			{
				m_contactList.SetItemColor(itemId, 1, ARGBF(1, 0.588, 0.662, 0.341));
			}
			else
			{
				m_contactList.SetItemColor(itemId, 1, ARGBF(1, 0.411, 0.547, 0.294));
			}		
			
			m_contactList.SetItemColor(itemId, 2, ARGBF(1, 0.588, 0.662, 0.341));	
		}
		
		if (selectedRow >= 0 && selectedRow < pluginGearPDA.m_contacts.Count() + rowShift)
		{
			m_lastSelectedContact = selectedRow;
			m_contactList.SelectRow(selectedRow);
			SelectConversation(selectedRow);
		}
		else if (pluginGearPDA.m_contacts.Count() + rowShift > 0)
		{
			m_lastSelectedContact = 0;
			m_contactList.SelectRow(0);
			SelectConversation(0);
		}
		else
		{
			m_lastSelectedContact = -1;
			m_contactList.SelectRow(-1);
			SelectConversation(-1);
		}
	}
	
	void SelectConversation(int id)
	{
		int rowShift = 0;		
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		ref array<ref Param2<string, string>> confMessages = null;
		
		if (pluginGearPDA.m_enableGlobalChat)
		{
			if (id == rowShift)
			{
				confMessages = pluginGearPDA.m_globalMessages;
			}
			
			rowShift = rowShift + 1;
		}
		
		if (pluginGearPDA.m_group_chatName.Length() > 0)
		{
			if (id == rowShift)
			{
				confMessages = pluginGearPDA.m_groupMessages;
			}
			
			rowShift = rowShift + 1;
		}
		
		if ( (id < 0) || (id >= pluginGearPDA.m_contacts.Count() + rowShift) )
		{
			m_chat.ClearItems();
			m_message.Enable(false);
			m_send.Enable(false);
			m_sendFuncEnabled = false;
			return;
		}
		
		m_chat.ClearItems();
		
		float chatWidth;
		float chatHeight;
		m_chat.GetScreenSize(chatWidth, chatHeight);
		int chatLineMaxSize = (int)(chatWidth * 0.70) - 50;
		int chatLinesCount = -1;
		string autor;	
		int color;	
		int itemId;
		int addedLinesCount = 0;
		string chatMessage;
		bool isLineFinished;
		string chatLine;
		int i = 0;
		int q = 0;
		int textWidthCalibration;
		int textHeightCalibration; 
		
		if (confMessages)
		{
			for (i = 0; i < confMessages.Count(); i++)
			{
				ref Param2<string, string> commentGlob = confMessages[i];
				autor = commentGlob.param1;							
				itemId = m_chat.AddItem(autor, NULL, 1);	
				m_chat.SetItemColor(itemId, 1, ARGBF(1, 0.588, 0.662, 0.341));
										
				addedLinesCount = 0;
				chatMessage = commentGlob.param2;			
				while (chatMessage.LengthUtf8() > 0)
				{		
					isLineFinished = false;
					chatLine = "";		
					for (q = 0; q < chatMessage.LengthUtf8() && !isLineFinished; q++)
					{
						chatLine = chatLine + chatMessage.SubstringUtf8(q, 1);						
						m_callibrationText.SetText(chatLine);
						m_callibrationText.GetTextSize(textWidthCalibration, textHeightCalibration);
						
						if (textWidthCalibration >= chatLineMaxSize)
						{						
							isLineFinished = true;
						}
					}
					
					if (addedLinesCount == 0)
					{
						m_chat.SetItem(itemId, chatLine, NULL, 3);
					} 
					else
					{
						itemId = m_chat.AddItem(chatLine, NULL, 3);
					}
					
					m_chat.SetItemColor(itemId, 3, ARGBF(1, 0.588, 0.662, 0.341));
					
					chatMessage = chatMessage.SubstringUtf8(chatLine.LengthUtf8(), chatMessage.LengthUtf8() - chatLine.LengthUtf8());
					addedLinesCount = addedLinesCount + 1;
					chatLinesCount = chatLinesCount + 1;
				}
			}
			
			m_callibrationText.SetText("");
			m_chat.SelectRow(chatLinesCount);
			m_chat.EnsureVisible(chatLinesCount);
			
			m_message.Enable(true);
			m_send.Enable(true);
			m_sendFuncEnabled = true;
		}
		else
		{
			ref PluginGearPDA_Conversation contact = pluginGearPDA.m_contacts[id - rowShift];		
			ref array<ref PluginGearPDA_Comment> comments = pluginGearPDA.GetComments(contact.m_id);

			for (i = 0; i < comments.Count(); i++)
			{
				ref PluginGearPDA_Comment comment = comments[i];	
				if (comment.m_id == GetSyberiaOptions().m_clientCharacterId)
				{
					autor = "Me";
					color = ARGBF(1, 0.678, 0.792, 0.305);
				}
				else
				{
					autor = contact.m_Name;
					color = ARGBF(1, 0.588, 0.662, 0.341);
				}
							
				itemId = m_chat.AddItem(autor, NULL, 1);
				m_chat.SetItemColor(itemId, 1, color);
							
				addedLinesCount = 0;
				chatMessage = comment.m_Message;			
				while (chatMessage.LengthUtf8() > 0)
				{		
					isLineFinished = false;
					chatLine = "";		
					for (q = 0; q < chatMessage.LengthUtf8() && !isLineFinished; q++)
					{
						chatLine = chatLine + chatMessage.SubstringUtf8(q, 1);
						m_callibrationText.SetText(chatLine);
						m_callibrationText.GetTextSize(textWidthCalibration, textHeightCalibration);
						
						if (textWidthCalibration >= chatLineMaxSize)
						{						
							isLineFinished = true;
						}
					}
					
					if (addedLinesCount == 0)
					{
						m_chat.SetItem(itemId, chatLine, NULL, 3);
					} 
					else
					{
						m_chat.AddItem(chatLine, NULL, 3);
					}
					
					m_chat.SetItemColor(itemId, 3, color);
					
					chatMessage = chatMessage.SubstringUtf8(chatLine.LengthUtf8(), chatMessage.LengthUtf8() - chatLine.LengthUtf8());
					addedLinesCount = addedLinesCount + 1;
					chatLinesCount = chatLinesCount + 1;
				}
			}
			
			m_callibrationText.SetText("");
			m_chat.SelectRow(chatLinesCount);
			m_chat.EnsureVisible(chatLinesCount);
			
			if ( (pluginGearPDA.m_onlineContacts.Find(contact.m_id) == -1) || (contact.m_IsBanned) )
			{
				m_message.Enable(false);
				m_send.Enable(false);
				m_sendFuncEnabled = false;
			}
			else
			{
				m_message.Enable(true);
				m_send.Enable(true);
				m_sendFuncEnabled = true;
			}
			
			if (contact.m_Unreaded > 0)
			{
				contact.m_Unreaded = 0;
				m_contactList.SetItem(id, "" + contact.m_Unreaded, NULL, 2);
				pluginGearPDA.SaveContactsConfig();
			}
		}
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_externalSendEvent)
		{
			SendMessageEvent();
			m_externalSendEvent = false;
		}
		
		if (m_addContactStatus == 2)
		{
			FillContactsList();
			m_addContactStatus = 0;
		}
		
		if (m_sendMessageStatus == 2)
		{
			FillContactsList();
			m_sendMessageStatus = 0;
		}
		
		if (m_lastSelectedContact != m_contactList.GetSelectedRow())
		{
			m_lastSelectedContact = m_contactList.GetSelectedRow();
			SelectConversation(m_lastSelectedContact);
		}
		
		if (m_addContactTimeout > 0 || m_addContactStatus != 0)
		{
			m_addContactTimeout = m_addContactTimeout - timeslice;
			m_addContactBtn.Enable(false);
		}
		else
		{
			m_addContactBtn.Enable(true);
		}
		
		if (m_sendMessageTimeout > 0 || m_sendMessageStatus != 0)
		{
			m_sendMessageTimeout = m_sendMessageTimeout - timeslice;
			m_send.Enable(false);
		}
		else
		{
			m_send.Enable(true);
		}
		
		if (m_dirty)
		{					
			PluginGearPDA pluginGearPDA;
			Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
			m_yourIdText.SetText("#pda_user_id " + pluginGearPDA.m_name);		
			
			FillContactsList();
			m_dirty = false;
		}
		
		if (m_updateBtnsPanel)
		{
			UpdateButtonsPagePanel();
			m_updateBtnsPanel = false;
		}
		
		if (m_updateGroupManagement)
		{
			m_updateGroupManagement = false;
			
			m_group_help_text.SetText(m_group_info);			
			m_groupMembersList.ClearItems();
			foreach (ref SyberiaPdaGroupMember member : m_group_members)
			{
				int itemId = m_groupMembersList.AddItem(member.m_id.ToString(), null, 1);
				m_groupMembersList.SetItem(itemId, member.m_name, null, 2);
				
				m_groupMembersList.SetItemColor(itemId, 1, ARGBF(1, 0.588, 0.662, 0.341));
				m_groupMembersList.SetItemColor(itemId, 2, ARGBF(1, 0.588, 0.662, 0.341));
			}
		}
		
		if (!m_active)
		{
			GetGame().GetUIManager().Back();
		}
	}
	
	void UpdateButtonsPagePanel()
	{
		float x, y, w, h, fw, fh;
		m_page_buttons_panel.GetSize(fw, fh);
		
		int btnsCount = 0;
		ref array<ref Widget> pagewgts = new array<ref Widget>;
		pagewgts.Insert(m_page_msg_back);
		pagewgts.Insert(m_page_map_back);
		pagewgts.Insert(m_page_grp_back);
		
		m_page_msg_back.GetPos(x, y);
		m_page_msg_back.GetSize(w, h);
		
		for (int i1 = 0; i1 < pagewgts.Count(); i1++)
		{
			if (m_visibleBtnsPanel[i1])
			{
				btnsCount = btnsCount + 1;
			}
		}

		float offset = 0;		
		float elemsize = fw / (float)btnsCount;		
		for (int i2 = 0; i2 < pagewgts.Count(); i2++)
		{
			ref Widget widg = pagewgts.Get(i2); 
			if (m_visibleBtnsPanel[i2])
			{				
				widg.Show(true);
				widg.SetPos(x + offset, y, true);			
				widg.SetSize(elemsize, h, true);
				offset = offset + elemsize;
			}
			else
			{
				widg.Show(false);
			}
		}
		
		delete pagewgts;
	}

	override void OnShow()
	{
		super.OnShow();

		PPERequesterBank.GetRequester(PPERequesterBank.REQ_INVENTORYBLUR).Start();

		GetGame().GetInput().ChangeGameFocus(1);

		SetFocus( layoutRoot );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(true);
		player.GetActionManager().EnableActions(false);
	}

	override void OnHide()
	{
		super.OnHide();

		PPERequesterBank.GetRequester(PPERequesterBank.REQ_INVENTORYBLUR).Stop();

		GetGame().GetInput().ResetGameFocus();
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
		player.GetActionManager().EnableActions(true);
		
		Close();
	}

	override bool OnKeyPress(Widget w, int x, int y, int key) {
		string boxText;
		if (w.GetName() == m_addContactTxt.GetName()) {
			boxText = m_addContactTxt.GetText();
			if (boxText.LengthUtf8() >= m_contactMaxLength) {
				return true;
			}
		}
		if (w.GetName() == m_message.GetName()) {
			boxText = m_message.GetText();
			if (boxText.LengthUtf8() >= m_messageMaxLength) {
				return true;
			}
		}
		if (w.GetName() == m_group_input.GetName()) {
			boxText = m_group_input.GetText();
			if (boxText.LengthUtf8() >= m_contactMaxLength) {
				return true;
			}
		}
		return false;
	}

	bool SendMessageEvent()
	{
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		
		if (m_sendFuncEnabled && m_sendMessageTimeout <= 0 && m_sendMessageStatus == 0)
		{
			int selectedRow = m_lastSelectedContact;
			string message = m_message.GetText();
			if (selectedRow >= 0 && message.LengthUtf8() > 0)
			{
				if (message.LengthUtf8() > m_messageMaxLength)
				{
					message = message.SubstringUtf8(0, m_messageMaxLength);
				}
				
				int rowShift = 0;
				if (pluginGearPDA.m_enableGlobalChat)
				{
					if (selectedRow == rowShift)
					{
						m_sendMessageTimeout = 1.0;
						m_sendMessageStatus = 1;
						GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_SEND_GLOBAL_MESSAGE, new Param1<string>( message ) );
						m_message.SetText("");	
						return true;				
					}
					
					rowShift = rowShift + 1;
				}
				if (pluginGearPDA.m_group_chatName.Length() > 0)
				{
					if (selectedRow == rowShift)
					{
						m_sendMessageTimeout = 1.0;
						m_sendMessageStatus = 1;
						GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_SEND_GROUP_MESSAGE, new Param1<string>( message ) );
						m_message.SetText("");	
						return true;				
					}
					
					rowShift = rowShift + 1;
				}
				


				ref PluginGearPDA_Conversation msgContact = pluginGearPDA.m_contacts[selectedRow - rowShift];				
				if ( (pluginGearPDA.m_onlineContacts.Find(msgContact.m_id) != -1) && (!msgContact.m_IsBanned) )
				{					
					m_sendMessageTimeout = 0.25;
					m_sendMessageStatus = 1;
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_SEND_MESSAGE, new Param2<int, string>( msgContact.m_id, message ) );
					m_message.SetText("");
					return true;
				}
			}
		}
		
		return false;
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		super.OnClick(w, x, y, button);
		
		int selectedRow;
		int rowShift;
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		
		if (w == m_addContactBtn)
		{
			if (m_addContactTimeout <= 0 && m_addContactStatus == 0)
			{
				string contactId = m_addContactTxt.GetText();
				if (contactId.LengthUtf8() <= m_contactMaxLength && contactId.LengthUtf8() > 0) {
					m_addContactStatus = 1;
					m_addContactTimeout = 1;
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_ADD_CONTACT, new Param1<string>( contactId ) );
				}	
			}
			return true;
		}
		
		if (w == m_send)
		{
			return SendMessageEvent();
		}
		
		if (w == m_deleteContactBtn)
		{
			selectedRow = m_lastSelectedContact;
			rowShift = 0;
			if (pluginGearPDA.m_enableGlobalChat)
			{				
				if (selectedRow == rowShift)
				{
					return true;
				}
				
				rowShift = rowShift + 1;
			}
			if (pluginGearPDA.m_group_chatName.Length() > 0)
			{
				if (selectedRow == rowShift)
				{
					return true;
				}
				
				rowShift = rowShift + 1;
			}
			
			if (selectedRow >= 0 && selectedRow < pluginGearPDA.m_contacts.Count() + rowShift)
			{
				int contactToDeleteId = pluginGearPDA.m_contacts[selectedRow - rowShift].m_id;
				pluginGearPDA.RemoveContact(contactToDeleteId);
				m_dirty = true;
			}
			return true;
		}
		
		if (w == m_mute_btn)
		{
			pluginGearPDA.m_options.m_Muted = !pluginGearPDA.m_options.m_Muted;
			UpdateMutedButton();
			return true;
		}

		if (w == m_rename_btn)
		{
			selectedRow = m_lastSelectedContact;
			rowShift = 0;
			if (pluginGearPDA.m_enableGlobalChat)
			{				
				if (selectedRow == rowShift)
				{
					return true;
				}
				
				rowShift = rowShift + 1;
			}
			if (pluginGearPDA.m_group_chatName.Length() > 0)
			{
				if (selectedRow == rowShift)
				{
					return true;
				}
				
				rowShift = rowShift + 1;
			}
			
			if (selectedRow >= 0 && selectedRow < pluginGearPDA.m_contacts.Count() + rowShift)
			{
				string newContactName = m_addContactTxt.GetText();
				if (newContactName.LengthUtf8() <= m_contactMaxLength && newContactName.LengthUtf8() > 0)
				{
					int contactToRenameId = pluginGearPDA.m_contacts[selectedRow - rowShift].m_id;
					pluginGearPDA.RenameContact(contactToRenameId, newContactName);
					m_dirty = true;
				}
			}
			return true;
		}
		
		if (w == m_ban_btn)
		{
			selectedRow = m_lastSelectedContact;
			rowShift = 0;
			if (pluginGearPDA.m_enableGlobalChat)
			{				
				if (selectedRow == rowShift)
				{
					return true;
				}
				
				rowShift = rowShift + 1;
			}
			if (pluginGearPDA.m_group_chatName.Length() > 0)
			{
				if (selectedRow == rowShift)
				{
					return true;
				}
				
				rowShift = rowShift + 1;
			}
			
			if (selectedRow >= 0 && selectedRow < pluginGearPDA.m_contacts.Count() + rowShift)
			{
				int contactToBanId = pluginGearPDA.m_contacts[selectedRow - rowShift].m_id;
				pluginGearPDA.BanUnbanContact(contactToBanId);
				m_dirty = true;
			}
			return true;
		}
		
		if (w == m_page_msg_btn)
		{
			SelectPdaPage(0);
			return true;
		}
		
		if (w == m_page_map_btn)
		{
			SelectPdaPage(1);
			return true;
		}
		
		if (w == m_page_grp_btn)
		{
			SelectPdaPage(2);
			return true;
		}
	
		if (w.GetName() == m_groupMembersList.GetName()) {
			return true;
		}
		
		if (w.GetName() == m_group_add_btn.GetName())
		{
			string memberId = m_group_input.GetText();
			if (memberId.LengthUtf8() > m_contactMaxLength) {
				memberId = memberId.SubstringUtf8(0, m_contactMaxLength);
			}
			
			m_group_input.SetText("");			
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_CMD_GROUP, new Param2< int, string >( 0, memberId ) );

			return true;
		}
		
		if (w.GetName() == m_group_del_btn.GetName())
		{
			int selectedMemberId = m_groupMembersList.GetSelectedRow();
			if (selectedMemberId >= 0 && selectedMemberId < m_group_members.Count())
			{
				ref SyberiaPdaGroupMember member = m_group_members.Get(selectedMemberId);
				GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_CMD_GROUP, new Param2< int, string >( 1, member.m_id.ToString() ) );
			}
			return true;
		}
		
		return false;
	}
	
	void UpdateMutedButton()
	{
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		
		if (pluginGearPDA.m_options.m_Muted)
		{
			m_mute_text.SetText("#pda_unmute");
		}
		else
		{
			m_mute_text.SetText("#pda_mute");
		}
	}

	override bool OnChange(Widget w, int x, int y, bool finished) {
		super.OnChange(w, x, y, finished);
		
		string boxText;
		if (w.GetName() == m_addContactTxt.GetName()) {
			boxText = m_addContactTxt.GetText();
			if (boxText.LengthUtf8() > m_contactMaxLength) {
				m_addContactTxt.SetText(boxText.SubstringUtf8(0, m_contactMaxLength));
			}
			return true;
		}
		if (w.GetName() == m_message.GetName()) {
			boxText = m_message.GetText();
			if (boxText.LengthUtf8() > m_messageMaxLength) {
				m_message.SetText(boxText.SubstringUtf8(0, m_messageMaxLength));
			}
			return true;
		}
		if (w.GetName() == m_group_input.GetName()) {
			boxText = m_group_input.GetText();
			if (boxText.LengthUtf8() > m_contactMaxLength) {
				m_group_input.SetText(boxText.SubstringUtf8(0, m_contactMaxLength));
			}
			return true;
		}
		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int  column,	int  oldRow, int  oldColumn)
	{
		super.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
		
		if (w == m_contactList)
		{
			return true;
		}
		
		if (w == m_chat)
		{
			return true;
		}
		
		if (w == m_groupMembersList)
		{
			return true;
		}
		
		return false;
	}
}