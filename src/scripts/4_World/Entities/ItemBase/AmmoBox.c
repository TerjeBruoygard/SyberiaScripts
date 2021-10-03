modded class AmmoBox
{
	override bool CanReceiveItemIntoCargo( EntityAI item )
	{
		if (!super.CanReceiveItemIntoCargo(item))
			return false;
		
		return item && (item.IsInherited(Ammunition_Base) || item.IsInherited(Box_Base));
	}
	
	override bool CanLoadItemIntoCargo( EntityAI item )
	{
		if (!super.CanLoadItemIntoCargo(item))
			return false;
		
		return item && (item.IsInherited(Ammunition_Base) || item.IsInherited(Box_Base));
	}
};