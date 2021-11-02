modded class ActionOpenDoors
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (super.ActionCondition(player, target, item))
		{
			House house;
			if ( target.GetObject() && !target.GetObject().IsInherited(BuildingLivespace) && Class.CastTo(house, target.GetObject()) )
			{
				int doorIndex = house.GetDoorIndex(target.GetComponentIndex());
				if (doorIndex != -1)
				{
					BuildingLivespace livespace = BuildingLivespace.FindByVanillaDoorIndex(house, doorIndex);
					if (livespace && !livespace.CanOpenDoor(player, doorIndex))
					{
						return false;
					}
				}
			}
			
			return true;
		}
		
		return false;
	}
};