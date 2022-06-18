const string Syberia_ModPreffix = "[SYBERIA] ";
const bool Syberia_DebugMode = false;
const string Syberia_Version = "OPEN BETA 0.49L";

class SyberiaVersionChecker {
	void CLIENT_AND_SERVER_MODS_VERSION_MISSMATCH_0_49K() {}
}

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

enum SyberiaERPC {
	SYBERPC_FIRST = -246400,
	SYBERPC_SYNCH_LIVESPACE_CLIENT,
	SYBERPC_SYNCH_LIVESPACE_SERVER,
	SYBERPC_SYNCH_TRADER_POINT_CLIENT,
	SYBERPC_SYNCH_TRADER_POINT_SERVER,
	SYBERPC_SYNCH_PLAYER_SYBSTATS_REQUEST,
	SYBERPC_SYNCH_PLAYER_SYBSTATS_RESPONSE
};

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
	SYBRPC_ADMINTOOL_DELETE_CHARACTER,
	SYBRPC_ADMINTOOL_KICK,
	SYBRPC_ADMINTOOL_TELEPORT_TO_PLAYER,
	SYBRPC_ADMINTOOL_TELEPORT_PLAYER_TO_ME,	
	SYBRPC_ADMINTOOL_MESSAGE,
	SYBRPC_SKILLS_UPDATE,
	SYBRPC_SKILLS_ACTIVATE,
	SYBRPC_STETHOSCOPE_INSPECT,
	SYBRPC_CURRENT_ZONE_SYNC,
	SYBRPC_SYNC_TOXIC_ZONES,
	SYBRPC_OPEN_TRADE_MENU,
	SYBRPC_CLOSE_TRADER_MENU,
	SYBRPC_ACTION_TRADER,
	SYBRPC_SELF_KICK,
	SYBRPC_SYNC_CRAFTS,
	SYBRPC_HOMEBOOK_OPEN
};

