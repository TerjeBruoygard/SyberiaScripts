class GameHelpers
{
	static Transport GetPlayerVehicle(PlayerBase player)
	{
		if (player.GetCommand_Vehicle())
		{
			return player.GetCommand_Vehicle().GetTransport();
		}

		return null;
	}
	
	static bool HasBatterySlot(string classname)
	{
		array<string> slots = new array<string>;
		string preffix = FindItemPreffix(classname);
		GetGame().ConfigGetTextArray( preffix + " " + classname + " attachments", slots);
		return slots && slots.Find("BatteryD") != -1;
	}
	
	static bool StringContainsCaseInsensetive(string text, string match)
	{
		string lowercaseText = text;
		lowercaseText.ToLower();
		match.ToLower();
		return lowercaseText.Contains(match);
	}
	
	static int StringIndexOfUtf8(string str, string match)
	{
		int lng = str.LengthUtf8();
		int mng = match.LengthUtf8();
		if (lng < mng) return -1;
		
		string substr;
		int dif = lng - mng;
		for (int i = 0; i <= dif; i++)
		{
			substr = str.SubstringUtf8(i, mng);
			if (substr == match) return i;
		}
		
		return -1;
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
	
	static void GetAllAttachments(string attachmentType, ref array<string> output)
	{
		GetAllAttachments2("CfgVehicles", attachmentType, output);
		GetAllAttachments2("CfgMagazines", attachmentType, output);
		GetAllAttachments2("CfgAmmo", attachmentType, output);
		GetAllAttachments2("CfgWeapons", attachmentType, output);
	}
	
	static void GetAllAttachments2(string preffix, string attachmentType, ref array<string> output)
	{
		string lowercaseType = attachmentType;
		lowercaseType.ToLower();
		
		string classname;
		array<string> inventoySlots = new array<string>;
		int childCount = GetGame().ConfigGetChildrenCount(preffix);
		for (int i = 0; i < childCount; i++)
		{
			if (GetGame().ConfigGetChildName(preffix, i, classname))
			{
				if (GetGame().ConfigGetInt(preffix + " " + classname + " scope") == 2)
				{
					GetGame().ConfigGetTextArray(preffix + " " + classname + " inventorySlot", inventoySlots);
					if (inventoySlots.Count() > 0)
					{
						foreach (string slotName : inventoySlots)
						{
							slotName.ToLower();
							if (slotName == lowercaseType)
							{
								output.Insert(classname);
								break;
							}
						}

						inventoySlots.Clear();
					}
				}
			}
		}
	}
	
	static string FindItemPreffix(string itemClassname)
	{
		if (GetGame().ConfigIsExisting("CfgVehicles " + itemClassname)) return "CfgVehicles";
		if (GetGame().ConfigIsExisting("CfgMagazines " + itemClassname)) return "CfgMagazines";
		if (GetGame().ConfigIsExisting("CfgAmmo " + itemClassname)) return "CfgAmmo";
		if (GetGame().ConfigIsExisting("CfgWeapons " + itemClassname)) return "CfgWeapons";
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