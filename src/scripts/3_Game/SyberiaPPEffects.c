modded class PPEffects
{
	static void SetColorizationNV(float r, float g, float b)
	{
		SyberiaPPEffects.SetColorizationNV(r, g, b);
	}
	
	static void SetNVParams(float light_mult, float noise_intensity, float sharpness, float grain_size)
	{
		SyberiaPPEffects.SetNVParams(light_mult, noise_intensity, sharpness, grain_size);
	}
	
	static void SetNVParams2(float light_mult, float noise_intensity, float sharpness, float grain_size)
	{
		Material matHDR = GetGame().GetWorld().GetMaterial("Graphics/Materials/postprocess/filmgrainNV");
		g_Game.NightVissionLightParams(light_mult, noise_intensity);
		matHDR.SetParam("Sharpness", sharpness);
		matHDR.SetParam("GrainSize", grain_size);
	}
};

class SyberiaPPEffects
{
	static Material m_MatChroma;
	static Material m_MatColors;
	static EffectSound m_hearthbitSound;
	static EffectSound m_psiEffectSound;
	static float m_matChromaOffsetLast;
	static float m_camShake;
	
	static int m_blurEffect;
	
	static float m_OverdosedOffset;
	static float m_OverdosedValue;
	
	static float m_PainValue;
	static float m_PainOffset;
	
	static float m_RadiationEffect;
	static float m_RadiationValue;
	static float m_RadEffectColors[4];
	
	static float m_ConcussionValue;
	static float m_ConcussionOffset;
	
	static int m_VignetteSleeping;
	static float m_SleepingCurrent;
	static float m_SleepingValue;
	static float m_SleepingOffset;
	
	static float m_psiEffectColors[4];
	static float m_psiLastEffectOffset;
	static float m_psiEffectOffset;
	static bool m_psiEffectValue;
	
	static float m_nvgEffectColors[4];
	static bool m_colorsMarkDirty;
	
	static float m_lightMult;
	static float m_noiseIntensity;
	static float m_sharpness;
	static float m_grainSize;
	static bool m_lightOptionsDirty;
	
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
		
		m_MatColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
		
		m_OverdosedOffset = 0;
		m_OverdosedValue = 0;
				
		m_PainValue = 0;
		m_PainOffset = 0;
		
		m_RadiationEffect = 0;
		m_RadiationValue = 0;		
		m_RadEffectColors[0] = 1.0;
		m_RadEffectColors[1] = 1.0;
		m_RadEffectColors[2] = 1.0;
		m_RadEffectColors[3] = 0.0;
		
		m_ConcussionValue = 0;
		m_ConcussionOffset = 0;
		
		m_SleepingValue = 0;
		m_SleepingOffset = 0;
		m_SleepingCurrent = 0;
		m_VignetteSleeping = PPEffects.RegisterVignetteEffect();
		
		m_psiLastEffectOffset = 0;
		m_psiEffectOffset = 0;
		m_psiEffectValue = false;
		m_psiEffectColors[0] = 1.0;
		m_psiEffectColors[1] = 1.0;
		m_psiEffectColors[2] = 1.0;
		m_psiEffectColors[3] = 0.0;
		
		m_nvgEffectColors[0] = 1.0;
		m_nvgEffectColors[1] = 1.0;
		m_nvgEffectColors[2] = 1.0;
		m_nvgEffectColors[3] = 0.0;
		m_MatColors.SetParam("ColorizationColor", m_nvgEffectColors);
		m_colorsMarkDirty = false;
		