enum SyberiaScreenEquipPages {
	SYBSEP_SPAWN_PAGE = 0,
	SYBSEP_BODY_PAGE = 1,
	SYBSEP_PANTS_PAGE = 2,
	SYBSEP_FOOT_PAGE = 3,
	SYBSEP_HEAD_PAGE = 4,
	SYBSEP_MASK_PAGE = 5,
	SYBSEP_GLOVES_PAGE = 6,
	SYBSEP_VEST_PAGE = 7,
	SYBSEP_BACKPACK_PAGE = 8,
	SYBSEP_WEAPON_PAGE = 9,
	SYBSEP_ITEMS_PAGE = 10,
	SYBSEP_SPECIAL_PAGE = 11,
	SYBSEP_TOTAL_COUNT = 12
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

const int SYBERIA_ENABLED_SKILLS_COUNT = 7;
const int SYBERIA_ENABLED_SKILLS_LIST[SYBERIA_ENABLED_SKILLS_COUNT] = {
	SyberiaSkillType.SYBSKILL_IMMUNITY,
	SyberiaSkillType.SYBSKILL_MEDICINE,
	SyberiaSkillType.SYBSKILL_ATHLETICS,
	SyberiaSkillType.SYBSKILL_STRENGTH,
	SyberiaSkillType.SYBSKILL_STEALTH,
	SyberiaSkillType.SYBSKILL_SURVIVAL,
	SyberiaSkillType.SYBSKILL_HUNTING
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
const int NTFKEY_RADIATIONSICKNESS = 1120;
const int NTFKEY_RADIOPROTECTION = 1121;
const int NTFKEY_DISINFECTED = 1122;
const int NTFKEY_ANTIDEPRESANT = 1123;

const int LEVELED_NTFKEY_BADGES_COUNT = 11;
const int LEVELED_NTFKEY_BADGES[LEVELED_NTFKEY_BADGES_COUNT] = { 
	NTFKEY_PAIN, NTFKEY_PAINKILLER, NTFKEY_ADRENALIN, NTFKEY_OVERDOSED, NTFKEY_INFLUENZA, 
	NTFKEY_ANTIBIOTIC, NTFKEY_STOMATCHPOISONING, NTFKEY_STOMATCHHEAL, NTFKEY_RADIATIONSICKNESS,
	NTFKEY_RADIOPROTECTION, NTFKEY_ANTIDEPRESANT 
};

class SyberiaConfig
{
	// Auth	
    ref array<string> m_allowedLettersInName = new array<string>;
    
	// Sleeping
	int m_sleepingMaxValue;
    int m_sleepingLevel5;
    int m_sleepingLevel4;
    int m_sleepingLevel3;
    int m_sleepingLevel2;
	
	// Mindstate
	float m_mindstateMaxValue;
	float m_mindstateLevel5;
	float m_mindstateLevel4;
	float m_mindstateLevel3;
	float m_mindstateLevel2;
	
	protected void ConfigGetTextArray(string path, out array<string> result, int count)
	{
		if (!GetGame().ConfigIsExisting(path))
			Error("Config property not exists");
		
		GetGame().ConfigGetTextArray(path, result);
		if (count != -1 && result.Count() != count)
			Error("Count check failed for config loading");
	}
	
	protected void ConfigGetFloatArray(string path, out array<float> result, int count)
	{
		if (!GetGame().ConfigIsExisting(path))
			Error("Config property not exists");
		
		GetGame().ConfigGetFloatArray(path, result);
		if (count != -1 && result.Count() != count)
			Error("Count check failed for config loading");
	}
	
	protected void ConfigGetIntArray(string path, out array<int> result, int count)
	{
		if (!GetGame().ConfigIsExisting(path))
			Error("Config property not exists");
		
		GetGame().ConfigGetIntArray(path, result);
		if (count != -1 && result.Count() != count)
			Error("Count check failed for config loading");
	}
	
	protected int ConfigGetInt(string path)
	{
		if (!GetGame().ConfigIsExisting(path))
			Error("Config property not exists");
		
		return GetGame().ConfigGetInt(path);
	}
	
	protected float ConfigGetFloat(string path)
	{
		if (!GetGame().ConfigIsExisting(path))
			Error("Config property not exists");
		
		return GetGame().ConfigGetFloat(path);
	}
	
	void Init()
	{
		// Auth
		ConfigGetTextArray("CfgSyberia AuthSystem allowedLettersInName", m_allowedLettersInName, -1);
		
		// Sleeping
		m_sleepingMaxValue = ConfigGetInt("CfgSyberia SleepingSystem sleepingMaxValue");
	    m_sleepingLevel5 = ConfigGetInt("CfgSyberia SleepingSystem sleepingLevel5");
	    m_sleepingLevel4 = ConfigGetInt("CfgSyberia SleepingSystem sleepingLevel4");
	    m_sleepingLevel3 = ConfigGetInt("CfgSyberia SleepingSystem sleepingLevel3");
	    m_sleepingLevel2 = ConfigGetInt("CfgSyberia SleepingSystem sleepingLevel2");
		
		// Mindstate
		m_mindstateMaxValue = ConfigGetFloat("CfgSyberia MindstateSystem mindstateMaxValue");
	    m_mindstateLevel5 = ConfigGetFloat("CfgSyberia MindstateSystem mindstateLevel5");
	    m_mindstateLevel4 = ConfigGetFloat("CfgSyberia MindstateSystem mindstateLevel4");
	    m_mindstateLevel3 = ConfigGetFloat("CfgSyberia MindstateSystem mindstateLevel3");
	    m_mindstateLevel2 = ConfigGetFloat("CfgSyberia MindstateSystem mindstateLevel2");
	}
};

static ref SyberiaConfig m_syberiaConfig = null;
ref SyberiaConfig GetSyberiaConfig()
{
    if (!m_syberiaConfig)
    {
        m_syberiaConfig = new SyberiaConfig;
		m_syberiaConfig.Init();
    }
    
    return m_syberiaConfig;
};

// Constants redefinition
modded class PlayerConstants
{
	static const float CHANCE_TO_BLEED_SLIDING_LADDER_PER_SEC = 0.1; // probability of bleeding source occuring while sliding down ladder without gloves given as percentage per second(0.5 means 50% chance bleeding source will happen every second while sliding down) 
	static const float GLOVES_DAMAGE_SLIDING_LADDER_PER_SEC = -0.5;// how much damage the gloves receive while sliding down the ladder (per sec)

	static const float BAREFOOT_MOVEMENT_BLEED_MODIFIER = 0.05;
	static const float SHOES_MOVEMENT_DAMAGE_PER_STEP = 0.003;
	
	static const float BLEEDING_SOURCE_BLOODLOSS_PER_SEC = -0.5;
	static const float BLOOD_REGEN_RATE_PER_SEC	= 0.05; //base amount of blood regenerated per second 
	
	static const float LOW_ENERGY_DAMAGE_PER_SEC			= 0.03;	//health loss per second while low on energy
	static const float LOW_WATER_DAMAGE_PER_SEC				= 0.04;	//health loss per second while low on water
	
	static const float HEALTH_REGEN_MIN	= 0.002;	//health regen rate at BLOOD_THRESHOLD_FATAL blood level
	static const float HEALTH_REGEN_MAX	= 0.01;	//health regen rate at MAXIMUM blood level
	
	static const float SHOCK_REFILL_CONSCIOUS_SPEED			= 0.8;		//shock refill speed when the player is conscious
	static const float SHOCK_REFILl_UNCONSCIOUS_SPEED		= 0.28;		//shock refill speed when the player is unconscious
	
	
	// Metabolic
	static const float SL_ENERGY_CRITICAL = 0;
	static const float SL_ENERGY_LOW = 1000;
	static const float SL_ENERGY_NORMAL = 2000;
	static const float SL_ENERGY_HIGH = 2800;
	static const float LOW_ENERGY_THRESHOLD = 0.01;
	
	static const float METABOLIC_SPEED_ENERGY_BASAL		= 0.01;		//energy loss per second while idle	
	static const float METABOLIC_SPEED_ENERGY_WALK		= 0.02;		//energy loss per second
	static const float METABOLIC_SPEED_ENERGY_JOG		= 0.10;		//energy loss per second
	static const float METABOLIC_SPEED_ENERGY_SPRINT	= 0.20;		//energy loss per second
	
	// Water
	static const float SL_WATER_CRITICAL = 0;
	static const float SL_WATER_LOW = 500;
	static const float SL_WATER_NORMAL = 1000;
	static const float SL_WATER_HIGH = 1300;
	static const float LOW_WATER_THRESHOLD = 0.01;

	static const float METABOLIC_SPEED_WATER_BASAL		= 0.01;		//water loss per second while idle	
	static const float METABOLIC_SPEED_WATER_WALK		= 0.03;		//water loss per second
	static const float METABOLIC_SPEED_WATER_JOG		= 0.15;		//water loss per second
	static const float METABOLIC_SPEED_WATER_SPRINT		= 0.30;		//water loss per second
	
	static const float HEALTH_LOSS_HC_PLUS_LOW				= 0.01;
	static const float HEALTH_LOSS_HC_PLUS_HIGH				= 0.05;			
	static const float HEALTH_LOSS_HC_MINUS_LOW				= 0.05;
	static const float HEALTH_LOSS_HC_MINUS_HIGH 			= 0.10;	
};

modded class GameConstants
{
	const int 	STAMINA_DRAIN_STANDING_SPRINT_PER_SEC = 7; //in units (how much sprint depletes stamina)
	const int 	STAMINA_DRAIN_CROUCHED_SPRINT_PER_SEC = 5; //in units (how much sprint in crouch depletes stamina)
	const int 	STAMINA_DRAIN_PRONE_SPRINT_PER_SEC = 4; //in units (how much sprint in prone depletes stamina)
	const int	STAMINA_DRAIN_SWIM_FAST_PER_SEC = 6; //in units (how much fast swimming depletes stamina)
	const int	STAMINA_DRAIN_LADDER_FAST_PER_SEC = 6; //in units (how much fast ladder climb depletes stamina)
	
	const float	STAMINA_DRAIN_HOLD_BREATH_START = 0.4; //in units (how much holding breath depletes stamina at the start)
	const float	STAMINA_DRAIN_HOLD_BREATH_END = 1.0; //in units (how much holding breath depletes stamina at the end)
	const float	STAMINA_DRAIN_JUMP = 30;		// in units (how much jumping depletes stamina)
	const float	STAMINA_DRAIN_VAULT = 20;		// in units (how much jumping depletes stamina)
	const float	STAMINA_DRAIN_CLIMB = 60;		// in units (how much jumping depletes stamina)
	const float	STAMINA_DRAIN_MELEE_LIGHT = 10; //in units (how much light melee punch depletes stamina)
	const float	STAMINA_DRAIN_MELEE_HEAVY = 40; //in units (how much heavy melee punch depletes stamina)
	const float	STAMINA_DRAIN_MELEE_EVADE = 15; // in units (how much evade depletes stamina)
	
	const float STAMINA_DRAIN_HOLD_BREATH_DURATION = 1.0; //in seconds, time it takes to increase stamina drain from STAMINA_DRAIN_HOLD_BREATH_START to STAMINA_DRAIN_HOLD_BREATH_END
	const float	STAMINA_DRAIN_HOLD_BREATH_EXPONENT = 4.0; //holding breath exponent
	
	const int 	STAMINA_GAIN_JOG_PER_SEC = 1.0; //in units (how much of stamina units is gained while jogging)
	const int 	STAMINA_GAIN_WALK_PER_SEC = 1.5; //in units (how much of stamina units is gained while walking)
	const int 	STAMINA_GAIN_IDLE_PER_SEC = 4; //in units (how much of stamina units is gained while iddling)
	const int	STAMINA_GAIN_SWIM_PER_SEC = 0.8; //in units (how much of stamina units is gained while slowly swim)
	const int	STAMINA_GAIN_LADDER_PER_SEC = 0.8; //in units (how much of stamina units is gained while slowly swim)
	const float STAMINA_GAIN_BONUS_CAP = 0.01; //in units (tells how much extra units can be added at best to stamina regain)
	
	const float STAMINA_KG_TO_STAMINAPERCENT_PENALTY = 1.8; //in units (by how many  units is max stamina bar reduced for each 1 kg of load weight)
	const float STAMINA_MIN_CAP = 5; //in units (overload won't reduce max stamina bar under this value)
	const float STAMINA_HOLD_BREATH_THRESHOLD_ACTIVATE = 10; // in units
	const float STAMINA_HOLD_BREATH_THRESHOLD_DRAIN = 0; // in units
	const float STAMINA_JUMP_THRESHOLD = STAMINA_DRAIN_JUMP; // in units
	const float STAMINA_VAULT_THRESHOLD = STAMINA_DRAIN_VAULT; // in units
	const float STAMINA_CLIMB_THRESHOLD = STAMINA_DRAIN_CLIMB; // in units
	
	
	const float STAMINA_MELEE_HEAVY_THRESHOLD = STAMINA_DRAIN_MELEE_HEAVY; // in units (how many units we need to make a heavy hit in melee)
	const float STAMINA_MELEE_EVADE_THRESHOLD = 8; // in units
	const float STAMINA_REGEN_COOLDOWN_DEPLETION = 3; // in secs (how much time we will spend in cooldown before the stamina will starts with regeneration)
	const float STAMINA_REGEN_COOLDOWN_EXHAUSTION = 5;
	const float STAMINA_WEIGHT_LIMIT_THRESHOLD = 5000; //! in grams (weight where the player is not penalized by stamina)
	const float STAMINA_KG_TO_GRAMS = 1000; //for kg to g conversion
	const float STAMINA_SYNC_RATE = 1; //in secs
	const float STAMINA_MAX = 100;
	
	const float TEMPERATURE_RATE_COOLING_INSIDE = -0.18;
	const float TEMPERATURE_RATE_COOLING_GROUND = -0.20;
	const float TEMPERATURE_RATE_COOLING_PLAYER = 0; // disabled for correct calculation
	const float ENVIRO_ITEM_HEAT_TRANSFER_COEF = 0.025;
	const float TEMPERATURE_ITEM_HEAT_TRANSFER_COEF = 0.05;
	const float TEMPERATURE_ITEMS_HEAT_IN_INVENTORY_FROM_BODY = 26;
	const float ENVIRO_FIRE_INCREMENT = 0.001;	
	const float ENVIRO_DRY_INCREMENT = 0.000005;
	const float ENVIRO_WIND_EFFECT = 0.05;
};
