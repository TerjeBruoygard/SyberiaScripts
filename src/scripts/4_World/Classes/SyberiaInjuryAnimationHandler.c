modded class InjuryAnimationHandler
{
	override eInjuryHandlerLevels GetInjuryLevel(float health)
	{
		eInjuryHandlerLevels result = super.GetInjuryLevel(health);
		eInjuryHandlerLevels sleepingState = CalculateSleepingState();
		eInjuryHandlerLevels painState = CalculatePainState();
		
		if (InjuryLevelToValue(result) < InjuryLevelToValue(sleepingState))
		{
			result = sleepingState;
		}
		
		if (InjuryLevelToValue(result) < InjuryLevelToValue(painState))
		{
			result = painState;
		}
		
		if (m_Player.m_concussionHit && InjuryLevelToValue(result) < 2)
		{
			result = eInjuryHandlerLevels.DAMAGED;
		}
		
		return result;
	}
	
	private eInjuryHandlerLevels CalculateSleepingState()
	{
		if (m_Player.GetSleepingValue() < SLEEPING_LEVEL_5)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		if (m_Player.GetSleepingValue() < SLEEPING_LEVEL_4)
		{
			return eInjuryHandlerLevels.DAMAGED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private eInjuryHandlerLevels CalculatePainState()
	{
		int painLevel = m_Player.GetCurrentPainLevel();
		if (painLevel == 1)
		{
			return eInjuryHandlerLevels.WORN;
		}
		
		if (painLevel == 2)
		{
			return eInjuryHandlerLevels.BADLY_DAMAGED;
		}
		
		if (painLevel == 3)
		{
			return eInjuryHandlerLevels.RUINED;
		}
		
		return eInjuryHandlerLevels.PRISTINE;
	}
	
	private int InjuryLevelToValue(eInjuryHandlerLevels level)
	{
		if (level == eInjuryHandlerLevels.PRISTINE)
		{
			return 0;
		}
		else if (level == eInjuryHandlerLevels.WORN)
		{
			return 1;
		}
		else if (level == eInjuryHandlerLevels.DAMAGED)
		{
			return 2;
		}
		else if (level == eInjuryHandlerLevels.BADLY_DAMAGED)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
};