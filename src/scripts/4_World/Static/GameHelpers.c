class GameHelpers
{
	static bool StringContainsCaseInsensetive(string text, string match)
	{
		string lowercaseText = text;
		lowercaseText.ToLower();
		match.ToLower();
		return lowercaseText.Contains(match);
	}
	
	static void GetAllClasses(string preffix, ref array<string> output)
	{
		string classname;
		int childCount = GetGame().ConfigGetChildrenCount(preffix);
		for (int i = 0; i < childCount; i++)
		{
			if (GetGame().ConfigGetChildName(preffix, i, classname))
			{
				if (GetGame().ConfigGetInt(preffix + " " + classname + " scope") == 2)
				{
					output.Insert(classname);
				}
			}
		}
	}
	
	static string FindItemPreffix(string itemClassname)
	{
		if (GetGame().ConfigIsExisting("CfgVehicles " + itemClassname)) return "CfgVehicles";
		if (GetGame().ConfigIsExisting("CfgMagazines " + itemClassname)) return "CfgMagazines";
		if (GetGame().ConfigIsExisting("CfgAmmo " + itemClassname)) return "CfgAmmo";
		if (GetGame().ConfigIsExisting("cfgWeapons " + itemClassname)) return "cfgWeapons";
		if (GetGame().ConfigIsExisting("CfgNonAIVehicles " + itemClassname)) return "CfgNonAIVehicles";
		return "";
	}
	
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
	
	static vector GetCursorPos()
	{
	    if ( !GetGame().GetPlayer() )
	        return "0 0 0";

	    vector rayStart = GetGame().GetCurrentCameraPosition();
	    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;
	    vector hitPos;
	    vector hitNormal;
	    int hitComponentIndex;
	    DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, GetGame().GetPlayer());
	    return hitPos;
	}
};