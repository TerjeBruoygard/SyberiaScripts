modded class PluginManager
{
	override void Init()
	{
        RegisterPlugin("PluginSyberiaRpc", true, true);
		
		if (GetGame().IsClient())
		{
			RegisterPlugin("PluginSyberiaLogin", true, false);
		}
        
		super.Init();
	}
}