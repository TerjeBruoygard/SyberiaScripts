class CharacterMetadata
{
	void CharacterMetadata(string classname, string facelogo)
	{
		m_classname = classname;
		m_facelogo = facelogo;
	}
	
	string m_classname;
	string m_facelogo;
	
	static bool ValidateCharacterNameFull(string fullname)
	{
		int length = fullname.LengthUtf8();
		if (length < 5 || length > 33) return false;
		
		TStringArray parts = new TStringArray;
		fullname.Split(" ", parts);
		
		if (parts.Count() != 2) return false;
		
		return ValidateCharacterNamePart(parts.Get(0)) && ValidateCharacterNamePart(parts.Get(1));
	}
	
	static bool ValidateCharacterNamePart(string name)
	{		
		int length = name.LengthUtf8();
		if (length < 2 || length > 16) return false;

		for (int i = 0; i < length; i++)
		{
			string letter = name.SubstringUtf8(i, 1);
			letter.ToLower();

			if (GetSyberiaConfig().m_allowedLettersInName.Find(letter) == -1)
			{
				return false;
			}
		}
		
		return true;
	}
	
	static string FormatNamePart(string name)
	{
		if (name.LengthUtf8() < 2) return name;
		
		string trimedName = name.Trim();
		string result1 = trimedName.SubstringUtf8(0, 1);
		string result2 = trimedName.SubstringUtf8(1, trimedName.LengthUtf8() - 1);
		result1.ToUpper();
		result2.ToLower();
		return result1 + result2;
	}
};