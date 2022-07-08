const string Syberia_ModPreffix = "[SYBERIA] ";
const bool Syberia_DebugMode = true;

void SybLog(string message)
{
	if (Syberia_DebugMode) Print(Syberia_ModPreffix + message);
}

bool ConfigIsInstanceOf(string basePath, string classname, string baseClassname)
{
	if (!GetGame().ConfigIsExisting(basePath + " " + classname))
	{
		return false;
	}
	
	string baseOutputName;
	while(GetGame().ConfigGetBaseName(basePath + " " + classname, baseOutputName))
	{
		if (baseOutputName == baseClassname)
		{
			return true;
		}
		
		classname = baseOutputName;
	}
	
	return false;
}

enum SyberiaRPC {
    SYBRPC_RESPAWN_SCREEN_OPEN,
	SYBRPC_NEWCHAR_SCREEN_OPEN,
	SYBRPC_EQUIP_SCREEN_OPEN,
	SYBRPC_CREATENEWCHAR_REQUEST,
	SYBRPC_STARTGAME_REQUEST,
	SYBRPC_RESPAWN_REQUEST,
	SYBRPC_DELETECHAR_REQUEST
};

const int NTFKEY_SLEEPING = 1000;
const int NTFKEY_BULLETHIT = 1100;
const int NTFKEY_KNIFEHIT = 1101;
const int NTFKEY_HEMATOMA = 1102;
const int NTFKEY_VISCERADMG = 1103;
const int NTFKEY_CONCUSSION = 1104;
const int NTFKEY_PAIN = 1105;
const int NTFKEY_PAINKILLER = 1106;
const int NTFKEY_ANTIBIOTIC = 1107;
const int NTFKEY_STOMATCHHEAL = 1108;

const int LEVELED_NTFKEY_BADGES_COUNT = 2;
const int LEVELED_NTFKEY_BADGES[LEVELED_NTFKEY_BADGES_COUNT] = { NTFKEY_PAIN, NTFKEY_PAINKILLER };

// VALUE - (SLEEPING_DEC_PER_SEC + SLEEPING_DEC_PER_INJURE_SEC) + (SLEEPING_INC_PER_UNCONSION_SEC + SLEEPING_INC_PER_SLEEPING_SEC)
const int SLEEPING_MAX_VALUE = 14000;
const int SLEEPING_DEC_PER_SEC = 1;
const bool SLEEPING_UNCONSION_ENABLED = false;
const int SLEEPING_INC_PER_UNCONSION_BOOST_VALUE = 5;
const int SLEEPING_INC_PER_UNCONSION_BOOST_TIME = 30;
const int SLEEPING_INC_PER_SLEEPING_SEC = 15;
const int SLEEPING_LEVEL_5 = 100;
const int SLEEPING_LEVEL_4 = 1000;
const int SLEEPING_LEVEL_3 = 5000;
const int SLEEPING_LEVEL_2 = 10000;

// ADV MED
const float PAIN_LVL1_TIME_SEC = 60 * 5;
const float PAIN_LVL2_TIME_SEC = 60 * 30;
const float PAIN_LVL3_TIME_SEC = 60 * 60;
const float PAIN_MAX_DURATION_SEC = 60 * 60 * 4;
const float PAINKILLER_MAX_DURATION_SEC = 60 * 60 * 1;

const float BLEEDING_BULLETHIT_HEALTHLOSE_PER_SECOND = -1;
const float BLEEDING_BULLETHIT_OPEN_PER_SECOND = -25;
const float BLEEDING_BULLETHIT_CUPD1_PER_SECOND = -10;
const float BLEEDING_BULLETHIT_CUPD2_PER_SECOND = -3;
const float BLEEDING_BULLETHIT_CUPD3_PER_SECOND = -1;

const float BLEEDING_KNIFEHIT_HEALTHLOSE_PER_SECOND = -1;
const float BLEEDING_KNIFEHIT_OPEN_PER_SECOND = -40;
const float BLEEDING_KNIFEHIT_CUPD1_PER_SECOND = -10;
const float BLEEDING_KNIFEHIT_CUPD2_PER_SECOND = -3;
const float BLEEDING_KNIFEHIT_CUPD3_PER_SECOND = -1;

const float BLEEDING_VISCERA_BLOODLOSE_PER_SECOND = -30;
const float BLEEDING_VISCERA_HEALTHLOSE_PER_SECOND = -5;

const float BLEEDING_HEMATOMA_BLOODLOSE_PER_SECOND = 0;
const float BLEEDING_HEMATOMA_HEALTHLOSE_PER_SECOND = -0.3;

const float HEMATOMA_REGEN_TIMER_SEC = 60 * 15;
const float CUTHIT_REGEN_TIMER_SEC = 60 * 5;

const float HEMOLOGIC_SHOCK_DIETIME_SEC = 60; 

// Constants redefinition
modded class PlayerConstants
{
	static const float CHANCE_TO_BLEED_SLIDING_LADDER_PER_SEC = 0.1; // probability of bleeding source occuring while sliding down ladder without gloves given as percentage per second(0.5 means 50% chance bleeding source will happen every second while sliding down) 
	static const float GLOVES_DAMAGE_SLIDING_LADDER_PER_SEC = -0.5;// how much damage the gloves receive while sliding down the ladder (per sec)

	static const float BAREFOOT_MOVEMENT_BLEED_MODIFIER = 0.02;
	static const float SHOES_MOVEMENT_DAMAGE_PER_STEP = 0.001;
	
	static const float BLEEDING_SOURCE_BLOODLOSS_PER_SEC = -1;
	static const float BLOOD_REGEN_RATE_PER_SEC	= 0.05; 	//base amount of blood regenerated per second 
	
	static const float HEALTH_REGEN_MIN	= 0.001;	//health regen rate at BLOOD_THRESHOLD_FATAL blood level
	static const float HEALTH_REGEN_MAX	= 0.005;	//health regen rate at MAXIMUM blood level
	
	static const float SHOCK_REFILL_CONSCIOUS_SPEED			= 2;		//shock refill speed when the player is conscious
	static const float SHOCK_REFILl_UNCONSCIOUS_SPEED		= 0.2;		//shock refill speed when the player is unconscious
}