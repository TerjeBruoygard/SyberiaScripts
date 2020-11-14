modded class InjuryAnimationHandler
{
	override eInjuryHandlerLevels GetInjuryLevel(float health)
	{
		eInjuryHandlerLevels result = super.GetInjuryLevel(health);

		if (m_Player.GetSleepingValue() < SLEEPING_LEVEL_5)
		{
			result = eInjuryHandlerLevels.RUINED;
		}
		else if (m_Player.GetSleepingValue() < SLEEPING_LEVEL_4)
		{
			result = eInjuryHandlerLevels.DAMAGED;
		}
		
		return result;
	}
};