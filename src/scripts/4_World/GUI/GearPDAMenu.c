class GearPDAMenu extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
	
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
	ref ButtonWidget m_hideId_btn;
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
	
	ref ButtonWidget m_page_msg_btn;
	ref ButtonWidget m_page_map_btn;
	ref ButtonWidget m_page_grp_btn;
	
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
	
	int m_selectedPage = 0;
	bool m_updateGroupManagement = false;
	ref array<ref GroupMember> m_group_members = null;
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
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layouts/GearPDAMenu.layout" );

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
		m_hideId_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "hideid_btn" ) );
		m_rename_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "rename_contact_btn" ) );
		m_ban_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ban_contact_btn" ) );
		m_map = MapWidget.Cast( layoutRoot.FindAnyWidget("map_widget") );
		
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
		
		UpdateMutedButton();
		UpdateHideIdButton();
				
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
				
		ref array<string> request = new array<string>();
		for (int i = 0; i < pluginGearPDA.m_contacts.Count(); i++)
		{
			request.Insert(pluginGearPDA.m_contacts[i].m_UID);
		}
		
		if (!m_active) 
		{
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_CHECK_CONTACT, new Param1< ref array<string> >( request ) );
			m_yourIdText.SetText("#pda_loading");
			m_message.Enable(false);
			m_send.Enable(false);
			m_sendFuncEnabled = false;
		}
		
		delete request;
		m_active = true;		
        return layoutRoot;
    }
	
	void EnableGroupManagement(ref array<ref GroupMember> members, string infoText)
	{
		m_group_members = members;
		m_group_info = infoText;
		m_updateGroupManagement = true;
	}
	
	void SelectPdaPage(int id)
	{
		if (m_selectedPage == id)
		{
			return;
		}
		
		m_selectedPage = id;
		m_page_msg.Show(false);
		m_page_map.Show(false);
		m_page_grp.Show(false);
		
		if (id == 0)
		{
			m_page_msg.Show(true);
		}
		else if (id == 1)
		{
			m_page_map.Show(true);
		}
		else if (id == 2)
		{
			m_page_grp.Show(true);
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
			itemId = m_contactList.AddItem("#pda_global_chat", NULL, 0);
			m_contactList.SetItem(itemId, "", NULL, 1);
			m_contactList.SetItemColor(itemId, 0, ARGBF(1, 0.0, 0.529, 0.858));
		}
		
		if (pluginGearPDA.m_group_chatName.Length() > 0)
		{
			rowShift = rowShift + 1;
			itemId = m_contactList.AddItem(pluginGearPDA.m_group_chatName, NULL, 0);
			m_contactList.SetItem(itemId, "", NULL, 1);
			m_contactList.SetItemColor(itemId, 0, ARGBF(1, 0.0, 0.529, 0.858));
		}
				
		for (int i = 0; i < pluginGearPDA.m_contacts.Count(); i++)
		{
			ref PluginGearPDA_Conversation contact = pluginGearPDA.m_contacts[i];
			itemId = m_contactList.AddItem(contact.m_Name, NULL, 0);
			m_contactList.SetItem(itemId, "" + contact.m_Unreaded, NULL, 1);
			
			if (contact.m_IsBanned)
			{
				m_contactList.SetItemColor(itemId, 0, ARGBF(1, 0.8, 0.02, 0.02));
			}
			else if (pluginGearPDA.m_onlineContacts.Find(contact.m_UID) != -1)
			{
				m_contactList.SetItemColor(itemId, 0, ARGBF(1, 0.2, 0.8, 0.02));
			}
			else
			{
				m_contactList.SetItemColor(itemId, 0, ARGBF(1, 0.7, 0.7, 0.7));
			}			
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
		int chatLineMaxSize = (int)(chatWidth * 0.85) - 50;
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
				itemId = m_chat.AddItem(autor, NULL, 0);							
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
						m_chat.SetItem(itemId, chatLine, NULL, 1);
					} 
					else
					{
						m_chat.AddItem(chatLine, NULL, 1);
					}
					
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
			ref array<ref PluginGearPDA_Comment> comments = pluginGearPDA.GetComments(contact.m_UID);

			for (i = 0; i < comments.Count(); i++)
			{
				ref PluginGearPDA_Comment comment = comments[i];	
				if (comment.m_UID == GetGame().GetPlayer().GetIdentity().GetId())
				{
					autor = "Me";
					color = ARGBF(1, 0.2, 0.8, 0.2);
				}
				else
				{
					autor = contact.m_Name;
					color = ARGBF(1, 0.976, 1, 0.298);
				}
							
				itemId = m_chat.AddItem(autor, NULL, 0);
				m_chat.SetItemColor(itemId, 0, color);
							
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
						m_chat.SetItem(itemId, chatLine, NULL, 1);
					} 
					else
					{
						m_chat.AddItem(chatLine, NULL, 1);
					}
					
					chatMessage = chatMessage.SubstringUtf8(chatLine.LengthUtf8(), chatMessage.LengthUtf8() - chatLine.LengthUtf8());
					addedLinesCount = addedLinesCount + 1;
					chatLinesCount = chatLinesCount + 1;
				}
			}
			
			m_callibrationText.SetText("");
			m_chat.SelectRow(chatLinesCount);
			m_chat.EnsureVisible(chatLinesCount);
			
			if ( (pluginGearPDA.m_onlineContacts.Find(contact.m_UID) == -1) || (contact.m_IsBanned) )
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
				m_contactList.SetItem(id, "" + contact.m_Unreaded, NULL, 1);
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
			m_yourIdText.SetText("#pda_user_id " + pluginGearPDA.m_steamId);		
			
			FillContactsList();
			m_dirty = false;
		}
		
		if (m_updateGroupManagement)
		{
			m_updateGroupManagement = false;
			
			m_group_help_text.SetText(m_group_info);			
			m_groupMembersList.ClearItems();
			foreach (ref GroupMember member : m_group_members)
			{
				int pos = m_groupMembersList.AddItem(member.m_uid, null, 0);
				m_groupMembersList.SetItem(pos, member.m_name, null, 1);
			}
			
			m_page_grp_btn.Show(true);
		}
		
		if (!m_active)
		{
			GetGame().GetUIManager().Back();
		}
	}

	override void OnShow()
	{
		super.OnShow();

		PPEffects.SetBlurMenu(0.5);

		GetGame().GetInput().ChangeGameFocus(1);

		SetFocus( layoutRoot );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(true);
		player.GetActionManager().EnableActions(false);
	}

	override void OnHide()
	{
		super.OnHide();

		PPEffects.SetBlurMenu(0);

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
					message = message.Substring(0, m_messageMaxLength);
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
				string target = msgContact.m_UID;					
				if ( (pluginGearPDA.m_onlineContacts.Find(target) != -1) && (!msgContact.m_IsBanned) )
				{					
					m_sendMessageTimeout = 0.25;
					m_sendMessageStatus = 1;
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_SEND_MESSAGE, new Param2<string, string>( target, message ) );
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
				string contactToDeleteUid = pluginGearPDA.m_contacts[selectedRow - rowShift].m_UID;
				pluginGearPDA.RemoveContact(contactToDeleteUid);
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
		
		if (w == m_hideId_btn)
		{
			pluginGearPDA.m_options.m_HideId = !pluginGearPDA.m_options.m_HideId;
			UpdateHideIdButton();
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
					string contactToRenameUid = pluginGearPDA.m_contacts[selectedRow - rowShift].m_UID;
					pluginGearPDA.RenameContact(contactToRenameUid, newContactName);
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
				string contactToBanUid = pluginGearPDA.m_contacts[selectedRow - rowShift].m_UID;
				pluginGearPDA.BanUnbanContact(contactToBanUid);
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
				memberId = memberId.Substring(0, m_contactMaxLength);
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
				ref GroupMember member = m_group_members.Get(selectedMemberId);
				GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_CMD_GROUP, new Param2< int, string >( 1, member.m_guid ) );
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
			m_mute_btn.SetText("#pda_unmute");
		}
		else
		{
			m_mute_btn.SetText("#pda_mute");
		}
	}
	
	void UpdateHideIdButton()
	{
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		
		if (pluginGearPDA.m_options.m_HideId)
		{
			m_hideId_btn.SetText("#pda_unhideId");
			m_yourIdText.Show(false);
		}
		else
		{
			m_hideId_btn.SetText("#pda_hideId");
			m_yourIdText.Show(true);
		}
	}	

	override bool OnChange(Widget w, int x, int y, bool finished) {
		super.OnChange(w, x, y, finished);
		
		string boxText;
		if (w.GetName() == m_addContactTxt.GetName()) {
			boxText = m_addContactTxt.GetText();
			if (boxText.LengthUtf8() > m_contactMaxLength) {
				m_addContactTxt.SetText(boxText.Substring(0, m_contactMaxLength));
			}
			return true;
		}
		if (w.GetName() == m_message.GetName()) {
			boxText = m_message.GetText();
			if (boxText.LengthUtf8() > m_messageMaxLength) {
				m_message.SetText(boxText.Substring(0, m_messageMaxLength));
			}
			return true;
		}
		if (w.GetName() == m_group_input.GetName()) {
			boxText = m_group_input.GetText();
			if (boxText.LengthUtf8() > m_contactMaxLength) {
				m_group_input.SetText(boxText.Substring(0, m_contactMaxLength));
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