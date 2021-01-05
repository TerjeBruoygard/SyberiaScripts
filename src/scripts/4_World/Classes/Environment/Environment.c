modded class Environment
{
	override void AddToEnvironmentTemperature(float pTemperature)
	{
		m_HeatSourceTemp = Math.Max(m_HeatSourceTemp, pTemperature);
	}
};