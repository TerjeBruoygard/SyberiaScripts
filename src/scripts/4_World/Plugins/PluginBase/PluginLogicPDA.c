class PluginLogicPDA extends PluginBase
{	
	EffectSound effect;

	override void OnInit()
	{
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_USER_STATE, this, "InitPdaProfile");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_ADD_CONTACT, this, "AddContact");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_CHECK_CONTACT, this, "CheckContacts");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_SEND_MESSAGE, this, "SendMessage");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_SEND_GLOBAL_MESSAGE, this, "SendGlobalMessage");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_SEND_GROUP_MESSAGE, this, "SendGroupMessage");
        GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_PDA_CMD_GROUP, this, "GroupCommand");
	}
	
	bool HasWorkingPDA(PlayerBase player)
	{
		array<EntityAI> itemsArray = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		ItemBase itemInHands = player.GetItemInHands();
		if (itemInHands)
		{
			itemsArray.Insert( itemInHands );
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
	
	void SendGlobalMessage( ParamsReadContext ctx, PlayerIdentity sender )
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
	
	void SendGroupMessage( ParamsReadContext ctx, PlayerIdentity sender )
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
	
	void SendMessage( ParamsReadContext ctx, PlayerIdentity sender )
    { 
        Param4< int, string, int, string > clientData;			
        if ( !ctx.Read( clientData ) ) return;
        
        int contactId = clientData.param1;
        string contactName = clientData.param2;
        int userSenderId = clientData.param3;
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

	void CheckContacts( ParamsReadContext ctx, PlayerIdentity sender )
    { 
        Param5< array<int>, bool, ref array<ref SyberiaPdaGroupMember>, string, string > clientData;
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
	
	void InitPdaProfile( ParamsReadContext ctx, PlayerIdentity sender )
    {   
        Param4<string, string, bool, bool> clientData;
        if ( !ctx.Read( clientData ) ) return;
        
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
        if (pluginGearPDA)
        {
            pluginGearPDA.m_name = clientData.param1;
            pluginGearPDA.m_enableGlobalChat = clientData.param3;
			pluginGearPDA.m_enableMapPage = clientData.param4;
			pluginGearPDA.InitPdaProfile(clientData.param2);
        }
	}
	
	void AddContact( ParamsReadContext ctx, PlayerIdentity sender )
    {        
        Param2< int, string > clientData;
        if ( !ctx.Read( clientData ) ) return;
        
        PluginGearPDA pluginGearPDA;
        Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
        if (pluginGearPDA && pluginGearPDA.IsOpen())
        {
            pluginGearPDA.AddContact(clientData.param1, clientData.param2);
        }
    }
	
	void GroupCommand( ParamsReadContext ctx, PlayerIdentity sender )
	{
	
	}
};

class SyberiaPdaGroupMember
{
	int m_id;
	string m_name;
};