modded class Edible_Base
{
	protected bool m_allowCargoManipulation = false;
	protected bool m_alreadySkinned = false;
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		RegisterNetSyncVariableBool("m_allowCargoManipulation");
		RegisterNetSyncVariableBool("m_alreadySkinned");
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionWashFruitsWell);
		AddAction(ActionWashFruitsWater);
	}
	
	override bool CanPutInCargo( EntityAI parent )
	{
		if (CanBeSkinned() && IsSkinned())
		{
			return false;
		}
		
		return super.CanPutInCargo(parent);
	}
	
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if (CanBeSkinned() && !m_allowCargoManipulation)
		{
			return false;
		}
		
		return super.CanReceiveItemIntoCargo(item);
	}
	
	override bool CanLoadItemIntoCargo(EntityAI item)
	{
		if (CanBeSkinned() && !m_allowCargoManipulation)
		{
			return false;
		}
		
		return super.CanLoadItemIntoCargo(item);
	}
	
	override bool CanSwapItemInCargo(EntityAI child_entity, EntityAI new_entity)
	{
		if (CanBeSkinned() && !m_allowCargoManipulation)
		{
			return false;
		}
		
		return super.CanSwapItemInCargo(child_entity, new_entity);
	}
};