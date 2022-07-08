modded class PlayerBase
{	
	// Sleeping
	int m_lastSleepingValue;
	int m_sleepingValue;
	
	// MindState
	float m_mindStateValue;
	float m_mindStateLast;
	
	// Skills container
	ref SkillsContainer m_skills;
	
	// Current zone
	ref array<ref ZoneImplementation> m_zones = new array<ref ZoneImplementation>;
	
	// Syberia stats (synch context)
	ref SyberiaPlayerStats m_sybstats;
	
	override void Init()
	{
		super.Init();
		
		// Initialize stats
		m_sybstats = new SyberiaPlayerStats;
		m_sybstats.Init();
		
		// Sleeping
		m_lastSleepingValue = GetSyberiaConfig().m_sleepingMaxValue;
		m_sleepingValue = GetSyberiaConfig().m_sleepingMaxValue;
		RegisterNetSyncVariableInt("m_lastSleepingValue", 0, GetSyberiaConfig().m_sleepingMaxValue);
		RegisterNetSyncVariableInt("m_sleepingValue", 0, GetSyberiaConfig().m_sleepingMaxValue);

		// Mind state
		m_mindStateValue = GetSyberiaConfig().m_mindstateMaxValue;
		m_mindStateLast = GetSyberiaConfig().m_mindstateMaxValue;
		RegisterNetSyncVariableFloat("m_mindStateValue");
		RegisterNetSyncVariableFloat("m_mindStateLast");
	}
	
	override void EEInit()
	{
		if (GetGame().IsClient())
		{
			RPCSingleParam(SyberiaERPC.SYBERPC_SYNCH_PLAYER_SYBSTATS_REQUEST, new Param1<int>(0), true);
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		delete m_sybstats;
		m_sybstats = null;
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		if (rpc_type == SyberiaERPC.SYBERPC_SYNCH_PLAYER_SYBSTATS_RESPONSE)
		{
			if (GetGame().IsClient())
			{
				Param1<ref SyberiaPlayerStats> params;
				if (!ctx.Read(params))
					return;
				
				if (m_sybstats != null)
				{
					delete m_sybstats;
				}
				
				m_sybstats = params.param1;
				
				//SybLog("SYBSTATS context synchronized for player " + this);
			}
		}
	}
	
	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		AddAction(ActionSearchTargetInventory, InputActionMap);
		AddAction(ActionTraderInteract, InputActionMap);
		AddAction(ActionOpenHomebook, InputActionMap);
	}
	
	override void SetActionsRemoteTarget(out TInputActionMap InputActionMap)
	{
		super.SetActionsRemoteTarget(InputActionMap);
		AddAction(ActionStethoscopeInspect, InputActionMap);
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
		return super.IsBleeding() || (m_sybstats.m_bulletHits > (m_sybstats.m_bulletBandage1 + m_sybstats.m_bulletBandage2)) || (m_sybstats.m_knifeHits > (m_sybstats.m_knifeBandage1 + m_sybstats.m_knifeBandage2));
	}
	
	override float GetPlayerLoad()
	{
		float result = super.GetPlayerLoad();
		result = result * (1.0 - GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_STAMINA_KG_TO, 0, 0));
		result = result * (1.0 - (GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_STAMINA_MAX, 0, 0) * 0.25));
		return result;
	}
	
	override void OnBleedingSourceRemovedEx(ItemBase item)
	{
		OnBleedingSourceRemoved();
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
		if (value < GetSyberiaConfig().m_sleepingLevel5) return 5;
		if (value < GetSyberiaConfig().m_sleepingLevel4) return 4;
		if (value < GetSyberiaConfig().m_sleepingLevel3) return 3;
		if (value < GetSyberiaConfig().m_sleepingLevel2) return 2;
		return 1; 
	}
	
	SyberiaSleepingLevel GetSleepingProcessLevel()
	{
		if (m_sybstats.m_sleepingLevel == SyberiaSleepingLevel.SYBSL_ENERGED) return SyberiaSleepingLevel.SYBSL_ENERGED;
		if (m_sybstats.m_sleepingLevel == SyberiaSleepingLevel.SYBSL_SICK) return SyberiaSleepingLevel.SYBSL_SICK;
		if (m_sybstats.m_sleepingLevel == SyberiaSleepingLevel.SYBSL_COLD) return SyberiaSleepingLevel.SYBSL_COLD;
		if (m_sybstats.m_sleepingLevel == SyberiaSleepingLevel.SYBSL_HOT) return SyberiaSleepingLevel.SYBSL_HOT;
		if (m_sybstats.m_sleepingLevel == SyberiaSleepingLevel.SYBSL_COMFORT) return SyberiaSleepingLevel.SYBSL_COMFORT;
		if (m_sybstats.m_sleepingLevel == SyberiaSleepingLevel.SYBSL_PERFECT) return SyberiaSleepingLevel.SYBSL_PERFECT;
		return SyberiaSleepingLevel.SYBSL_NONE;
	}
	
	int GetCurrentPainLevel()
	{
		if (m_sybstats.m_painkillerEffect >= m_sybstats.m_painLevel)
		{
			return 0;
		}
		
		return m_sybstats.m_painLevel;
	}
	
	bool HasVisibleSepsis()
	{
		return m_sybstats.m_sepsis > 1;
	}
	
	bool HasVisibleZVirus()
	{
		return m_sybstats.m_zombieVirus > 1;
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
		if (value < GetSyberiaConfig().m_mindstateLevel5) return 5;
		if (value < GetSyberiaConfig().m_mindstateLevel4) return 4;
		if (value < GetSyberiaConfig().m_mindstateLevel3) return 3;
		if (value < GetSyberiaConfig().m_mindstateLevel2) return 2;
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
		if (m_sybstats.m_bulletHits > 3) return true;
		if (m_sybstats.m_knifeHits > 3) return true;
		if (m_sybstats.m_visceraHit > 0) return true;
		if (GetCurrentPainLevel() > 1) return true;
		if (m_sybstats.m_sepsis > 1) return true;
		if (m_sybstats.m_zombieVirus > 2) return true;
		if (m_sybstats.m_influenzaLevel > 2) return true;
		if (m_sybstats.m_stomatchpoisonLevel > 1) return true;
		if (m_sybstats.m_overdosedLevel > 2) return true;
		if (GetRadiationSicknessLevel() > 0) return true;
		if (m_mindStateValue < GetSyberiaConfig().m_mindstateLevel4) return true;
		if (GetStatWater().Get() < PlayerConstants.SL_WATER_LOW) return true;
		if (GetStatEnergy().Get() < PlayerConstants.SL_ENERGY_LOW) return true;
		return false;
	}
	
	bool IsGhostBody()
	{
		return (GetType().Contains("_Ghost"));
	}
	
	bool IsNPC()
	{
		return m_sybstats.m_isNPC;
	}
	
	bool CanOpenSyberiaUI()
	{
		return !IsGhostBody() && !IsUnconscious() && m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE;
	}
	
	int GetSkillValue(int skillId)
	{
		if (IsAlive() && m_skills)
		{
			int result = m_skills.GetSkillValueInt(skillId);
			if (result != -1)
			{
				return result;
			}
		}
		
		return 0;
	}
	
	int GetPerkIntValue(int perkId, int defaultValue = 0)
	{
		if (IsAlive() && m_skills)
		{
			int result = m_skills.GetPerkValue(perkId);
			if (result != -1)
			{
				return result;
			}
		}
		
		return defaultValue;
	}
	
	float GetPerkFloatValue(int perkId, float defaultValue, float additionValue)
	{
		float result = defaultValue;
		int value = GetPerkIntValue(perkId, -1);
		if (value != -1) 
		{
			result = additionValue + ((float)value * 0.01);		
		}
		
		return result;
	}
	
	bool GetPerkBoolValue(int perkId)
	{
		int value = GetPerkIntValue(perkId, -1);
		return value == 1;
	}
	
	bool IsBuildingModeBlocked()
	{
		foreach (ref ZoneImplementation zoneImpl : m_zones)
		{
			if (zoneImpl.m_zone.m_blockBuildingMode == 1)
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool IsInteractionWithPlayersBlocked()
	{
		foreach (ref ZoneImplementation zoneImpl : m_zones)
		{
			if (zoneImpl.m_zone.m_blockInteractionWithPlayers == 1)
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool IsInversedDammageEnabled()
	{
		foreach (ref ZoneImplementation zoneImpl : m_zones)
		{
			if (zoneImpl.m_zone.m_inverseDammage == 1)
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool IsInsidePsiZone()
	{
		foreach (ref ZoneImplementation zoneImpl : m_zones)
		{
			if (zoneImpl.m_zone.m_psi > 0)
			{
				return true;
			}
		}
		
		return false;
	}
	
	void OnZoneChanged(ref array<ref ZoneImplementation> zones)
	{
		if (m_zones != null)
		{
			foreach (ref ZoneImplementation zoneImpl : m_zones)
			{
				delete zoneImpl.m_zone;
				delete zoneImpl;
			}
			
			delete m_zones;
		}
		
		m_zones = zones;
	}
	
	int GetRadiationSicknessLevel()
	{
		return m_sybstats.m_radiationSickness;
	}
	
	int GetRadioprotectionLevel()
	{
		return m_sybstats.m_radioprotectionLevel;
	}
	
	bool HasDisinfectedHands()
	{
		return m_sybstats.m_disinfectedHands;
	}
	
	int GetAntidepresantLevel()
	{
		return m_sybstats.m_antidepresantLevel;
	}
	
	ref SyberiaPlayerStats GetSybStats()
	{
		return m_sybstats;
	}
	
	override void OnUnconsciousUpdate(float pDt, int last_command)
	{
		super.OnUnconsciousUpdate(pDt, last_command);
		
		if( GetGame().IsClient() )
		{
			GetGame().GetMission().GetHud().ShowHudUI( true );
		}
	}
	
	override void OnCommandVehicleStart()
	{
		super.OnCommandVehicleStart();
		TryHideShoulders(true);
	}
	
	override void OnCommandVehicleFinish()
	{
		super.OnCommandVehicleFinish();
		TryHideShoulders(false);
	}
	
	void TryHideShoulders(bool state)
	{
		EntityAI weaponMelee = GetItemOnSlot("Melee");
		EntityAI weaponShoulder = GetItemOnSlot("Shoulder");
		
		if (weaponMelee)
		{
			if (state)
			{
				SetSimpleHiddenSelectionState(DayZPlayer.SIMPLE_SELECTION_MELEE_RIFLE,false);
				SetSimpleHiddenSelectionState(DayZPlayer.SIMPLE_SELECTION_MELEE_MELEE,false);
			}
			else
			{
				UpdateShoulderProxyVisibility(weaponMelee, "Melee");
			}
		}
		
		if (weaponShoulder)
		{
			if (state)
			{
				SetSimpleHiddenSelectionState(SIMPLE_SELECTION_SHOULDER_RIFLE,false);
				SetSimpleHiddenSelectionState(SIMPLE_SELECTION_SHOULDER_MELEE,false);
			}
			else
			{
				UpdateShoulderProxyVisibility(weaponShoulder, "Shoulder");
			}
		}
	}
};