#ifdef NAMALSK_SURVIVAL		
modded class EVRStorm: WeatherEvent
{	
	protected SyberiaObjectiveZone m_A1_SybZone;

    override void ContaminateAthena1Site()
    {
        m_A1_SybZone = SyberiaObjectiveZone.Cast( GetGame().CreateObjectEx( "SyberiaObjectiveZone_Toxic100", Vector( 3777, 145, 8242 ), ECE_NONE ) );
    }
    
    override void EndPhaseServer()
    {
        super.EndPhaseServer();
        
        if (m_A1_SybZone)
            GetGame().ObjectDelete( m_A1_SybZone );
    }
}
#endif
