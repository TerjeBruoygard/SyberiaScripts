modded class HealthNotfr
{
    private const float 	DEC_TRESHOLD_LOW 			= 0;
	private const float 	DEC_TRESHOLD_MED 			= -0.2;
	private const float 	DEC_TRESHOLD_HIGH			= -1.0;
	private const float 	INC_TRESHOLD_LOW 			= 0;
	private const float 	INC_TRESHOLD_MED 			= 0.2;
	private const float 	INC_TRESHOLD_HIGH			= 1.0;
    
    override void DisplayTendency(float delta)
	{
		int tendency = CalculateTendency(delta, INC_TRESHOLD_LOW, INC_TRESHOLD_MED, INC_TRESHOLD_HIGH, DEC_TRESHOLD_LOW, DEC_TRESHOLD_MED, DEC_TRESHOLD_HIGH);
		EStatLevels health_level = m_Player.GetStatLevelHealth();
		DisplayElementTendency dis_elm = DisplayElementTendency.Cast(GetVirtualHud().GetElement(eDisplayElements.DELM_TDCY_HEALTH));
		
		if( dis_elm )
		{
			dis_elm.SetSeriousnessLevel(health_level);
			dis_elm.SetTendency(tendency);
		}
	}
};