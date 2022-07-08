class ActionOpenPDA extends ActionSingleUseBase
{
	void ActionOpenPDA()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM_ONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM_ONCE;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( item && !item.IsRuined() && item.HasEnergyManager() && item.GetCompEM().CanWork() )
		{
			if (GetGame().IsClient() && player.CanOpenSyberiaUI())
			{
				PluginGearPDA pluginGearPDA;
				Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
				
				if (!pluginGearPDA)
				{
					return false;
				}
				
				if (pluginGearPDA.IsOpen())
				{
					return false;
				}
			}
				
			return true;
		}
		
		return false;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{		
		action_data.m_MainItem.GetCompEM().ConsumeEnergy(0.01);
		
		PluginGearPDA pluginGearPDA;
		Class.CastTo(pluginGearPDA, GetPlugin(PluginGearPDA));
		
		if (pluginGearPDA && !pluginGearPDA.IsOpen())
		{					
			pluginGearPDA.Open();
		}
	}

	override void OnExecuteServer( ActionData action_data )
	{
		action_data.m_MainItem.GetCompEM().ConsumeEnergy(0.01);
	}
};