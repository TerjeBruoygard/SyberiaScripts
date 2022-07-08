class PluginGearPDA extends PluginBase
{
	string m_configDir;
	
	ref GearPDAMenu m_GearPDAMenu;
	
	ref array<ref PluginGearPDA_Conversation> m_contacts;
	
	ref array<string> m_onlineContacts;
	
	ref map<string, ref array<ref PluginGearPDA_Comment>> m_comments;
	
	string m_steamId;
	
	bool m_enableGlobalChat;
	
	bool m_enableMapPage;
	
	ref array<ref Param2<string, string>> m_globalMessages;
	
	const string contactsBinFilename = "contacts.bin";
	
	const string optionsBinFilename = "options.bin";
	
	string m_group_chatName = "";
	
	ref array<ref Param2<string, string>> m_groupMessages;
	
	ref PluginGearPDA_Options m_options;
	
	void PluginGearPDA()
	{
		m_contacts = new array<ref PluginGearPDA_Conversation>();
		m_comments = new map<string, ref array<ref PluginGearPDA_Comment>>();
		m_onlineContacts = new array<string>();
		m_globalMessages = new array<ref Param2<string, string>>;
		m_groupMessages = new array<ref Param2<string, string>>;
		m_options = new PluginGearPDA_Options();
		m_configDir = "$profile:SyberiaPDA\\";
	}
	
	void ~PluginGearPDA()
	{
		SaveOptionsConfig();
	}
	
	override void OnInit()
	{
		MakeDirectory(m_configDir);
		
		if (!FileExist(m_configDir + contactsBinFilename)) {
			SaveOptionsConfig();
            SaveContactsConfig();
        } else {
			LoadOptionsConfig();
            LoadContactsConfig();
        }
	}
	
	void SaveOptionsConfig()
	{
		BinaryFileLoader<ref PluginGearPDA_Options>.BinarySaveFile(m_configDir + optionsBinFilename, m_options);
	}
	
	void LoadOptionsConfig()
	{
		BinaryFileLoader<ref PluginGearPDA_Options>.BinaryLoadFile(m_configDir + optionsBinFilename, m_options);
	}
	
	void SaveContactsConfig()
	{
		BinaryFileLoader<ref array<ref PluginGearPDA_Conversation>>.BinarySaveFile(m_configDir + contactsBinFilename, m_contacts);
	}
	
	void LoadContactsConfig()
	{
		BinaryFileLoader<ref array<ref PluginGearPDA_Conversation>>.BinaryLoadFile(m_configDir + contactsBinFilename, m_contacts);
	}
	
	void SaveCommentsConfig(string uid)
	{
		if (m_comments.Contains(uid))
		{
			ref array<ref PluginGearPDA_Comment> comments = m_comments[uid];
			
			while (comments.Count() > 100)
			{
				comments.RemoveOrdered(0);
			}
			
			BinaryFileLoader<ref array<ref PluginGearPDA_Comment>>.BinarySaveFile(m_configDir + uid + ".bin", comments);
		}
	}
	
	void LoadCommentsConfig(string uid)
	{
		string fileName = m_configDir + uid + ".bin";
		if (FileExist(fileName))
		{
			ref array<ref PluginGearPDA_Comment> result = new array<ref PluginGearPDA_Comment>(); 
			BinaryFileLoader<ref array<ref PluginGearPDA_Comment>>.BinaryLoadFile(fileName, result);
			m_comments[uid] = result;
		}
	}
	
	ref array<ref PluginGearPDA_Comment> GetComments(string uid)
	{
		if (!m_comments.Contains(uid))
		{
			LoadCommentsConfig(uid);
		}

		if (!m_comments.Contains(uid))
		{
			m_comments[uid] = new array<ref PluginGearPDA_Comment>();
		}
		
		return m_comments[uid];
	}
	
	void AddComment(string contactId, string senderId, string message)
	{
		if (contactId.Length() > 0)
		{
			ref array<ref PluginGearPDA_Comment> comments = GetComments(contactId);
			ref PluginGearPDA_Comment comment = new PluginGearPDA_Comment();
			comment.m_UID = senderId;
			comment.m_Message = message;
			comments.Insert(comment);
			
			SaveCommentsConfig(contactId);
			
			ref PluginGearPDA_Conversation contact = FindContact(contactId);
			if (contact != null)
			{
				contact.m_Unreaded = contact.m_Unreaded + 1;
				SaveContactsConfig();
			}
			
			if (IsOpen())
			{
				m_GearPDAMenu.m_sendMessageStatus = 2;
			}
		}
		else
		{
			if (IsOpen())
			{
				m_GearPDAMenu.m_sendMessageStatus = 0;
			}
				
			ref array<string> request = new array<string>();
			for (int i = 0; i < m_contacts.Count(); i++)
			{
				request.Insert(m_contacts[i].m_UID);
			}
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_CHECK_CONTACT, new Param1< ref array<string> >( request ) );
            delete request;
		}
	}
	
	bool IsOpen()
	{
		return m_GearPDAMenu && m_GearPDAMenu.m_active;
	}
	
	void Open()
	{
		if (IsOpen())
		{
			Close();
		}
		
		if (GetGame().GetUIManager().GetMenu() != NULL)
		{
			return;
		}
		
		m_GearPDAMenu = new GearPDAMenu;
		GetGame().GetUIManager().ShowScriptedMenu( m_GearPDAMenu, NULL );
	}
	
	ref PluginGearPDA_Conversation FindContact(string uid)
	{
		for (int i = 0; i < m_contacts.Count(); i++)
		{
			ref PluginGearPDA_Conversation item = m_contacts[i];
			if (item.m_UID == uid)
			{
				return item;
			}
		}
		
		return null;
	}
	
	void AddContact(string uid, string name)
	{
		if (uid.Length() > 0 && name.Length() > 0)
		{
			if (FindContact(uid) == null)
			{
				ref PluginGearPDA_Conversation conv = new PluginGearPDA_Conversation();
				conv.m_UID = uid;
				conv.m_Name = name;
				conv.m_Unreaded = 0;
				conv.m_IsBanned = false;
				m_contacts.Insert(conv);
				m_onlineContacts.Insert(uid);
				SaveContactsConfig();
			}
		}
		
		if (IsOpen())
		{
			m_GearPDAMenu.m_addContactStatus = 2;
		}
	}
	
	void RemoveContact(string uid)
	{
		ref PluginGearPDA_Conversation contactToDelete = FindContact(uid);
		if (contactToDelete == null)
		{
			return;
		}
		
		m_contacts.RemoveItem(contactToDelete);
		SaveContactsConfig();
		
		if (m_comments.Contains(uid))
		{
			m_comments.Remove(uid);
		}
		
		string fileName = m_configDir + uid + ".bin";
		if (FileExist(fileName))
		{
			DeleteFile(fileName);
		}
	}
	
	void RenameContact(string uid, string newName)
	{
		ref PluginGearPDA_Conversation contactToRename = FindContact(uid);
		if (contactToRename == null)
		{
			return;
		}
		
		contactToRename.m_Name = newName;
		SaveContactsConfig();
	}
	
	void BanUnbanContact(string uid)
	{
		ref PluginGearPDA_Conversation contactToRename = FindContact(uid);
		if (contactToRename == null)
		{
			return;
		}
		
		contactToRename.m_IsBanned = !contactToRename.m_IsBanned;
		SaveContactsConfig();
	}
	
	void Close()
	{
		if (m_GearPDAMenu)
		{
			m_GearPDAMenu.m_active = false;
		}
	}
	
	void EnableGroupManagement(ref array<ref GroupMember> members, string infoText)
	{
		if (m_GearPDAMenu)
		{
			m_GearPDAMenu.EnableGroupManagement(members, infoText);
		}
	}
};

class PluginGearPDA_Conversation
{
	string m_UID;
	string m_Name;
	int m_Unreaded;
	bool m_IsBanned;

	void PluginGearPDA_Conversation()
	{
	
	}
};

class PluginGearPDA_Comment
{
	string m_UID;
	string m_Message;
	
	void PluginGearPDA_Comment()
	{
	
	}
};

class PluginGearPDA_Options
{
	bool m_Muted;
	bool m_HideId;
	
	void PluginGearPDA_Options()
	{
	
	}
};