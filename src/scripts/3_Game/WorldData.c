modded class WorldData
{
	float m_sybTimer;
	float m_airDayTemperatureMin;
    float m_airDayTemperatureMax;
    float m_airNightTemperatureMin;
    float m_airNightTemperatureMax;
	float m_airCurrentTemperature;
	
	override void Init()
	{
		super.Init();
		
		string worldName;
		GetGame().GetWorldName(worldName);
		m_airDayTemperatureMin = GetGame().ConfigGetFloat("CfgWorlds " + worldName + " airDayTemperatureMin");
		m_airDayTemperatureMax = GetGame().ConfigGetFloat("CfgWorlds " + worldName + " airDayTemperatureMax");
		m_airNightTemperatureMin = GetGame().ConfigGetFloat("CfgWorlds " + worldName + " airNightTemperatureMin");
		m_airNightTemperatureMax = GetGame().ConfigGetFloat("CfgWorlds " + worldName + " airNightTemperatureMax");
		m_airCurrentTemperature = m_airDayTemperatureMin;
		m_sybTimer = 0;
		
		if (IsDayTime())
		{
			m_airCurrentTemperature = Math.Lerp(m_airDayTemperatureMin, m_airDayTemperatureMax, Math.RandomFloat01());
		}
		else
		{
			m_airCurrentTemperature = Math.Lerp(m_airNightTemperatureMin, m_airNightTemperatureMax, Math.RandomFloat01());
		}
	}
	
	bool IsDayTime()
	{
		int year, month, day, hour, minute;
		GetGame().GetWorld().GetDate( year, month, day, hour, minute );
		float curTime = hour + ( minute / 60.0 );
		float monthday = month + ( day / 32.0 );
		float approxSunrise = GetApproxSunriseTime( monthday );
		float approxSunset = GetApproxSunsetTime( monthday );
		return ( curTime >= approxSunrise ) && ( curTime <= approxSunset );
	}
	
	override void UpdateBaseEnvTemperature(float timeslice)
	{
		super.UpdateBaseEnvTemperature(timeslice);
		
		m_sybTimer = m_sybTimer + timeslice;
		if (m_sybTimer > 30)
		{
			m_sybTimer = 0;
			
			float randShift = Math.RandomFloat01() - 0.5;
			if ( IsDayTime() ) {
				// day
				m_airCurrentTemperature = Math.Clamp(m_airCurrentTemperature + randShift, m_airDayTemperatureMin, m_airDayTemperatureMax);
			}
			else {
				// night
				m_airCurrentTemperature = Math.Clamp(m_airCurrentTemperature + randShift, m_airNightTemperatureMin, m_airNightTemperatureMax);
			}
		}
	}
	
	override float GetBaseEnvTemperature()
	{
		return m_airCurrentTemperature;
	}
};