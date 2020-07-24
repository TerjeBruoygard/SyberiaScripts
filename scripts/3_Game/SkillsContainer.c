class SkillsContainer
{
	ref array<ref SkillContainer> m_skills;
	ref array<int> m_perks;
	
	void SkillsContainer()
	{

	}
	
	void ~SkillsContainer()
	{
		if (m_skills)
		{
			foreach (ref SkillContainer skill : m_skills)
			{
				delete skill;
			}
			
			delete m_skills;
		}
		
		if (m_perks)
		{
			delete m_perks;
		}
	}
};

class SkillContainer
{
	string m_name;
	float m_value;
	bool m_bounded;
	ref array<bool> m_achivments;
	
	void SkillContainer()
	{
	
	}
	
	void ~SkillContainer()
	{
		if (m_achivments) delete m_achivments;
	}
};

class PerkDescription
{
	string m_name;
	string m_antiperk;
	int m_cost;
	ref map<string, float> m_effects;
	
	void PerkDescription(string name, string antiperk, int cost)
	{
		m_name = name;
		m_antiperk = antiperk;
		m_cost = cost;
		m_effects = new map<string, float>;
	}
	
	void ~PerkDescription()
	{
		delete m_effects;
	}
};

void GetPerkDescriptions(ref array<ref PerkDescription> perks)
{
	ref PerkDescription perk = null;
	
	// resilient
	perk = new PerkDescription("resilient", "illness", 8);
	perk.m_effects.Insert("immunity", 5);
	perks.Insert(perk);	
	// prone to illness
	perk = new PerkDescription("illness", "resilient", -4);
	perk.m_effects.Insert("immunity", -10);
	perks.Insert(perk);
	
	
	
	// athletics
	perk = new PerkDescription("athlete", "smoker", 10);
	perk.m_effects.Insert("athletics", 5);
	perks.Insert(perk);
	// smoker
	perk = new PerkDescription("smoker", "athlete", -5);
	perk.m_effects.Insert("athletics", -10);
	perks.Insert(perk);
	
	
	
	// weightlifter
	perk = new PerkDescription("weightlifter", "weak", 10);
	perk.m_effects.Insert("strength", 5);
	perks.Insert(perk);
	// weak
	perk = new PerkDescription("weak", "weightlifter", -5);
	perk.m_effects.Insert("strength", -10);
	perks.Insert(perk);
	
	
	
	// paramedic
	perk = new PerkDescription("paramedic", "hemophobic", 12);
	perk.m_effects.Insert("medicine", 5);
	perks.Insert(perk);
	// hemophobic
	perk = new PerkDescription("hemophobic", "paramedic", -6);
	perk.m_effects.Insert("medicine", -10);
	perks.Insert(perk);
	

	
	// inconspicuous
	perk = new PerkDescription("inconspicuous", "clumsy", 8);
	perk.m_effects.Insert("stealth", 5);
	perks.Insert(perk);
	// clumsy
	perk = new PerkDescription("clumsy", "inconspicuous", -4);
	perk.m_effects.Insert("stealth", -10);
	perks.Insert(perk);
	
	
	
	// outdoorsman
	perk = new PerkDescription("outdoorsman", "nerd", 12);
	perk.m_effects.Insert("survival", 5);
	perks.Insert(perk);
	// nerd
	perk = new PerkDescription("nerd", "outdoorsman", -6);
	perk.m_effects.Insert("survival", -10);
	perks.Insert(perk);
	
	
		
	// gooddriver
	perk = new PerkDescription("gooddriver", "baddriver", 8);
	perk.m_effects.Insert("driving", 5);
	perks.Insert(perk);
	// baddriver
	perk = new PerkDescription("baddriver", "gooddriver", -4);
	perk.m_effects.Insert("driving", -10);
	perks.Insert(perk);
	
	
	
	// hunter
	perk = new PerkDescription("hunter", "pacifist", 15);
	perk.m_effects.Insert("hunting", 5);
	perk.m_effects.Insert("weapon", 5);
	perks.Insert(perk);
	// pacifist
	perk = new PerkDescription("pacifist", "hunter", -6);
	perk.m_effects.Insert("hunting", -10);
	perk.m_effects.Insert("weapon", -10);
	perks.Insert(perk);
	
	
	
	// engineer
	perk = new PerkDescription("engineer", "stupid", 8);
	perk.m_effects.Insert("mechanics", 5);
	perk.m_effects.Insert("building", 3);
	perks.Insert(perk);
	// stupid
	perk = new PerkDescription("stupid", "engineer", -4);
	perk.m_effects.Insert("mechanics", -10);
	perk.m_effects.Insert("building", -5);
	perks.Insert(perk);

	
		
		
	// radio amateur
	perk = new PerkDescription("radioamateur", "", 8);
	perk.m_effects.Insert("electronics", 5);
	perks.Insert(perk);
	
	// builder
	perk = new PerkDescription("builder", "", 6);
	perk.m_effects.Insert("building", 5);
	perks.Insert(perk);
	
	// farmer
	perk = new PerkDescription("farmer", "", 4);
	perk.m_effects.Insert("farming", 5);
	perks.Insert(perk);
	
	// naturalist
	perk = new PerkDescription("naturalist", "", 2);
	perk.m_effects.Insert("herbalism", 5);
	perks.Insert(perk);
	

	
	
	// myopic
	perk = new PerkDescription("myopic", "", -10);
	perks.Insert(perk);
	
	// hypochondriac
	perk = new PerkDescription("hypochondriac", "", -8);
	perks.Insert(perk);
}

int GetPerkIdByName(ref array<ref PerkDescription> perks, string name)
{
	foreach (ref PerkDescription perk : perks)
	{
		if (perk.m_name == name)
		{
			return perks.Find(perk);
		}
	}
	
	return -1;
}