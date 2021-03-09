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
	SYBRPC_DELETECHAR_REQUEST,
	SYBRPC_CREATENEWCHAR_ERROR,
	SYBRPC_PDA_USER_STATE,
	SYBRPC_PDA_ADD_CONTACT,
	SYBRPC_PDA_CHECK_CONTACT,
	SYBRPC_PDA_SEND_MESSAGE,
	SYBRPC_PDA_SEND_GLOBAL_MESSAGE,
	SYBRPC_PDA_SEND_GROUP_MESSAGE,
	SYBRPC_PDA_CMD_GROUP,
	SYBRPC_SCREEN_MESSAGE,
	SYBRPC_CLIENT_OPTIONS,
	SYBRPC_ADMINTOOL_OPEN,
	SYBRPC_ADMINTOOL_PLAYERINFO,
	SYBRPC_ADMINTOOL_PLAYERUPDATE,
	SYBRPC_ADMINTOOL_SPAWNITEM,
	SYBRPC_ADMINTOOL_CLEARITEMS,
	SYBRPC_ADMINTOOL_UPDATEMAP,
	SYBRPC_ADMINTOOL_TELEPORT,
	SYBRPC_ADMINTOOL_FREECAM,
	SYBRPC_ADMINTOOL_ESPSYNCH,
	SYBRPC_ADMINTOOL_OBJMOVE,
	SYBRPC_ADMINTOOL_OBJDEL,
	SYBRPC_SKILLS_UPDATE,
	SYBRPC_SKILLS_ACTIVATE
};

enum SyberiaScreenEquipPages {
	SYBSEP_SPAWN_PAGE = 0,
	SYBSEP_BODY_PAGE = 1,
	SYBSEP_PANTS_PAGE = 2,
	SYBSEP_FOOT_PAGE = 3,
	SYBSEP_HEAD_PAGE = 4,
	SYBSEP_WEAPON_PAGE = 5,
	SYBSEP_ITEMS_PAGE = 6,
	SYBSEP_SPECIAL_PAGE = 7
};

enum SyberiaSleepingLevel {
	SYBSL_ENERGED = -4,
	SYBSL_SICK = -3,
	SYBSL_COLD = -2,
	SYBSL_HOT = -1,
	SYBSL_NONE = 0,
	SYBSL_COMFORT = 1,
	SYBSL_PERFECT = 2
};

enum SyberiaSkillType {
	SYBSKILL_IMMUNITY = 0,
	SYBSKILL_ATHLETICS = 1,
	SYBSKILL_STRENGTH = 2,
	SYBSKILL_MEDICINE = 3,
	SYBSKILL_STEALTH = 4,
	SYBSKILL_SURVIVAL = 5,
	SYBSKILL_FARMING = 6,
	SYBSKILL_HUNTING = 7,
	SYBSKILL_FISHING = 8,
	SYBSKILL_MECHANICS = 9,
	SYBSKILL_ELECTRONICS = 10,
	SYBSKILL_CARPENTRY = 11,
	SYBSKILL_METALWORKING = 12,
	SYBSKILL_BUILDING = 13,
	SYBSKILL_FIREARMS = 14,
	SYBSKILL_LOCKPICKING = 15,
	SYBSKILL_HERBALISM = 16,
	SYBSKILL_SEAMSTRESS = 17,
	
	// Total count of all skills (internal use only)
	SYBSKILL_TOTALCOUNT = 18
};

const int NTFKEY_SLEEPING = 1000;
const int NTFKEY_MINDSTATE = 1001;
const int NTFKEY_BULLETHIT = 1100;
const int NTFKEY_KNIFEHIT = 1101;
const int NTFKEY_HEMATOMA = 1102;
const int NTFKEY_VISCERADMG = 1103;
const int NTFKEY_CONCUSSION = 1104;
const int NTFKEY_PAIN = 1105;
const int NTFKEY_PAINKILLER = 1106;
const int NTFKEY_ANTIBIOTIC = 1107;
const int NTFKEY_STOMATCHHEAL = 1108;
const int NTFKEY_SEPSIS = 1109;
const int NTFKEY_ZVIRUS = 1110;
const int NTFKEY_BANDAGE1 = 1111;
const int NTFKEY_BANDAGE2 = 1112;
const int NTFKEY_HEMOSTATIC = 1113;
const int NTFKEY_HEMATOPOIESIS = 1114;
const int NTFKEY_USESALVE = 1115;
const int NTFKEY_ADRENALIN = 1116;
const int NTFKEY_OVERDOSED = 1117;
const int NTFKEY_INFLUENZA = 1118;
const int NTFKEY_STOMATCHPOISONING = 1119;

