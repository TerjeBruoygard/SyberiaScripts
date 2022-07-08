class SyberiaPlayerStats
{
	// Sleeping
	int m_sleepingLevel;
	
	// Adv medicine
	int m_bulletHits;
	int m_knifeHits;
	int m_hematomaHits;
	int m_visceraHit;
	int m_painLevel;
	int m_painkillerEffect;
	int m_sepsis;
	int m_zombieVirus;
	int m_bulletBandage1;
	int m_bulletBandage2;
	int m_knifeBandage1;
	int m_knifeBandage2;
	int m_adrenalinEffect;
	int m_influenzaLevel;
	int m_antibioticsLevel;
	int m_stomatchpoisonLevel;
	int m_stomatchhealLevel;
	int m_radiationSickness;
	int m_radioprotectionLevel;
	int m_antidepresantLevel;
	int m_overdosedLevel;	
	bool m_concussionHit;
	bool m_bloodHemostaticEffect;
	bool m_hematopoiesisEffect;
	bool m_salveEffect;
	bool m_disinfectedHands;
	
	// Skills
	float m_skillsStealthStepVolume;
	float m_skillsStealthVoiceVolume;
	float m_skillsStealthWeaponsVolume;
	float m_skillsStealthEquipmentVolume;
	
	// Zones
	bool m_isPveIntruder;
	
	// Misc
	bool m_isNPC;
	
	void Init()
	{
		// Sleeping
		m_sleepingLevel = (int)SyberiaSleepingLevel.SYBSL_NONE;
		
		// Adv medicine
		m_overdosedLevel = 0;
		m_bulletHits = 0;
		m_knifeHits = 0;
		m_hematomaHits = 0;
		m_visceraHit = 0;
		m_concussionHit = false;
		m_painLevel = 0;
		m_painkillerEffect = 0;
		m_stomatchpoisonLevel = 0;
		m_stomatchhealLevel = 0;
		m_radiationSickness = 0;
		m_radioprotectionLevel = 0;
		m_antidepresantLevel = 0;
		m_sepsis = 0;
		m_zombieVirus = 0;
		m_bulletBandage1 = 0;
		m_bulletBandage2 = 0;
		m_knifeBandage1 = 0;
		m_knifeBandage2 = 0;
		m_bloodHemostaticEffect = false;
		m_hematopoiesisEffect = false;
		m_salveEffect = false;
		m_disinfectedHands = false;
		m_adrenalinEffect = 0;
		m_influenzaLevel = 0;
		m_antibioticsLevel = 0;
		
		// Skills
		m_skillsStealthStepVolume = 1;
		m_skillsStealthVoiceVolume = 1;
		m_skillsStealthWeaponsVolume = 1;
		m_skillsStealthEquipmentVolume = 1;
		
		// Zones
		m_isPveIntruder = false;
		
		// Misc
		m_isNPC = false;
	}
};