modded class PlayerBase
{	
	// Sleeping
	int m_lastSleepingValue;
	int m_sleepingValue;
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
	float m_overdosedValue;	
	bool m_concussionHit;
	bool m_bloodHemostaticEffect;
	bool m_hematopoiesisEffect;
	bool m_salveEffect;
	
	// MindState
	float m_mindStateValue;
	float m_mindStateLast;
	
	override void Init()
	{
		super.Init();
		
		// Sleeping
		m_lastSleepingValue = SLEEPING_MAX_VALUE;
		m_sleepingValue = SLEEPING_MAX_VALUE;
		m_sleepingLevel = (int)SyberiaSleepingLevel.SYBSL_NONE;
		RegisterNetSyncVariableInt("m_lastSleepingValue", 0, SLEEPING_MAX_VALUE);
		RegisterNetSyncVariableInt("m_sleepingValue", 0, SLEEPING_MAX_VALUE);
		RegisterNetSyncVariableInt("m_sleepingLevel", -4, 2);
		
		// Adv medicine
		m_overdosedValue = 0;
		m_bulletHits = 0;
		m_knifeHits = 0;
		m_hematomaHits = 0;
		m_visceraHit = 0;
		m_concussionHit = false;
		m_painLevel = 0;
		m_painkillerEffect = 0;
		m_stomatchpoisonLevel = 0;
		m_stomatchhealLevel = 0;
		m_sepsis = 0;
		m_zombieVirus = 0;
		m_bulletBandage1 = 0;
		m_bulletBandage2 = 0;
		m_knifeBandage1 = 0;
		m_knifeBandage2 = 0;
		m_bloodHemostaticEffect = false;
		m_hematopoiesisEffect = false;
		m_salveEffect = false;
		m_adrenalinEffect = 0;
		m_influenzaLevel = 0;
		m_antibioticsLevel = 0;
		RegisterNetSyncVariableFloat("m_overdosedValue");
		RegisterNetSyncVariableInt("m_bulletHits", 0, 99);
		RegisterNetSyncVariableInt("m_knifeHits", 0, 99);
		RegisterNetSyncVariableInt("m_hematomaHits", 0, 99);
		RegisterNetSyncVariableInt("m_visceraHit", 0, 99);
		RegisterNetSyncVariableInt("m_painLevel", 0, 3);
		RegisterNetSyncVariableInt("m_painkillerEffect", 0, 3);
		RegisterNetSyncVariableInt("m_sepsis", 0, 4);
		RegisterNetSyncVariableInt("m_zombieVirus", 0, 4);		
		RegisterNetSyncVariableInt("m_bulletBandage1", 0, 99);
		RegisterNetSyncVariableInt("m_bulletBandage2", 0, 99);
		RegisterNetSyncVariableInt("m_knifeBandage1", 0, 99);
		RegisterNetSyncVariableInt("m_knifeBandage2", 0, 99);
		RegisterNetSyncVariableInt("m_adrenalinEffect", 0, 3);
		RegisterNetSyncVariableInt("m_influenzaLevel", 0, 3);
		RegisterNetSyncVariableInt("m_antibioticsLevel", 0, 3);		
		RegisterNetSyncVariableInt("m_stomatchpoisonLevel", 0, 3);
		RegisterNetSyncVariableInt("m_stomatchhealLevel", 0, 3);
		
		RegisterNetSyncVariableBool("m_concussionHit");
		RegisterNetSyncVariableBool("m_bloodHemostaticEffect");
		RegisterNetSyncVariableBool("m_hematopoiesisEffect");
		RegisterNetSyncVariableBool("m_salveEffect");
		
		// Mind state
		m_mindStateValue = MINDSTATE_MAX_VALUE;
		m_mindStateLast = MINDSTATE_MAX_VALUE;
		RegisterNetSyncVariableFloat("m_mindStateValue");
		RegisterNetSyncVariableFloat("m_mindStateLast");
	}
	
	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap)
	{
		super.SetActionsRemoteTarget(InputActionMap);
		AddAction(ActionCheckName, InputActionMap);
		AddAction(ActionSayName, InputActionMap);
	}
	
	override void IncreaseDiseaseCount()
	{
		m_DiseaseCount = 0;
	}
	
	override void DecreaseDiseaseCount()
	{
		m_DiseaseCount = 0;
	}
	
	override bool HasDisease()
	{
		return false;
	}
	
	override bool IsBleeding()
	{
		return super.IsBleeding() || (m_bulletHits > (m_bulletBandage1 + m_bulletBandage2)) || (m_knifeHits > (m_knifeBandage1 + m_knifeBandage2));
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
	
	SyberiaSleepingLevel GetSleepingProcessLevel()
	{
		if (m_sleepingLevel == SyberiaSleepingLevel.SYBSL_ENERGED) return SyberiaSleepingLevel.SYBSL_ENERGED;
		if (m_sleepingLevel == SyberiaSleepingLevel.SYBSL_SICK) return SyberiaSleepingLevel.SYBSL_SICK;
		if (m_sleepingLevel == SyberiaSleepingLevel.SYBSL_COLD) return SyberiaSleepingLevel.SYBSL_COLD;
		if (m_sleepingLevel == SyberiaSleepingLevel.SYBSL_HOT) return SyberiaSleepingLevel.SYBSL_HOT;
		if (m_sleepingLevel == SyberiaSleepingLevel.SYBSL_COMFORT) return SyberiaSleepingLevel.SYBSL_COMFORT;
		if (m_sleepingLevel == SyberiaSleepingLevel.SYBSL_PERFECT) return SyberiaSleepingLevel.SYBSL_PERFECT;
		return SyberiaSleepingLevel.SYBSL_NONE;
	}
	
	int GetCurrentPainLevel()
	{
		if (m_painkillerEffect >= m_painLevel)
		{
			return 0;
		}
		
		return m_painLevel;
	}
	
	bool HasVisibleSepsis()
	{
		return m_sepsis > 1;
	}
	
	bool HasVisibleZVirus()
	{
		return m_zombieVirus > 1;
	}
	
	float GetMindStateValue()
	{
		return m_mindStateValue; 
	}
	
	int GetMindStateTendency()
	{
		float diff = m_mindStateValue - m_mindStateLast;
		if (diff < 0)
		{
			if (diff > -0.1) return -1;
			if (diff > -1.0) return -2;
			return -3;
		}
		else if (diff > 0)
		{
			if (diff < 0.1) return 1;
			if (diff < 1.0) return 2;
			return 3;
		}
		
		return 0;
	}
	
	int GetMindState()
	{
		float value = GetMindStateValue();
		if (value < MINDSTATE_LEVEL_5) return 5;
		if (value < MINDSTATE_LEVEL_4) return 4;
		if (value < MINDSTATE_LEVEL_3) return 3;
		if (value < MINDSTATE_LEVEL_2) return 2;
		return 1; 
	}
	
	bool IsFaceBlocked(bool mouthOnly)
	{
		ref ItemBase itemCheck = GetItemOnSlot("Mask");
		if (itemCheck)
		{
			if (mouthOnly)
			{
				bool skipMaskCondition = false;
				string itemMaskType = itemCheck.GetType();
				if (itemMaskType.IndexOf("Balaclava3Holes_") == 0)
				{
					skipMaskCondition = true;
				}
				
				if (!skipMaskCondition)
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		
		itemCheck = GetItemOnSlot("Headgear");
		if (itemCheck)
		{
			string configPathNoMask = "CfgVehicles " + itemCheck.GetType() +  " noMask";
			if (GetGame().ConfigIsExisting(configPathNoMask))
			{
				if (GetGame().ConfigGetInt(configPathNoMask) == 1)
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	bool IsSicknesOrInjured()
	{
		if (m_bulletHits > 3) return true;
		if (m_knifeHits > 3) return true;
		if (m_visceraHit > 0) return true;
		if (m_painLevel > 1) return true;
		if (m_sepsis > 1) return true;
		if (m_zombieVirus > 1) return true;
		if (m_influenzaLevel > 2) return true;
		if (m_stomatchpoisonLevel > 1) return true;
		if (m_overdosedValue > 1) return true;
		if (m_mindStateValue < MINDSTATE_LEVEL_4) return true;
		if (GetStatWater().Get() < PlayerConstants.SL_WATER_LOW) return true;
		if (GetStatEnergy().Get() < PlayerConstants.SL_ENERGY_LOW) return true;
		return false;
	}
	
	bool IsGhostBody()
	{
		return (GetType().Contains("_Ghost"));
	}
};