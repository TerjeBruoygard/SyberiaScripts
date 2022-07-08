modded class Hologram
{
    override void EvaluateCollision(ItemBase action_item = null)
    {
        super.EvaluateCollision(action_item);

        if (m_Player.IsBuildingModeBlocked())
            SetIsColliding( true );
    }
    
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