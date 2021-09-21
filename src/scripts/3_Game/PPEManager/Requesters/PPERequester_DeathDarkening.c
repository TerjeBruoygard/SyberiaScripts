modded class PPERequester_DeathDarkening
{
    override protected void OnStart(Param par = null)
	{
		super.OnStart(par);
		
		m_Value = Param1<float>.Cast(par).param1;
		m_Value = Easing.EaseInCubic(m_Value);
		m_Value = Math.Lerp(0,-1000,m_Value);
		SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,m_Value,PPEExposureNative.L_0_DEATH,PPOperators.SET);
	}
};