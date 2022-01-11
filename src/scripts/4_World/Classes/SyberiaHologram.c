modded class Hologram
{
    override void EvaluateCollision(ItemBase action_item = null)
    {
        super.EvaluateCollision(action_item);

        if (m_Player.IsBuildingModeBlocked())
            SetIsColliding( true );
    }
	
	override string ProjectionBasedOnParent()
    {
		string holoName;
        ItemBase item = ItemBase.Cast(m_Player.GetHumanInventory().GetEntityInHands());
		if (item && GetGame().ConfigGetText("CfgVehicles " + item.GetType() + " hologramName", holoName))
		{
			return holoName;
		} 
		
		return super.ProjectionBasedOnParent();
	}
};