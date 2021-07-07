modded class DayZPlayerCameraBase
{
    override void SetNVPostprocess(int NVtype)
	{
		//Print("+++Setting NV type: " + NVtype + " +++");
		switch (NVtype)
		{
			case NVTypes.NONE:
				PPEffects.SetEVValuePP(0);
				SyberiaPPEffects.SetColorizationNV(1.0, 1.0, 1.0);
				SyberiaPPEffects.SetNVParams(1.0, 0.0, 2.35, 2.75); //default values
			break;
			
			case NVTypes.NV_OPTICS_ON:
				PPEffects.SetEVValuePP(7);
				SyberiaPPEffects.SetColorizationNV(0.0, 1.0, 0.0);
				SyberiaPPEffects.SetNVParams(3.0, 2.0, 9.0, 1.0);
			break;
			
			case NVTypes.NV_OPTICS_OFF:
				PPEffects.SetEVValuePP(-10);
				SyberiaPPEffects.SetColorizationNV(0.0, 0.0, 0.0);
				SyberiaPPEffects.SetNVParams(1.0, 0.0, 2.35, 2.75); //default values
			break;
			
			case NVTypes.NV_GOGGLES:
				PPEffects.SetEVValuePP(7);
				SyberiaPPEffects.SetColorizationNV(0.0, 1.0, 0.0);
				SyberiaPPEffects.SetNVParams(2.0, 1.0, 10.0, 1.0);
			break;
		}
		
		if (PlayerBaseClient.Cast(m_pPlayer))
		{
			PlayerBaseClient.Cast(m_pPlayer).SwitchPersonalLight(NVtype < 1); //TODO 
		}
	}
};