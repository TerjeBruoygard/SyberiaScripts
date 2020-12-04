class PluginLogicPDA extends PluginBase
{	
	EffectSound effect;
	
	void PluginLogicPDA()
	{

	}
	
	void ~PluginLogicPDA()
	{

	}
	
	override void OnInit()
	{
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_USER_STATE, this, "GetVisualUserId");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_ADD_CONTACT, this, "AddContact");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_CHECK_CONTACT, this, "CheckContacts");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_SEND_MESSAGE, this, "SendMessage");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_SEND_GLOBAL_MESSAGE, this, "SendGlobalMessage");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_SEND_GROUP_MESSAGE, this, "SendGroupMessage");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_CMD_GROUP, this, "GroupCommand");
		
		if (GetGame().IsClient())
		{
            GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_PDA_USER_STATE, new Param1<string>( "" ));
		}
	}
	
	bool HasWorkingPDA(PlayerBase player)
	{
		array<EntityAI> itemsArray = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		ItemBase itemInHands = player.GetItemInHands();
		if (itemInHands)
		{
			itemsArray.Insert(EntityAI.Cast(itemInHands));
		}
		
		ItemPDA item;		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			ItemPDA.CastTo(item, itemsArray.Get(i));

			if (!item)
				continue;

			if (item.IsRuined())
				continue;

			if (!item.HasEnergyManager())
				continue;
			
			if (!item.GetCompEM().CanWork())
				continue;

			return true;
		}
		
		return false;
	}
	
	void SendGlobalMessage( ref ParamsReadContext ctx, ref PlayerIdentity sender )
	{
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));			
        if (pluginGearPDA && pluginGearPDA.m_enableGlobalChat)
        {
            Param2< string, string > clientData;			
            if ( !ctx.Read( clientData ) ) return;
            
            pluginGearPDA.m_globalMessages.Insert(clientData);
            
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
            if (player && HasWorkingPDA(player))
            {
                if (!pluginGearPDA.m_options.m_Muted)
                {	
                    GetGame().GetPlayer().PlaySoundSet(effect, "messagePDA_SoundSet", 0, 0);
                }
                
                if (pluginGearPDA.IsOpen())
                {
                    pluginGearPDA.m_GearPDAMenu.m_sendMessageStatus = 2;
                }
            }
        }
	}
	
	void SendGroupMessage( ref ParamsReadContext ctx, ref PlayerIdentity sender )
	{
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));			
        if (pluginGearPDA)
        {
            Param2< string, string > clientData;			
            if ( !ctx.Read( clientData ) ) return;
            
            pluginGearPDA.m_groupMessages.Insert(clientData);
            
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
            if (player && HasWorkingPDA(player))
            {
                if (!pluginGearPDA.m_options.m_Muted)
                {	
                    GetGame().GetPlayer().PlaySoundSet(effect, "messagePDA_SoundSet", 0, 0);
                }
                
                if (pluginGearPDA.IsOpen())
                {
                    pluginGearPDA.m_GearPDAMenu.m_sendMessageStatus = 2;
                }
            }
        }
	}
	
	void SendMessage( ref ParamsReadContext ctx, ref PlayerIdentity sender )
    { 
        Param4< string, string, string, string > clientData;			
        if ( !ctx.Read( clientData ) ) return;
        
        string contactId = clientData.param1;
        string contactName = clientData.param2;
        string userSenderId = clientData.param3;
        string message = clientData.param4;
        
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));			
        if (pluginGearPDA)
        {
            ref PluginGearPDA_Conversation msgContact = pluginGearPDA.FindContact(contactId);
            if (msgContact == null)
            {
                pluginGearPDA.AddContact(contactId, contactName);
                msgContact = pluginGearPDA.FindContact(contactId);
            }
            
            if (!msgContact.m_IsBanned)
            {
                if (userSenderId == contactId && !pluginGearPDA.m_options.m_Muted)
                {	
                    GetGame().GetPlayer().PlaySoundSet(effect, "messagePDA_SoundSet", 0, 0);
                }
                
                pluginGearPDA.AddComment(contactId, userSenderId, message);
            }
        }
	}

	void CheckContacts( ref ParamsReadContext ctx, ref PlayerIdentity sender )
    { 
        Param5< array<string>, bool, ref array<ref GroupMember>, string, string > clientData;
        if ( !ctx.Read( clientData ) ) return;
        
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
        if (pluginGearPDA)
        {
            if (clientData.param1)
            {
                pluginGearPDA.m_onlineContacts.Clear();
                pluginGearPDA.m_onlineContacts.Copy(clientData.param1);
            }
            
            if (clientData.param5 != pluginGearPDA.m_group_chatName)
            {
                pluginGearPDA.m_group_chatName = clientData.param5;
                pluginGearPDA.m_groupMessages.Clear();
            }
            
            if (pluginGearPDA.IsOpen())
            {
                if (clientData.param2)
                {
                    pluginGearPDA.EnableGroupManagement(clientData.param3, clientData.param4);
                }
                
                pluginGearPDA.m_GearPDAMenu.m_dirty = true;
            }
        }
	}
	
	void GetVisualUserId( ref ParamsReadContext ctx, ref PlayerIdentity sender )
    {   
        Param2<string, bool> clientData;
        if ( !ctx.Read( clientData ) ) return;
        
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
        if (pluginGearPDA)
        {
            pluginGearPDA.m_steamId = clientData.param1;
            pluginGearPDA.m_enableGlobalChat = clientData.param2;
        }
	}
	
	void AddContact( ref ParamsReadContext ctx, ref PlayerIdentity sender )
    {        
        Param2< string, string > clientData;
        if ( !ctx.Read( clientData ) ) return;
        
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
        if (pluginGearPDA && pluginGearPDA.IsOpen())
        {
            pluginGearPDA.AddContact(clientData.param1, clientData.param2);
        }
    }
	
	void GroupCommand( ref ParamsReadContext ctx, ref PlayerIdentity sender )
	{
	
	}
};

class GroupMember
{
	string m_guid;
	string m_uid;
	string m_name;
};