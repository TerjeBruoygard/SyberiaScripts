modded class PlayerSwayConstants
{
	static const float SWAY_TIME_STABLE = 30.0;
};

modded class StaminaHandler
{
	private float CalculateStaminaConsumerValue(EStaminaConsumers consumer)
	{
		float resultValue = m_Stamina;
		if (consumer == EStaminaConsumers.HOLD_BREATH)
		{
			resultValue = resultValue * m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_BREATH_DEC, 1, 1);
		}
		else if (consumer == EStaminaConsumers.JUMP)
		{
			resultValue = resultValue / (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_JUMP_STAMINA_DEC, 0, 0));
		}
		else if (consumer == EStaminaConsumers.VAULT)
		{
			resultValue = resultValue / (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_JUMP_STAMINA_DEC, 0, 0));
		}
		else if (consumer == EStaminaConsumers.CLIMB)
		{
			resultValue = resultValue / (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_JUMP_STAMINA_DEC, 0, 0));
		}
		else if (consumer == EStaminaConsumers.MELEE_EVADE)
		{
			resultValue = resultValue / (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_BLOCK_STAMINA_DEC, 0, 0));
		}
		else if (consumer == EStaminaConsumers.MELEE_HEAVY)
		{
			resultValue = resultValue / (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_HEAVY_ATTACK_STAMINA_DEC, 0, 0));
		}

		resultValue = resultValue * m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_STAMINA_MAX, 1, 1);
		resultValue = resultValue * (1.0 + (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_STAMINA_KG_TO, 0, 0) * 0.25));
		return resultValue;
	}
	
	override bool HasEnoughStaminaFor(EStaminaConsumers consumer)
	{
		return m_StaminaConsumers.HasEnoughStaminaFor(consumer, CalculateStaminaConsumerValue(consumer), m_StaminaDepleted, m_StaminaCap);
	}
	
	override bool HasEnoughStaminaToStart(EStaminaConsumers consumer)
	{
		return m_StaminaConsumers.HasEnoughStaminaToStart(consumer, CalculateStaminaConsumerValue(consumer), m_StaminaDepleted, m_StaminaCap);
	}
	
	override void DepleteStamina(EStaminaModifiers modifier, float dT = -1)
	{
		float depleteMod = 1;
		float additionaMod = 1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_STAMINA_MAX, 0, 0);
		additionaMod = additionaMod * (1.0 - (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_STAMINA_KG_TO, 0, 0) * 0.25));
		StaminaModifier sm = m_StaminaModifiers.GetModifierData(modifier);
		if (modifier == EStaminaModifiers.HOLD_BREATH)
		{
			depleteMod = m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_BREATH_DEC, 1, 1);
			sm.SetMinValue( GameConstants.STAMINA_DRAIN_HOLD_BREATH_START / depleteMod );
		}
		else if (modifier == EStaminaModifiers.JUMP)
		{
			depleteMod = 1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_JUMP_STAMINA_DEC, 0, 0);
			sm.SetMaxValue( GameConstants.STAMINA_DRAIN_JUMP * depleteMod * additionaMod );
		}
		else if (modifier == EStaminaModifiers.VAULT)
		{
			depleteMod = 1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_JUMP_STAMINA_DEC, 0, 0);
			sm.SetMaxValue( GameConstants.STAMINA_DRAIN_VAULT * depleteMod * additionaMod );
		}
		else if (modifier == EStaminaModifiers.CLIMB)
		{
			depleteMod = 1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_JUMP_STAMINA_DEC, 0, 0);
			sm.SetMaxValue( GameConstants.STAMINA_DRAIN_CLIMB * depleteMod * additionaMod );
		}
		else if (modifier == EStaminaModifiers.MELEE_EVADE)
		{
			depleteMod = 1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_BLOCK_STAMINA_DEC, 0, 0);
			sm.SetMaxValue( GameConstants.STAMINA_DRAIN_MELEE_EVADE * depleteMod * additionaMod );
			sm.SetMinValue( sm.GetMaxValue() * 0.5 );
		}
		else if (modifier == EStaminaModifiers.MELEE_LIGHT)
		{
			depleteMod = 1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_FAST_ATTACK_STAMINA_DEC, 0, 0);
			sm.SetMaxValue( GameConstants.STAMINA_DRAIN_MELEE_LIGHT * depleteMod * additionaMod );
		}
		else if (modifier == EStaminaModifiers.MELEE_HEAVY)
		{
			depleteMod = 1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_STRENGTH_HEAVY_ATTACK_STAMINA_DEC, 0, 0);
			sm.SetMaxValue( GameConstants.STAMINA_DRAIN_MELEE_HEAVY * depleteMod * additionaMod );
		}
		
		super.DepleteStamina(modifier, dT);
	}
	
	override protected void StaminaProcessor_Move(HumanMovementState pHumanMovementState)
	{
		switch ( pHumanMovementState.m_iMovement )
		{
		case DayZPlayerConstants.MOVEMENTIDX_SPRINT: //sprint
			if ( pHumanMovementState.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_ERECT )
			{
				m_StaminaDelta = -GameConstants.STAMINA_DRAIN_STANDING_SPRINT_PER_SEC;
				m_StaminaDelta = m_StaminaDelta * (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SPRINT_DEC, 0, 0));
				m_StaminaDelta = m_StaminaDelta * (1.0 - (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_JOG_INC, 0, 0) * 0.25));
				SetCooldown(GameConstants.STAMINA_REGEN_COOLDOWN_DEPLETION);
				break;
			}
			if ( pHumanMovementState.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_CROUCH)
			{
				m_StaminaDelta = -GameConstants.STAMINA_DRAIN_CROUCHED_SPRINT_PER_SEC;
				m_StaminaDelta = m_StaminaDelta * (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SPRINT_DEC, 0, 0));
				m_StaminaDelta = m_StaminaDelta * (1.0 - (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_JOG_INC, 0, 0) * 0.25));
				SetCooldown(GameConstants.STAMINA_REGEN_COOLDOWN_DEPLETION);
				break;
			}
			m_StaminaDelta = GameConstants.STAMINA_GAIN_JOG_PER_SEC;
		break;
			
		case DayZPlayerConstants.MOVEMENTIDX_RUN: //jog
			if (!m_IsInCooldown)
			{
				m_StaminaDelta = (GameConstants.STAMINA_GAIN_JOG_PER_SEC + CalcStaminaGainBonus());
				m_StaminaDelta = m_StaminaDelta * (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_JOG_INC, 1, 1) * 2.0);
				m_StaminaDelta = m_StaminaDelta * (1.0 + (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SPRINT_DEC, 0, 0) * 0.5));
			}
		break;
			
		case DayZPlayerConstants.MOVEMENTIDX_WALK: //walk
			if (!m_IsInCooldown)
			{
				m_StaminaDelta = (GameConstants.STAMINA_GAIN_WALK_PER_SEC + CalcStaminaGainBonus());
				m_StaminaDelta = m_StaminaDelta * (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_JOG_INC, 1, 1) * 2.0);
				m_StaminaDelta = m_StaminaDelta * (1.0 + (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SPRINT_DEC, 0, 0) * 0.5));
			}
		break;
			
		case DayZPlayerConstants.MOVEMENTIDX_IDLE: //idle
			if (m_Player.IsRolling())
			{
				m_StaminaDelta = GameConstants.STAMINA_GAIN_ROLL_PER_SEC;
				break;
			}
			if (!m_IsInCooldown)
			{
				m_StaminaDelta = (GameConstants.STAMINA_GAIN_IDLE_PER_SEC + CalcStaminaGainBonus()) * m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_IDDLE_INC, 1, 1);
			}
		break;
			
		default:
			if ( !m_IsInCooldown )
			{
				m_StaminaDelta = GameConstants.STAMINA_GAIN_IDLE_PER_SEC * m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_IDDLE_INC, 1, 1);
			}
		break;
		}
	}
	
	override protected void StaminaProcessor_Swimming(HumanMovementState pHumanMovementState)
	{
		switch ( pHumanMovementState.m_iMovement )
		{
		case 3: //swim fast
			m_StaminaDelta = -GameConstants.STAMINA_DRAIN_SWIM_FAST_PER_SEC;
			m_StaminaDelta = m_StaminaDelta * (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SWIM_SPRINT_DEC, 0, 0));
			m_StaminaDelta = m_StaminaDelta * (1.0 - (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SWIM_INC, 0, 0) * 0.25));
			SetCooldown(GameConstants.STAMINA_REGEN_COOLDOWN_DEPLETION);
			break;
		break;
			
		case 2: //swim slow
			if (!m_IsInCooldown)
			{
				m_StaminaDelta = (GameConstants.STAMINA_GAIN_SWIM_PER_SEC + CalcStaminaGainBonus());
				m_StaminaDelta = m_StaminaDelta * m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SWIM_INC, 1, 1);
				m_StaminaDelta = m_StaminaDelta * (1.0 + (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_SWIM_SPRINT_DEC, 0, 0) * 0.25));
			}
		break;
			
		default:
			if( !m_IsInCooldown )
			{
				m_StaminaDelta = GameConstants.STAMINA_GAIN_IDLE_PER_SEC;
			}
		break;
		}
	}
	
	override protected void StaminaProcessor_Ladder(HumanMovementState pHumanMovementState)
	{
		switch ( pHumanMovementState.m_iMovement )
		{
		case 2: //climb up (fast)
			m_StaminaDelta = -GameConstants.STAMINA_DRAIN_LADDER_FAST_PER_SEC;
			m_StaminaDelta = m_StaminaDelta * (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_LADDER_SPRINT_DEC, 0, 0));
			m_StaminaDelta = m_StaminaDelta * (1.0 - (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_LADDER_INC, 0, 0) * 0.25));
			SetCooldown(GameConstants.STAMINA_REGEN_COOLDOWN_DEPLETION);
			break;
		break;
			
		case 1: //climb up (slow)
			if (!m_IsInCooldown)
			{
				m_StaminaDelta = (GameConstants.STAMINA_GAIN_LADDER_PER_SEC + CalcStaminaGainBonus());
				m_StaminaDelta = m_StaminaDelta * m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_LADDER_INC, 1, 1);
				m_StaminaDelta = m_StaminaDelta * (1.0 + (m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_LADDER_SPRINT_DEC, 0, 0) * 0.25));
			}
		break;
			
		default:
			if( !m_IsInCooldown )
			{
				m_StaminaDelta = GameConstants.STAMINA_GAIN_IDLE_PER_SEC;
			}
		break;
		}
	}
	
	override protected void SetCooldown(float time, int modifier = -1)
	{
		super.SetCooldown(time * 2.5 * (1.0 - m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_ATHLETICS_COLDOWN_DEC, 0, 0)), modifier);
	}
};