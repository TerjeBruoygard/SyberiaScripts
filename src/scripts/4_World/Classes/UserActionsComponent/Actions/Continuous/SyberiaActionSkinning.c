modded class ActionSkinningCB
{
	override void CreateActionComponent()
	{
		float skinTime = 30;		
		if (m_ActionData.m_Player) {
			float modifier = 1 - m_ActionData.m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_BUTCH_SPEED, 0, 0);
			skinTime = Math.Max(1, skinTime * modifier);
		}
		
		m_ActionData.m_ActionComponent = new CAContinuousTime( skinTime );
	}
};

modded class ActionSkinning
{
	override string GetText()
	{
		return "#syb_skinning_action";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject != NULL )
		{
			if ( targetObject.CanBeSkinned() )
			{
				AnimalBase animal = AnimalBase.Cast(targetObject);
				if (animal && !animal.IsSkinned() && !animal.IsAlive())
				{
					return true;
				}
				
				Edible_Base edibleBase = Edible_Base.Cast(targetObject);
				if (edibleBase && !edibleBase.IsSkinned())
				{
					return true;
				}
			}
		}
		
		return false;
	}
};