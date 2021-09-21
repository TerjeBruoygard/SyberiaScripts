class PPERequester_SybPSI : PPERequester_GameplayBase
{
	private EffectSound m_psiEffectSound;
	private ref array<float> m_psiEffectColors = new array<float>();
	private float m_psiLastEffectOffset = 0;
	private float m_psiEffectOffset = 0;
	private bool m_psiEffectValue = false;
	
	void SetPsiEffect(bool value)
	{
		m_psiEffectValue = value;
	}
	
	override protected void OnStart(Param par = null)
	{
		super.OnStart(par);
		m_psiEffectColors.Insert(0.0);
		m_psiEffectColors.Insert(0.0);
		m_psiEffectColors.Insert(0.0);
		m_psiEffectColors.Insert(0.0);
	}
	
	override protected void OnStop(Param par = null)
	{
		super.OnStop();
		m_psiEffectValue = false;
		m_psiEffectColors[0] = 0.0;
		m_psiEffectColors[1] = 0.0;
		m_psiEffectColors[2] = 0.0;
		m_psiEffectColors[3] = 0.0;
		SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_psiEffectColors,PPEGlow.L_PSI,PPOperators.SUBSTRACT);
	}
	
	override void OnUpdate(float delta)
	{
		super.OnUpdate(delta);
		
		if (m_psiEffectValue)
		{
			m_psiEffectOffset = m_psiEffectOffset + (delta * 0.1);
			if (m_psiEffectOffset >= 1)
			{
				m_psiEffectOffset = 1;				
			}
		}
		else
		{
			m_psiEffectOffset = m_psiEffectOffset - (delta * 0.2);
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
			m_psiEffectColors[0] = m_psiEffectOffset * 0.8;
			m_psiEffectColors[1] = m_psiEffectOffset * 0.8;
			m_psiEffectColors[2] = 0.0;
			m_psiEffectColors[3] = 0.0;
		}
		
		SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_psiEffectColors,PPEGlow.L_PSI,PPOperators.SUBSTRACT);
	}
};