const int LEVELED_NTFKEY_BADGES_COUNT = 8;
const int LEVELED_NTFKEY_BADGES[LEVELED_NTFKEY_BADGES_COUNT] = { 
	NTFKEY_PAIN, NTFKEY_PAINKILLER, NTFKEY_ADRENALIN, NTFKEY_OVERDOSED, NTFKEY_INFLUENZA, 
	NTFKEY_ANTIBIOTIC, NTFKEY_STOMATCHPOISONING, NTFKEY_STOMATCHHEAL 
};

const string ALLOWED_LETTERS_IN_NAME = "abcdefghijklmnopqrstuvwxyz";

// U CAN CHANGE THIS CONSTANTS
const int SLEEPING_MAX_VALUE = 14000;
const int SLEEPING_LEVEL_5 = 100;
const int SLEEPING_LEVEL_4 = 1000;
const int SLEEPING_LEVEL_3 = 5000;
const int SLEEPING_LEVEL_2 = 10000;

const float MINDSTATE_MAX_VALUE = 100;
const float MINDSTATE_LEVEL_5 = 1.0;
const float MINDSTATE_LEVEL_4 = 10.0;
const float MINDSTATE_LEVEL_3 = 30.0;
const float MINDSTATE_LEVEL_2 = 70.0;

// Constants redefinition
modded class PlayerConstants
{
	static const float CHANCE_TO_BLEED_SLIDING_LADDER_PER_SEC = 0.1; // probability of bleeding source occuring while sliding down ladder without gloves given as percentage per second(0.5 means 50% chance bleeding source will happen every second while sliding down) 
	static const float GLOVES_DAMAGE_SLIDING_LADDER_PER_SEC = -0.5;// how much damage the gloves receive while sliding down the ladder (per sec)

	static const float BAREFOOT_MOVEMENT_BLEED_MODIFIER = 0.02;
	static const float SHOES_MOVEMENT_DAMAGE_PER_STEP = 0.001;
	
	static const float BLEEDING_SOURCE_BLOODLOSS_PER_SEC = -2;
	static const float BLOOD_REGEN_RATE_PER_SEC	= 0.05; //base amount of blood regenerated per second 
	
	static const float HEALTH_REGEN_MIN	= 0.002;	//health regen rate at BLOOD_THRESHOLD_FATAL blood level
	static const float HEALTH_REGEN_MAX	= 0.01;	//health regen rate at MAXIMUM blood level
	
	static const float SHOCK_REFILL_CONSCIOUS_SPEED			= 0.8;		//shock refill speed when the player is conscious
	static const float SHOCK_REFILl_UNCONSCIOUS_SPEED		= 0.28;		//shock refill speed when the player is unconscious
	
	
	// Metabolic
	static const float SL_ENERGY_CRITICAL = 0;
	static const float SL_ENERGY_LOW = 300;
	static const float SL_ENERGY_NORMAL = 1500;
	static const float SL_ENERGY_HIGH = 2800;
	
	static const float METABOLIC_SPEED_ENERGY_BASAL		= 0.01;		//energy loss per second while idle	
	static const float METABOLIC_SPEED_ENERGY_WALK		= 0.03;		//energy loss per second
	static const float METABOLIC_SPEED_ENERGY_JOG		= 0.15;		//energy loss per second
	static const float METABOLIC_SPEED_ENERGY_SPRINT	= 0.25;		//energy loss per second
	
	// Water
	static const float SL_WATER_CRITICAL = 0;
	static const float SL_WATER_LOW = 150;
	static const float SL_WATER_NORMAL = 700;
	static const float SL_WATER_HIGH = 1300;
	
	static const float METABOLIC_SPEED_WATER_BASAL		= 0.02;		//water loss per second while idle	
	static const float METABOLIC_SPEED_WATER_WALK		= 0.05;		//water loss per second
	static const float METABOLIC_SPEED_WATER_JOG		= 0.2;		//water loss per second
	static const float METABOLIC_SPEED_WATER_SPRINT		= 0.35;		//water loss per second
};

