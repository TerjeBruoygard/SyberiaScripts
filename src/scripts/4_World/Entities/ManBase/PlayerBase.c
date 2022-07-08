modded class PlayerBase
{	
	private float m_sleepingDecTimer;
	private int m_lastSleepingValue;
	private float m_sleepingBoostTimer;
	private int m_sleepingBoostValue;
	protected int m_sleepingValue;
	
	override void Init()
	{
		super.Init();
		m_sleepingDecTimer = 0;
		m_sleepingBoostTimer = 0;
		m_sleepingBoostValue = 0;
		m_lastSleepingValue = SLEEPING_MAX_VALUE;
		m_sleepingValue = SLEEPING_MAX_VALUE;
		
		RegisterNetSyncVariableInt("m_lastSleepingValue", 0, SLEEPING_MAX_VALUE);
		RegisterNetSyncVariableInt("m_sleepingValue", 0, SLEEPING_MAX_VALUE);
		RegisterNetSyncVariableFloat("m_sleepingBoostTimer");
		RegisterNetSyncVariableInt("m_sleepingBoostValue");
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
				SetSleepingBoost(SLEEPING_INC_PER_UNCONSION_BOOST_TIME, SLEEPING_INC_PER_UNCONSION_BOOST_VALUE);
			}
			
			m_sleepingValue = 0;
		}
		
		if (m_sleepingValue > SLEEPING_MAX_VALUE)
		{
			m_sleepingValue = SLEEPING_MAX_VALUE;
		}
	}
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{
		super.OnStoreSave(ctx);
		ctx.Write( m_sleepingValue );
		ctx.Write( m_sleepingBoostTimer );
		ctx.Write( m_sleepingBoostValue );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;
		
		if(!ctx.Read( m_sleepingValue ))
			return false;
		
		if(!ctx.Read( m_sleepingBoostTimer ))
			return false;
		
		if(!ctx.Read( m_sleepingBoostValue ))
			return false;
		
		
		return true;
	}
	
	override bool Consume(ItemBase source, float amount, EConsumeType consume_type )
	{
		bool result = super.Consume(source, amount, consume_type);
				
		if (result)
		{
			SodaCan_EnergyDrink edible_item = SodaCan_EnergyDrink.Cast(source);
			if (edible_item)
			{
				AddSleepingBoost(amount, 10);
			}
		}
		
		return result;
	}
	
	void SetSleepingBoost(float time, int value)
	{
		m_sleepingBoostTimer = time;
		m_sleepingBoostValue = value;
	}
	
	void AddSleepingBoost(float time, int value)
	{
		if (value == m_sleepingBoostValue)
		{
			m_sleepingBoostTimer = m_sleepingBoostTimer + time;
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
	
	bool IsGhostBody()
	{
		return (GetType().Contains("_Ghost"));
	}
}