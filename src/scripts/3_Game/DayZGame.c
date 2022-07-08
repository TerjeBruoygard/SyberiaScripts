modded class LoginTimeBase
{
	override Widget Init()
	{
		Widget result = super.Init();
		if (m_btnLeave)
		{		
			m_btnLeave.Show(false);
		}
		return result;
	}
	
	override void Leave()
	{
		// DO NOTHING
	}
	
	override void Update(float timeslice)
	{
		if (IsRespawn())
		{
			return;
		}
		
		super.Update(timeslice);
	}
};

modded class DayZGame
{
	override void OnRespawnEvent(int time)
	{
		PPERequesterBank.GetRequester(PPERequester_DeathDarkening).Start(new Param1<float>(1.0));
	}
};