class EquipItemData
{
	// M4A1; @M4_CarryHandleOptic,weaponButtstockM4,WeaponHandguardM4; &Mag_STANAGCoupled_30Rnd; H0.5; Q1.0
	static void Parse(string data, out string item, ref array<string> attachments, out float health01, out float quantity, out string mag)
	{
		health01 = -1;
		quantity = -1;
		mag = "";
		
		TStringArray parts = new TStringArray;
		data.Split(";", parts);
		
		if (parts.Count() == 0)
		{
			item = data.Trim();
		}
		else
		{
			item = parts.Get(0);
		}
		
		for (int i = 1; i < parts.Count(); i++)
		{
			string part = parts.Get(i).Trim();
			if (part.LengthUtf8() <= 1)
			{
				continue;
			}
			
			string firstLetter = part.SubstringUtf8(0, 1);
			part = part.SubstringUtf8(1, part.LengthUtf8() - 1);			
			if (firstLetter == "@")
			{
				part.Split(",", attachments);
				for(int q = 0; q < attachments.Count(); q++)
				{
					attachments.Set(q, attachments.Get(q).Trim());
				}
			}
			else if (firstLetter == "H")
			{
				health01 = part.ToFloat();
			}
			else if (firstLetter == "Q")
			{
				quantity = part.ToFloat();
			}
			else if (firstLetter == "&")
			{
				mag = part;
			}
		}
	}
};