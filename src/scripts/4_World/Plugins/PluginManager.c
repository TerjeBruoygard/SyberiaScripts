modded class PluginManager
{
	override void Init()
	{
		RegisterPlugin("PluginSyberiaRpc", true, true);
		RegisterPlugin("PluginLogicPDA", true, true);
		RegisterPlugin("PluginSyberiaOptions", true, true);
        RegisterPlugin("PluginTrader", true, true);
		
		if (GetGame().IsClient())
		{
			RegisterPlugin("PluginSyberiaLogin", true, false);
			RegisterPlugin("PluginGearPDA", true, false);
		}
		
        RegisterPlugin("PluginAdminTool", true, true);
        
		super.Init();
	}
}