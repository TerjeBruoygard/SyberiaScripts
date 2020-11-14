class RpcCreateNewCharContainer
{
	string m_name;
	bool m_isMale;
	int m_faceId;
	ref array<int> m_perks;
	
	void ~RpcCreateNewCharContainer()
	{
		if (m_perks) delete m_perks;
	}
};