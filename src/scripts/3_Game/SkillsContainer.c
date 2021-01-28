class SkillsContainer
{
	protected ref map<int, float> m_values;
	
	void SkillsContainer()
	{

	}
	
	void ~SkillsContainer()
	{
		if (m_values)
		{
			delete m_values;
		}
	}
	
	float GetValue(int id)
	{
		if (m_values.Contains(id))
		{
			return m_values.Get(id);
		}
		
		return 0;
	}
	
	float GetMin(int id)
	{
		if (id == SyberiaSkillType.SYBSKILL_HUMANITY)
		{
			return -100;
		}
		
		return 0;
	}
	
	float GetMax(int id)
	{
		return 100;
	}
	
	float GetTotalScore()
	{
		float result = 0;
		foreach (int id, float val : m_values)
		{
			result = result + val;
		}
		
		return result;
	}
	
	static ref SkillsContainer Create()
	{
		ref SkillsContainer result = new SkillsContainer;
		result.m_values = new map<int, float>;		
		return result;
	}
};