modded class GameConstants
{
	const int 	STAMINA_DRAIN_STANDING_SPRINT_PER_SEC = 2; //in units (how much sprint depletes stamina)
	const int 	STAMINA_DRAIN_CROUCHED_SPRINT_PER_SEC = 1; //in units (how much sprint in crouch depletes stamina)
	const int 	STAMINA_DRAIN_PRONE_SPRINT_PER_SEC = 1; //in units (how much sprint in prone depletes stamina)
	const int	STAMINA_DRAIN_SWIM_FAST_PER_SEC = 3; //in units (how much fast swimming depletes stamina)
	const int	STAMINA_DRAIN_LADDER_FAST_PER_SEC = 3; //in units (how much fast ladder climb depletes stamina)
	
	const float	STAMINA_DRAIN_HOLD_BREATH_START = 0.2; //in units (how much holding breath depletes stamina at the start)
	const float	STAMINA_DRAIN_HOLD_BREATH_END = 1.0; //in units (how much holding breath depletes stamina at the end)
	const float	STAMINA_DRAIN_JUMP = 20;		// in units (how much jumping depletes stamina)
	const float	STAMINA_DRAIN_VAULT = 10;		// in units (how much jumping depletes stamina)
	const float	STAMINA_DRAIN_CLIMB = 20;		// in units (how much jumping depletes stamina)
	const float	STAMINA_DRAIN_MELEE_LIGHT = 5; //in units (how much light melee punch depletes stamina)
	const float	STAMINA_DRAIN_MELEE_HEAVY = 15; //in units (how much heavy melee punch depletes stamina)
	const float	STAMINA_DRAIN_MELEE_EVADE = 8; // in units (how much evade depletes stamina)
	
	const float STAMINA_DRAIN_HOLD_BREATH_DURATION = 5.0; //in seconds, time it takes to increase stamina drain from STAMINA_DRAIN_HOLD_BREATH_START to STAMINA_DRAIN_HOLD_BREATH_END
	const float	STAMINA_DRAIN_HOLD_BREATH_EXPONENT = 4.0; //holding breath exponent
	
	const int 	STAMINA_GAIN_JOG_PER_SEC = 0.5; //in units (how much of stamina units is gained while jogging)
	const int 	STAMINA_GAIN_WALK_PER_SEC = 1; //in units (how much of stamina units is gained while walking)
	const int 	STAMINA_GAIN_IDLE_PER_SEC = 3; //in units (how much of stamina units is gained while iddling)
	const int	STAMINA_GAIN_SWIM_PER_SEC = 0.5; //in units (how much of stamina units is gained while slowly swim)
	const int	STAMINA_GAIN_LADDER_PER_SEC = 1; //in units (how much of stamina units is gained while slowly swim)
	const float STAMINA_GAIN_BONUS_CAP = 1.0; //in units (tells how much extra units can be added at best to stamina regain)
	
	const float STAMINA_KG_TO_STAMINAPERCENT_PENALTY = 0.75; //in units (by how many  units is max stamina bar reduced for each 1 kg of load weight)
	const float STAMINA_MIN_CAP = 5; //in units (overload won't reduce max stamina bar under this value)
	const float STAMINA_HOLD_BREATH_THRESHOLD_ACTIVATE = 10; // in units
	const float STAMINA_HOLD_BREATH_THRESHOLD_DRAIN = 0; // in units
	const float STAMINA_JUMP_THRESHOLD = 25; // in units
	const float STAMINA_VAULT_THRESHOLD = 20; // in units
	const float STAMINA_CLIMB_THRESHOLD = 42; // in units
	
	
	const float STAMINA_MELEE_HEAVY_THRESHOLD = STAMINA_DRAIN_MELEE_HEAVY; // in units (how many units we need to make a heavy hit in melee)
	const float STAMINA_MELEE_EVADE_THRESHOLD = 8; // in units
	const float STAMINA_REGEN_COOLDOWN_DEPLETION = 0.45; // in secs (how much time we will spend in cooldown before the stamina will starts with regeneration)
	const float STAMINA_REGEN_COOLDOWN_EXHAUSTION = 0.5;
	const float STAMINA_WEIGHT_LIMIT_THRESHOLD = 6000; //! in grams (weight where the player is not penalized by stamina)
	const float STAMINA_KG_TO_GRAMS = 1000; //for kg to g conversion
	const float STAMINA_SYNC_RATE = 1; //in secs
	const float STAMINA_MAX = 120;
	
	const float TEMPERATURE_RATE_COOLING_INSIDE = -0.02;
	const float TEMPERATURE_RATE_COOLING_GROUND = -0.05;
	const float TEMPERATURE_RATE_COOLING_PLAYER = 0; // disabled for correct calculation
	const float ENVIRO_ITEM_HEAT_TRANSFER_COEF = 0.02;
	const float TEMPERATURE_ITEM_HEAT_TRANSFER_COEF = 0.03;
	const float TEMPERATURE_ITEMS_HEAT_IN_INVENTORY_FROM_BODY = 26;
};