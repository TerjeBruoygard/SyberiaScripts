modded class LoginTimeBase
{
	override Widget Init()
	{
		Widget result = super.Init();		
		m_btnLeave.Show(false);
		return result;
	}
	
	override void Leave()
	{
		// DO NOTHING
	}
	
	override void Update(float timeslice)
	{
		if (IsRespawn())
		{
			return;
		}
		
		super.Update(timeslice);
	}
};

modded class DayZGame
{
	override void OnRespawnEvent(int time)
	{
		PPEffects.SetDeathDarkening(1);
	}
};

class GameHelpers
{
	static string GetItemDisplayName(string itemClassname)
	{
		string cfg = "CfgVehicles " + itemClassname + " displayName";
		string displayName;
		GetGame().ConfigGetText(cfg, displayName);
	
		if (displayName == "")
		{
			cfg = "CfgAmmo " + itemClassname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
		
		if (displayName == "")
		{
			cfg = "CfgMagazines " + itemClassname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
		
		if (displayName == "")
		{
			cfg = "cfgWeapons " + itemClassname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
	
		if (displayName == "")
		{
			cfg = "CfgNonAIVehicles " + itemClassname + " displayName";
			GetGame().ConfigGetText(cfg, displayName);
		}
		
		
		if (displayName != "")
			return displayName;
		else
			return itemClassname;
	}
}