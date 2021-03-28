class PluginGearPDA extends PluginBase
{
	string m_configDir;
	
	ref GearPDAMenu m_GearPDAMenu;
	
	ref array<ref PluginGearPDA_Conversation> m_contacts;
	
	ref array<int> m_onlineContacts;
	
	ref map<int, ref array<ref PluginGearPDA_Comment>> m_comments;
	
	string m_name;
	
	bool m_enableGlobalChat;
	
	bool m_enableMapPage;
	
	ref array<ref Param2<string, string>> m_globalMessages;
	
	const string contactsBinFilename = "contacts.bin";
	
	const string optionsBinFilename = "options.bin";
	
	string m_group_chatName = "";
	
	ref array<ref Param2<string, string>> m_groupMessages;
	
	ref PluginGearPDA_Options m_options;
	
	int m_current_page_id = 0;
	
	void PluginGearPDA()
	{
		m_contacts = new array<ref PluginGearPDA_Conversation>();
		m_comments = new map<int, ref array<ref PluginGearPDA_Comment>>();
		m_onlineContacts = new array<int>();
		m_globalMessages = new array<ref Param2<string, string>>;
		m_groupMessages = new array<ref Param2<string, string>>;
		m_options = new PluginGearPDA_Options();
	}
	
	void ~PluginGearPDA()
	{
		SaveOptionsConfig();
	}
	
	void InitPdaProfile(string profileName)
	{
		MakeDirectory("$profile:Syberia\\");
		MakeDirectory("$profile:Syberia\\PDA\\");
		
		m_configDir = "$profile:Syberia\\PDA\\" + profileName + "\\";		
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
	
	void SaveCommentsConfig(int id)
	{
		if (m_comments.Contains(id))
		{
			ref array<ref PluginGearPDA_Comment> comments = m_comments[id];
			
			while (comments.Count() > 100)
			{
				comments.RemoveOrdered(0);
			}
			
			BinaryFileLoader<ref array<ref PluginGearPDA_Comment>>.BinarySaveFile(m_configDir + id + ".bin", comments);
		}
	}
	
	void LoadCommentsConfig(int id)
	{
		string fileName = m_configDir + id + ".bin";
		if (FileExist(fileName))
		{
			ref array<ref PluginGearPDA_Comment> result = new array<ref PluginGearPDA_Comment>(); 
			BinaryFileLoader<ref array<ref PluginGearPDA_Comment>>.BinaryLoadFile(fileName, result);
			m_comments[id] = result;
		}
	}
	
	ref array<ref PluginGearPDA_Comment> GetComments(int id)
	{
		if (!m_comments.Contains(id))
		{
			LoadCommentsConfig(id);
		}

		if (!m_comments.Contains(id))
		{
			m_comments[id] = new array<ref PluginGearPDA_Comment>();
		}
		
		return m_comments[id];
	}
	
	void AddComment(int contactId, int senderId, string message)
	{
		if (contactId != -1)
		{
			ref array<ref PluginGearPDA_Comment> comments = GetComments(contactId);
			ref PluginGearPDA_Comment comment = new PluginGearPDA_Comment();
			comment.m_id = senderId;
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
				
			ref array<int> request = new array<int>();
			for (int i = 0; i < m_contacts.Count(); i++)
			{
				request.Insert(m_contacts[i].m_id);
			}
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_PDA_CHECK_CONTACT, new Param1< ref array<int> >( request ) );
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
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (GetGame().GetUIManager().GetMenu() != NULL || !player || !player.CanOpenSyberiaUI())
		{
			return;
		}
		
		m_GearPDAMenu = new GearPDAMenu;
		GetGame().GetUIManager().ShowScriptedMenu( m_GearPDAMenu, NULL );
	}
	
	ref PluginGearPDA_Conversation FindContact(int id)
	{
		for (int i = 0; i < m_contacts.Count(); i++)
		{
			ref PluginGearPDA_Conversation item = m_contacts[i];
			if (item.m_id == id)
			{
				return item;
			}
		}
		
		return null;
	}
	
	void AddContact(int id, string name)
	{
		if (name.Length() > 0)
		{
			if (FindContact(id) == null)
			{
				ref PluginGearPDA_Conversation conv = new PluginGearPDA_Conversation();
				conv.m_id = id;
				conv.m_Name = name;
				conv.m_Unreaded = 0;
				conv.m_IsBanned = false;
				m_contacts.Insert(conv);
				m_onlineContacts.Insert(id);
				SaveContactsConfig();
			}
		}
		
		if (IsOpen())
		{
			m_GearPDAMenu.m_addContactStatus = 2;
		}
	}
	
	void RemoveContact(int id)
	{
		ref PluginGearPDA_Conversation contactToDelete = FindContact(id);
		if (contactToDelete == null)
		{
			return;
		}
		
		m_contacts.RemoveItem(contactToDelete);
		SaveContactsConfig();
		
		if (m_comments.Contains(id))
		{
			m_comments.Remove(id);
		}
		
		string fileName = m_configDir + id + ".bin";
		if (FileExist(fileName))
		{
			DeleteFile(fileName);
		}
	}
	
	void RenameContact(int id, string newName)
	{
		ref PluginGearPDA_Conversation contactToRename = FindContact(id);
		if (contactToRename == null)
		{
			return;
		}
		
		contactToRename.m_Name = newName;
		SaveContactsConfig();
	}
	
	void BanUnbanContact(int id)
	{
		ref PluginGearPDA_Conversation contactToRename = FindContact(id);
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
	
	void EnableGroupManagement(ref array<ref SyberiaPdaGroupMember> members, string infoText)
	{
		if (m_GearPDAMenu)
		{
			m_GearPDAMenu.EnableGroupManagement(members, infoText);
		}
	}
};

class PluginGearPDA_Conversation
{
	int m_id;
	string m_Name;
	int m_Unreaded;
	bool m_IsBanned;

	void PluginGearPDA_Conversation()
	{
	
	}
};

class PluginGearPDA_Comment
{
	int m_id;
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