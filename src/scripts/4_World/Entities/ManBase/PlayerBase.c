modded class PlayerBase
{	
	// Sleeping
	private float m_sleepingDecTimer;
	private int m_lastSleepingValue;
	private float m_sleepingBoostTimer;
	private int m_sleepingBoostValue;
	protected int m_sleepingValue;
	
	// Adv medicine
	int m_bulletHits;
	int m_knifeHits;
	int m_hematomaHits;
	int m_visceraHit;
	bool m_concussionHit;
	int m_painLevel;
	float m_painEffectDurationLast;
	float m_painEffectDurationCur;
	int m_painkillerEffect;
	
	override void Init()
	{
		super.Init();
		
		// Sleeping
		m_sleepingDecTimer = 0;
		m_sleepingBoostTimer = 0;
		m_sleepingBoostValue = 0;
		m_lastSleepingValue = SLEEPING_MAX_VALUE;
		m_sleepingValue = SLEEPING_MAX_VALUE;
		RegisterNetSyncVariableInt("m_lastSleepingValue", 0, SLEEPING_MAX_VALUE);
		RegisterNetSyncVariableInt("m_sleepingValue", 0, SLEEPING_MAX_VALUE);
		RegisterNetSyncVariableFloat("m_sleepingBoostTimer");
		RegisterNetSyncVariableInt("m_sleepingBoostValue");
		
		// Adv medicine
		m_bulletHits = 0;
		m_knifeHits = 0;
		m_hematomaHits = 0;
		m_visceraHit = 0;
		m_concussionHit = false;
		m_painLevel = 0;
		m_painEffectDurationLast = 0;
		m_painEffectDurationCur = 0;
		m_painkillerEffect = 0;
		RegisterNetSyncVariableInt("m_bulletHits", 0, 99);
		RegisterNetSyncVariableInt("m_knifeHits", 0, 99);
		RegisterNetSyncVariableInt("m_hematomaHits", 0, 99);
		RegisterNetSyncVariableInt("m_visceraHit", 0, 99);
		RegisterNetSyncVariableBool("m_concussionHit");
		RegisterNetSyncVariableInt("m_painLevel", 0, 3);
		RegisterNetSyncVariableInt("m_painkillerEffect", 0, 3);
	}
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		
		m_sleepingDecTimer = m_sleepingDecTimer + deltaTime;
		while (m_sleepingDecTimer > 1.0)
		{
			m_sleepingDecTimer = m_sleepingDecTimer - 1.0;
			OnTickSleeping();
		}
	}
	
	private void OnTickSleeping()
	{
		int sleepingDiff = 0;		
		sleepingDiff = sleepingDiff - SLEEPING_DEC_PER_SEC;
		
		if (m_sleepingBoostTimer > 0)
		{
			m_sleepingBoostTimer = m_sleepingBoostTimer - 1;
			sleepingDiff = sleepingDiff + m_sleepingBoostValue;
		}
		else if (m_EmoteManager && m_EmoteManager.IsPlayerSleeping())
		{
			sleepingDiff = sleepingDiff + SLEEPING_INC_PER_SLEEPING_SEC;
		}
		
		m_lastSleepingValue = m_sleepingValue;
		m_sleepingValue = m_sleepingValue + sleepingDiff;
		
		if (m_sleepingValue <= 0) 
		{
			if (SLEEPING_UNCONSION_ENABLED)
			{
				m_UnconsciousEndTime = -60;
				SetHealth("","Shock",0);
				if (GetGame().IsServer() || GetGame().IsMultiplayer())
				{
					SetSleepingBoost(SLEEPING_INC_PER_UNCONSION_BOOST_TIME, SLEEPING_INC_PER_UNCONSION_BOOST_VALUE);
				}
			}
			
			m_sleepingValue = 0;
		}
		
		if (m_sleepingValue > SLEEPING_MAX_VALUE)
		{
			m_sleepingValue = SLEEPING_MAX_VALUE;
		}
	}
	
	void SetSleepingBoost(float time, int value)
	{
		m_sleepingBoostTimer = time;
		m_sleepingBoostValue = value;
		SetSynchDirty();
	}
	
	void AddSleepingBoost(float time, int value)
	{
		if (value == m_sleepingBoostValue)
		{
			m_sleepingBoostTimer = m_sleepingBoostTimer + time;
			SetSynchDirty();
		}
		else
		{
			SetSleepingBoost(time, value);
		}
	}
	
	int GetSleepingValue()
	{
		return m_sleepingValue; 
	}
	
	int GetSleepingTendency()
	{
		int diff = m_sleepingValue - m_lastSleepingValue;
		if (diff < 0)
		{
			if (diff > -3) return -1;
			if (diff > -10) return -2;
			return -3;
		}
		else if (diff > 0)
		{
			if (diff < 3) return 1;
			if (diff < 10) return 2;
			return 3;
		}
		
		return 0;
	}
	
	int GetSleepingState()
	{
		int value = GetSleepingValue();
		if (value < SLEEPING_LEVEL_5) return 5;
		if (value < SLEEPING_LEVEL_4) return 4;
		if (value < SLEEPING_LEVEL_3) return 3;
		if (value < SLEEPING_LEVEL_2) return 2;
		return 1; 
	}
	
	int GetCurrentPainLevel()
	{
		if (m_painkillerEffect >= m_painLevel)
		{
			return 0;
		}
		
		return m_painLevel;
	}
	
	int GetCurrentMedicineInUse()
	{
		int counter = 0;
		if (m_painkillerEffect > 0)
		{
			counter = counter + 1;
		}
		
		return counter;
	}
	
	bool IsGhostBody()
	{
		return (GetType().Contains("_Ghost"));
	}
};