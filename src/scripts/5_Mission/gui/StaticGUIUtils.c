modded class StaticGUIUtils
{
	static string FILE_LITERAL = "file: ";
	
	override static string VerifyIconImageString(int imageset_group = IMAGESETGROUP_INVENTORY, string icon_name = "")
	{
        if ( icon_name.IndexOf(FILE_LITERAL) == 0 )
        {
            icon_name = icon_name.Substring(FILE_LITERAL.Length(), icon_name.Length() - FILE_LITERAL.Length());
        }
		else if ( !icon_name.Contains("image:") )
		{
			switch (imageset_group)
			{
				case IMAGESETGROUP_INVENTORY:
					return "set:dayz_inventory image:" + icon_name;
			}
			
		}
		return icon_name;
	}
}