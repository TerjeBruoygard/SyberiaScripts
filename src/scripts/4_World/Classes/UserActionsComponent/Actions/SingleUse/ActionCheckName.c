class ActionCheckName: ActionInteractBase
{
	void ActionCheckName()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTDummy( );
	}

	override string GetText()
	{
		return "#syb_inspect_player";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetItemInHands()) return false;
		
		Stethoscope itemStatoschope = Stethoscope.Cast(player.GetItemOnSlot("Eyewear"));
		if (itemStatoschope)
			return false;
		
		PlayerBase ntarget = PlayerBase.Cast( target.GetObject() );
		if( !ntarget ) return false;
		
		int mode = 0;		
		if (GetSyberiaOptions() && GetSyberiaOptions().m_client)
		{
			mode = GetSyberiaOptions().m_client.m_checkIdentityMode;
		}

		if (mode == 0)
		{
			return false;
		}
		
		if (mode == 1)
		{
			if (!ntarget.IsFaceBlocked(false))
			{
				return true;
			}
		}
		else if (mode == 2)
		{
			if (!ntarget.IsAlive() || ntarget.IsUnconscious() || ntarget.IsRestrained())
			{
				return true;
			}
		}

		return false;
	}
};

class ActionSayName: ActionInteractBase
{
	void ActionSayName()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "#syb_say_name";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetItemInHands()) return false;
		
		Stethoscope itemStatoschope = Stethoscope.Cast(player.GetItemOnSlot("Eyewear"));
		if (itemStatoschope)
			return false;
		
		PlayerBase ntarget = PlayerBase.Cast( target.GetObject() );
		if( !ntarget ) return false;
		
		int mode = 0;		
		if (GetSyberiaOptions() && GetSyberiaOptions().m_client)
		{
			mode = GetSyberiaOptions().m_client.m_checkIdentityMode;
		}
		
		if (mode != 2)
		{
			return false;
		}
		
		if (ntarget.IsAlive() && !ntarget.IsUnconscious() && !ntarget.IsRestrained())
		{
			return true;
		}
		
		return false;
	}
	
	override void OnEndClient( ActionData action_data )
	{
		if (action_data.m_Player && action_data.m_Player.GetEmoteManager())
		{
			action_data.m_Player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_GREETING);
		}
	}
};