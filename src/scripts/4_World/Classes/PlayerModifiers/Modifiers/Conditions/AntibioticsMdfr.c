modded class AntibioticsMdfr
{
	float m_strength;
	
	override void Init()
	{
		super.Init();
		m_strength = ANTIBIOTICS_STRENGTH;
	}
	
	void SetAntibioticsConfig(float regenTime, float strength)
	{
		m_RegenTime = regenTime;
		m_strength = strength;
	}
	
	override void OnTick(PlayerBase player, float deltaT)
	{
		player.AntibioticsAttack(m_strength * deltaT);
	}
};