modded class Hologram
{
	string GetProjectionName(ItemBase item)
	{
		if( !item )
			return "";
		
		string holoName;
		if (GetGame().ConfigGetText("CfgVehicles " + item.GetType() + " hologramName", holoName))
		{
			return holoName;
		}
		
		return super.GetProjectionName(item);
	}
};