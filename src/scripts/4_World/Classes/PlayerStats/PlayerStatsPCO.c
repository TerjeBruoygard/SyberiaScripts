modded class PlayerStatsPCO_current
{
	override void Init()
	{
		super.Init();
		UpdateStat(EPlayerStats_v115.ENERGY,  		new PlayerStat<float>	(0,		3000,	1500,	"Energy",	EPSstatsFlags.EMPTY) );
		UpdateStat(EPlayerStats_v115.WATER,  		new PlayerStat<float>	(0,		1500,	700,	"Water",	EPSstatsFlags.EMPTY) );
	}
	
	void UpdateStat(int id, PlayerStatBase stat)
	{
		m_PlayerStats.Set(id, stat);
		stat.Init(id);
	}
};