class ZoneDefinition
{
	int m_id;
	vector m_position;
	float m_radius;
	float m_height;
	string m_enterMessage;
	string m_leaveMessage;
	float m_leaveTime;
	int m_godMode;
	int m_inverseDammage;
	int m_blockBuildingMode;
	int m_blockInteractionWithPlayers;
	float m_radiation;
    float m_psi;
    float m_gas;
	float m_spawnChance;
};

class ZoneImplementation
{
	ref ZoneDefinition m_zone;
	float m_zoneLeaveTimer;
	
	void ZoneImplementation(ref ZoneDefinition zone)
	{
		m_zone = zone;
		m_zoneLeaveTimer = 0;
	}
};