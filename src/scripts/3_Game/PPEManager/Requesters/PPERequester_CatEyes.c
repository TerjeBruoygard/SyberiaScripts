class PPERequester_CatEyes extends PPERequester_GameplayBase
{
	static const int L_0_CAT_EYES = 250;
	
	void SetValue(float value)
	{
		SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,value,PPERequester_CatEyes.L_0_CAT_EYES,PPOperators.HIGHEST);
	}
	
	override protected void OnStart(Param par = null)
	{
		super.OnStart();
	}
	
	//other values reset automatically on stop
	override protected void OnStop(Param par = null)
	{
		super.OnStop(par);
	}
}