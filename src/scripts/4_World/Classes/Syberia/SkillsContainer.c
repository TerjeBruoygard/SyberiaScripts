class SkillsContainer
{
	protected ref map<int, float> m_skills;
	protected ref map<int, int> m_perks;
	bool m_dirty = true;
	
	void SkillsContainer()
	{

	}
	
	void ~SkillsContainer()
	{
		if (m_skills)
		{
			delete m_skills;
		}
		
		if (m_perks)
		{
			delete m_perks;
		}
	}
	
	float GetSkillValue(int id)
	{
		if (m_skills.Contains(id))
		{
			return m_skills.Get(id);
		}
		
		return 0;
	}
	
	int GetSkillValueInt(int id)
	{
		return (int)GetSkillValue(id);
	}
	
	void SetSkillValue(int id, float value)
	{
		value = Math.Clamp(value, GetSkillMin(id), GetSkillMax(id));
		
		if (m_skills.Contains(id))
		{
			if (m_skills.Get(id) != value)
			{
				m_skills.Set(id, value);
				m_dirty = true;
			}
		}
		else
		{
			m_skills.Insert(id, value);
			m_dirty = true;
		}
	}
	
	void AddSkillValue(int id, float value)
	{
		SetSkillValue(id, GetSkillValue(id) + value);
	}
	
	float GetSkillMin(int id)
	{		
		return 0;
	}
	
	float GetSkillMax(int id)
	{
		return 100;
	}
	
	float GetSkillLevelSize(int id)
	{
		return SkillsContainer.CalculateSkillLevelSize(GetSkillValueInt(id));
	}
	
	float GetSkillLevelValue(int id)
	{
		float val = GetSkillValue(id);
		float dif = val - Math.Floor(val);
		return GetSkillLevelSize(id) * dif;
	}
	
	bool HasPerk(int perkId)
	{
		return m_perks.Contains(perkId);
	}
	
	int GetPerkLevel(int perkId)
	{
		if (HasPerk(perkId))
		{
			return m_perks.Get(perkId);
		}
		
		return -1;
	}
	
	int GetPerkValue(int perkId)
	{
		int perkLevel = GetPerkLevel(perkId);
		ref PerkInfo perk = PerksCollection.m_Instance.GetPerk(perkId);
		if (perk && perk.HasUnlockLevel(perkLevel))
		{
			return perk.GetUnlockLevelValue(perkLevel);
		}
		
		return -1;
	}
	
	void SetPerk(int perkId, int perkLevel)
	{
		if (HasPerk(perkId))
		{
			m_perks.Set(perkId, perkLevel);
		}
		else
		{
			m_perks.Insert(perkId, perkLevel);
		}
		
		m_dirty = true;
	}
	
	float GetTotalScore()
	{
		float result = 0;
		foreach (int id, float val : m_skills)
		{
			result = result + val;
		}
		
		return result;
	}
	
	int GetSkillLevelVisualStatus(int skillId, int level)
	{
		if ( GetSkillValueInt(skillId) < level )
			return -1;
		
		array<ref PerkInfo> m_perksOnThisLevel = new array<ref PerkInfo>;
		PerksCollection.m_Instance.GetFilteredPerks(skillId, level, m_perksOnThisLevel);
		foreach (ref PerkInfo checkedPerk : m_perksOnThisLevel)
		{
			if (GetPerkLevel(checkedPerk.GetId()) >= level)
			{
				return 1;
			}
		}
		
		return 0;
	}
	
	int GetPerkStatus(int perkId, int level)
	{
		ref PerkInfo perk = PerksCollection.m_Instance.GetPerk(perkId);
		if (!perk || !perk.HasUnlockLevel(level)) 
			return -4;
		
		int skillId = perk.GetSkillId();
		array<ref PerkInfo> m_perksOnThisLevel = new array<ref PerkInfo>;
		PerksCollection.m_Instance.GetFilteredPerks(skillId, level, m_perksOnThisLevel);
		foreach (ref PerkInfo checkedPerk : m_perksOnThisLevel)
		{
			if (checkedPerk.GetId() == perkId)
				continue;
			
			if (GetPerkLevel(checkedPerk.GetId()) >= level)
				return -2;
		}
		
		if (level > GetSkillValueInt(skillId)) 
			return -1;
		
		int currentPerkLevel = GetPerkLevel(perkId);
		if (currentPerkLevel >= level)
			return 1;
		
		int prevUnlockLevel = perk.GetPrevUnlockLevel(level);		
		if (prevUnlockLevel != -1 && currentPerkLevel != prevUnlockLevel)
			return -3;
						
		return 0;
	}
	
	bool CanActivatePerk(int perkId, int level)
	{		
		return GetPerkStatus(perkId, level) == 0;
	}
	
	static float CalculateSkillLevelSize(int levelValue)
	{
		int skillLevelSize = GetSyberiaOptions().m_client.m_skillLevelSize;
		int skillLevelModifier = GetSyberiaOptions().m_client.m_skillLevelModifier;
		if (levelValue >= 0)
		{
			return skillLevelSize + (levelValue * skillLevelModifier);
		}
		else
		{
			return (skillLevelSize * -1) + (levelValue * skillLevelModifier);
		}
	}
	
	static ref SkillsContainer Create()
	{
		ref SkillsContainer result = new SkillsContainer;
		result.m_skills = new map<int, float>;
		result.m_perks = new map<int, int>;		
		return result;
	}
};