		m_lightMult = 1.0;
		m_noiseIntensity = 0.0;
		m_sharpness = 2.35;
		m_grainSize = 2.75;
		m_lightOptionsDirty = true;
	}
	
	static void Update(float dt)
	{
		float matChromaOffset = 0;
		float blurEffect = 0;
		float sinusVal = 0;
		
		if (m_psiEffectValue)
		{
			m_psiEffectOffset = m_psiEffectOffset + (dt * 0.1);
			if (m_psiEffectOffset >= 1)
			{
				m_psiEffectOffset = 1;				
			}
		}
		else
		{
			m_psiEffectOffset = m_psiEffectOffset - (dt * 0.2);
			if (m_psiEffectOffset < 0)
			{
				m_psiEffectOffset = 0;				
			}
		}
		
		if (m_psiLastEffectOffset != m_psiEffectOffset)
		{
			if (m_psiEffectOffset > 0 && m_psiLastEffectOffset == 0)
			{
				if (!m_psiEffectSound)
				{
					GetGame().GetPlayer().PlaySoundSet(m_psiEffectSound, "psieffect_SoundSet", 5.0, 2.0, true);
				}
				else
				{
					m_psiEffectSound.SoundPlay();
				}
			}
			else if (m_psiEffectOffset == 0 && m_psiLastEffectOffset > 0)
			{
				m_psiEffectSound.SoundStop();
			}
			
			m_psiLastEffectOffset = m_psiEffectOffset;
			m_psiEffectColors[0] = 1.0 - (m_psiEffectOffset * 0.8);
			m_psiEffectColors[1] = 1.0 - (m_psiEffectOffset * 0.8);
			m_psiEffectColors[2] = 1.0;
			m_psiEffectColors[3] = 0.0;
			m_colorsMarkDirty = true;
		}
		
		float newRadValue = m_RadiationValue;
		if (m_RadiationEffect > 0)
		{
			newRadValue = Math.Clamp(m_RadiationValue + (dt * 0.1), 0, m_RadiationEffect);
		}
		else
		{
			newRadValue = Math.Max(m_RadiationValue - (dt * 0.1), 0);
		}
		
		if (newRadValue != m_RadiationValue)
		{
			m_RadiationValue = newRadValue;
			PPEffects.SetNVParams2(1.0, 1.0, 10.0, 1.0);
			
			float radColorValue = Math.Clamp(m_RadiationValue, 0, 1);
			m_RadEffectColors[0] = 1.0 - (radColorValue * 0.2);
			m_RadEffectColors[1] = 1.0 - (radColorValue * 0.2);
			m_RadEffectColors[2] = 1.0 - (radColorValue * 0.5);
			m_RadEffectColors[3] = 0.0;
			m_colorsMarkDirty = true;
			m_lightOptionsDirty = true;
		}
		
		if (m_colorsMarkDirty)
		{
			m_colorsMarkDirty = false;
			float color[4];
			color[0] = m_psiEffectColors[0];
			color[1] = m_psiEffectColors[1];
			color[2] = m_psiEffectColors[2];
			color[3] = 0.0;
			
			if (m_nvgEffectColors[0] != 0 || m_nvgEffectColors[1] != 0 || m_nvgEffectColors[2] != 0)
			{
				color[0] = color[0] * m_nvgEffectColors[0];
				color[1] = color[1] * m_nvgEffectColors[1];
				color[2] = color[2] * m_nvgEffectColors[2];
			}
			
			if (m_RadEffectColors[0] != 0 || m_RadEffectColors[1] != 0 || m_RadEffectColors[2] != 0)
			{
				color[0] = color[0] * m_RadEffectColors[0];
				color[1] = color[1] * m_RadEffectColors[1];
				color[2] = color[2] * m_RadEffectColors[2];
			}
			
			m_MatColors.SetParam("ColorizationColor", color);
		}
		
		if (m_lightOptionsDirty)
		{
			m_lightOptionsDirty = false;
			float lightMul = m_lightMult;
			float noiseIntensity = Math.Min(2, m_noiseIntensity + m_RadiationValue);
			float sharpness = Math.Min(10, m_sharpness + (m_RadiationValue * 10));
			float grainSize = Math.Max(1, m_grainSize - m_RadiationValue);
			PPEffects.SetNVParams2(lightMul, noiseIntensity, sharpness, grainSize);		
		}
		
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
	
	static void SetRadiationEffect(float value)
	{
		m_RadiationEffect = value;
	}
	
	static void SetConcussionEffect(float value)
	{
		m_ConcussionValue = value;
	}
	
	static void SetPsiEffect(bool value)
	{
		m_psiEffectValue = value;
	}
	
	static void SetNVParams(float light_mult, float noise_intensity, float sharpness, float grain_size)
	{
		m_lightMult = light_mult;
		m_noiseIntensity = noise_intensity;
		m_sharpness = sharpness;
		m_grainSize = grain_size;
		m_lightOptionsDirty = true;
	}
	
	static void SetColorizationNV(float r, float g, float b)
	{
		m_nvgEffectColors[0] = r;
		m_nvgEffectColors[1] = g;
		m_nvgEffectColors[2] = b;
		m_colorsMarkDirty = true;
	}
	
	static void ResetAllEffects()
	{
		m_OverdosedValue = 0;
		m_ConcussionValue = 0;
		m_PainValue = 0;
		m_camShake = 0;
		
		m_RadiationEffect = 0;
		m_RadiationValue = 0;
		
		m_SleepingValue = 0;
		m_SleepingOffset = 0;
		m_SleepingCurrent = 0;
		
		m_psiEffectValue = false;
		m_psiEffectOffset = 0;
		m_psiLastEffectOffset = 0;
		
		m_psiEffectColors[0] = 1.0;
		m_psiEffectColors[1] = 1.0;
		m_psiEffectColors[2] = 1.0;
		m_psiEffectColors[3] = 0.0;
		
		m_nvgEffectColors[0] = 1.0;
		m_nvgEffectColors[1] = 1.0;
		m_nvgEffectColors[2] = 1.0;
		m_nvgEffectColors[3] = 0.0;
		
		m_RadEffectColors[0] = 1.0;
		m_RadEffectColors[1] = 1.0;
		m_RadEffectColors[2] = 1.0;
		m_RadEffectColors[3] = 0.0;	
		
		m_MatColors.SetParam("ColorizationColor", m_nvgEffectColors);
		m_colorsMarkDirty = false;
		
		m_lightMult = 1.0;
		m_noiseIntensity = 0.0;
		m_sharpness = 2.35;
		m_grainSize = 2.75;
		m_lightOptionsDirty = true;
		
		if (m_psiEffectSound) 
		{
			m_psiEffectSound.SoundStop();
		}
		
		Update(0);
	}
};