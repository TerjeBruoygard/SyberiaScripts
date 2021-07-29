class GameHelpers
{
	static void GetMedicineItemVisualEffects(string classname, ref array<string> effects)
	{
		float overdosedIncrement = GetGame().ConfigGetFloat( "CfgVehicles " + classname + " overdosedIncrement" );
		if (overdosedIncrement > 3) effects.Insert("#syb_med_killoverdose"); 
			
		int medPainkillerLevel = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medPainkillerLevel" );
		if (medPainkillerLevel > 0) effects.Insert("#syb_med_painkill " + medPainkillerLevel + " #syb_skill_level3"); 
		
		int medStomatchhealLevel = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medStomatchhealLevel" );
		if (medStomatchhealLevel > 0) effects.Insert("#syb_med_stomachheal " + medStomatchhealLevel + " #syb_skill_level3"); 
		
		int medAntibioticLevel = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medAntibioticLevel" );
		if (medAntibioticLevel > 0) effects.Insert("#syb_med_antibiotic " + medAntibioticLevel + " #syb_skill_level3"); 
		
		int medRemoveSepsis = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medRemoveSepsis" );
		if (medRemoveSepsis > 0) effects.Insert("#syb_med_sepsis"); 
		
		int medRemoveZVirus = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medRemoveZVirus" );
		if (medRemoveZVirus > 0) effects.Insert("#syb_med_zvirus"); 
		
		int medConcussionHeal = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medConcussionHeal" );
		if (medConcussionHeal > 0) effects.Insert("#syb_med_concussion"); 
		
		int medBloodHemostatic = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medBloodHemostatic" );
		if (medBloodHemostatic > 0) effects.Insert("#syb_med_hemostatic"); 
		
		int medBloodHematopoiesis = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medBloodHematopoiesis" );
		if (medBloodHematopoiesis > 0) effects.Insert("#syb_med_hemostopoesis"); 
		
		int medHematomaHeal = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medHematomaHeal" );
		if (medHematomaHeal > 0) effects.Insert("#syb_med_hematoma"); 
		
		int medAdrenalinLevel = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medAdrenalinLevel" );
		if (medAdrenalinLevel > 0) effects.Insert("#syb_med_adrenalin " + medAdrenalinLevel + " #syb_skill_level3"); 
		
		int medAntiradLevel = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medRadioprotectionLevel" );
		if (medAntiradLevel > 0) effects.Insert("#syb_med_antirad " + medAntiradLevel + " #syb_skill_level3"); 
		
		int medAntidepLevel = GetGame().ConfigGetInt( "CfgVehicles " + classname + " medAntidepresantLevel" );
		if (medAntidepLevel > 0) effects.Insert("#syb_med_antidepresant " + medAntidepLevel + " #syb_skill_level3"); 
	}
	
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
		return StringIndexOfUtf8(lowercaseText, match) != -1;
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
				if (GetGame().ConfigGetInt(preffix + " " + classname + " scope") != 0)
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
	
	static bool GetCursorPos(out vector result)
	{
	    if ( GetGame().GetPlayer() )
		{
			vector rayStart = GetGame().GetCurrentCameraPosition();
		    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;
		    vector hitPos;
		    vector hitNormal;
		    int hitComponentIndex;
		    if (DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, GetGame().GetPlayer()))
			{
				result = hitPos;
				return true;
			}
		}
		
		result = "0 0 0";
        return false;
	}
	
	static bool IntersectBBox(vector min, vector max, vector point)
	{
		vector trueMin = Vector(Math.Min(min[0], max[0]), Math.Min(min[1], max[1]), Math.Min(min[2], max[2]));
		vector trueMax = Vector(Math.Max(min[0], max[0]), Math.Max(min[1], max[1]), Math.Max(min[2], max[2]));
		return point[0] >= trueMin[0] && point[0] <= trueMax[0] && point[1] >= trueMin[1] && point[1] <= trueMax[1] && point[2] >= trueMin[2] && point[2] <= trueMax[2];
	}
};