modded class ActionSkinningCB
{
	override void CreateActionComponent()
	{
		float skinTime = 30;		
		if (m_ActionData.m_Player) {
			int divider = Math.Max(1, m_ActionData.m_Player.GetSkillValue(SyberiaSkillType.SYBSKILL_HUNTING) / 10);
			skinTime = skinTime / divider;
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
		bool result = super.ActionCondition(player, target, item);
		if (result)
		{
			AnimalBase animal = AnimalBase.Cast(target.GetObject());
			if (animal.IsSkinned())
			{
				return false;
			}
		}
		
		return result;
	}
};