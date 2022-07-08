class MedContainerMedium : Container_Base
{
	override bool CanReceiveItemIntoCargo( EntityAI item )
	{
		if (!super.CanReceiveItemIntoCargo(item))
			return false;
		
		return item && item.ConfigGetBool("medicalItem");
	}
	
	override bool CanLoadItemIntoCargo( EntityAI item )
	{
		if (!super.CanLoadItemIntoCargo(item))
			return false;
		
		return item && item.ConfigGetBool("medicalItem");
	}
};