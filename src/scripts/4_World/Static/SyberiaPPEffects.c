class SyberiaPPEffects
{
	static Material m_MatChroma;
	static EffectSound m_hearthbitSound;
	static float m_matChromaOffsetLast;
	static float m_camShake;
	
	static int m_blurEffect;
	
	static float m_OverdosedOffset;
	static float m_OverdosedValue;
	
	static float m_PainValue;
	static float m_PainOffset;
	
	static float m_ConcussionValue;
	static float m_ConcussionOffset;
	
	static int m_VignetteSleeping;
	static float m_SleepingCurrent;
	static float m_SleepingValue;
	static float m_SleepingOffset;
	
	static void Init()
	{
		// Fix game options
		GameOptions ggOptions = new GameOptions();
		ListOptionsAccess ppQualityOption = ListOptionsAccess.Cast( ggOptions.GetOptionByType( AT_POSTPROCESS_EFFECTS ) );
		if (ppQualityOption.GetIndex() == 0)
		{
			SybLog("CHANGE PP EFFECT OPTIONS FROM 0 TO 1");
			ppQualityOption.SetIndex(1);
			ggOptions.Apply();
		}
		
		m_camShake = 0;
		m_matChromaOffsetLast = 0;
		m_MatChroma = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");
		m_blurEffect = PPEffects.RegisterBlurEffect();
		
		m_OverdosedOffset = 0;
		m_OverdosedValue = 0;
				
		m_PainValue = 0;
		m_PainOffset = 0;
		
		m_ConcussionValue = 0;
		m_ConcussionOffset = 0;
		
		m_SleepingValue = 0;
		m_SleepingOffset = 0;
		m_SleepingCurrent = 0;
		m_VignetteSleeping = PPEffects.RegisterVignetteEffect();
	}
	
	static void Update(float dt)
	{
		float matChromaOffset = 0;
		float blurEffect = 0;
		float sinusVal = 0;
		
		if (m_OverdosedValue > 0)
		{
			m_OverdosedOffset = m_OverdosedOffset + (dt * 6);
			if (m_OverdosedOffset >= 12)
			{
				m_OverdosedOffset = 0;
				GetGame().GetPlayer().PlaySoundSet(m_hearthbitSound, "hearthbit_SoundSet", 0, 0);
			}
			
			sinusVal = Math.Clamp(m_OverdosedOffset, 0, 12);
			if (sinusVal >= 2) sinusVal = Math.Cos((sinusVal - 2) * Math.PI_HALF * 0.1);
			else sinusVal = Math.AbsFloat( Math.Sin( sinusVal * Math.PI * 0.75 ) );
			
			matChromaOffset = matChromaOffset + (sinusVal * m_OverdosedValue * 0.25);
			blurEffect = blurEffect + (m_OverdosedValue + (sinusVal * 0.1));
		}
		
		if (m_PainValue > 0)
		{
			m_PainOffset = m_PainOffset + (dt * 0.5);
			if (m_PainOffset >= Math.PI2) m_PainOffset = 0;
			
			sinusVal = Math.Clamp( Math.Sin(m_PainOffset), 0, 1);
			if (m_PainValue >= 0.2 && sinusVal >= 0.9 && m_camShake <= 0)
			{
				m_camShake = 1;
			}
			
			sinusVal = ((m_PainValue - 0.1) + (sinusVal * 0.05));
			sinusVal = Math.Clamp(sinusVal, 0, 1);
			
			matChromaOffset = matChromaOffset + sinusVal;
			
			if (m_PainValue >= 0.3)
			{
				blurEffect = blurEffect + sinusVal;
			}
		}
		
		if (m_ConcussionValue > 0)
		{
			m_ConcussionOffset = m_ConcussionOffset + (dt * 0.1);
			if (m_ConcussionOffset >= Math.PI2) m_ConcussionOffset = 0;
			sinusVal = Math.Clamp( Math.Sin(m_ConcussionOffset) * 0.05, 0, 0.05) ;
			blurEffect = blurEffect + (m_ConcussionValue + sinusVal);
		}
		
		matChromaOffset = Math.Clamp(matChromaOffset, 0, 1);
		blurEffect = Math.Clamp(blurEffect, 0, 1);
		
		if (m_matChromaOffsetLast != matChromaOffset)
		{
			m_matChromaOffsetLast = matChromaOffset;
			m_MatChroma.SetParam("PowerX", matChromaOffset);
			m_MatChroma.SetParam("PowerY", matChromaOffset);
		}
		
		if (m_camShake == 1)
		{
			if (GetGame() && GetGame().GetPlayer())
			{
				GetGame().GetPlayer().GetCurrentCamera().SpawnCameraShake();
			}
		}
		if (m_camShake > 0)
		{
			m_camShake = m_camShake - dt;
		}
		
		PPEffects.SetBlurValue(m_blurEffect, blurEffect);
		PPEffects.UpdateBlur();
		
		m_SleepingCurrent = m_SleepingCurrent + ((m_SleepingValue - m_SleepingCurrent) * dt * 0.1);	
		m_SleepingCurrent = Math.Clamp(m_SleepingCurrent, 0, 1);	
		if (m_SleepingCurrent == 0) 
		{
			m_SleepingOffset = Math.Clamp(m_SleepingOffset - (dt * 0.2), 0, 1);	
		}
		else
		{
			m_SleepingOffset = m_SleepingOffset + (dt * 0.2);
			if (m_SleepingOffset > Math.PI2) m_SleepingOffset = 0;
		}	
		float sleepOffset = Math.Clamp(Math.Sin(m_SleepingOffset) * 0.2, 0, 0.2);		
		PPEffects.SetVignetteEffectValue(m_VignetteSleeping, Math.Clamp( (2 * m_SleepingCurrent) - sleepOffset, 0, 2), 0,0,0,0);
		PPEffects.UpdateVignette();
	}
	
	static void SetSleepingEffect(float value)
	{
		m_SleepingValue = value;
	}
	
	static void SetOverdosedEffect(float value)
	{
		m_OverdosedValue = value;
	}
	
	static void SetPainEffect(float value)
	{
		m_PainValue = value;
	}
	
	static void SetConcussionEffect(float value)
	{
		m_ConcussionValue = value;
	}
	
	static void ResetAllEffects()
	{
		m_OverdosedValue = 0;
		m_ConcussionValue = 0;
		m_PainValue = 0;
		m_camShake = 0;
		
		m_SleepingValue = 0;
		m_SleepingOffset = 0;
		m_SleepingCurrent = 0;
		
		Update(0);
	}
};