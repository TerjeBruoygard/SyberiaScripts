class AuthSystem
{
    allowedLettersInName[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
};

class SleepingSystem
{
    // Client
    sleepingMaxValue = 14000;
    sleepingLevel5 = 100;
    sleepingLevel4 = 1000;
    sleepingLevel3 = 6000;
    sleepingLevel2 = 10000;
    
    // Server
    sleepingDecPerSec = 1;
    sleepingUnconsionEnabled = 0;
    sleepingIncPerUnconsionBoostValue = 5;
    sleepingIncPerUnconsionBoostTime = 30;
    sleepingIncPerSleepingLvl1Sec = 10;
    sleepingIncPerSleepingLvl2Sec = 20;
    sleepingHealPerSec01 = 0.002;
    sleepingHealInfluenzaChance = 0.01;
};

class MindstateSystem
{
    mindstateMaxValue = 100;
    mindstateLevel5 = 1.0;
    mindstateLevel4 = 20.0;
    mindstateLevel3 = 60.0;
    mindstateLevel2 = 90.0;
};

class MedicineSystem
{
    sepsisStage1TimeSec = 600;
    sepsisStage2TimeSec = 2400;
    sepsisDeathTimeSec = 900;
    sepsisHighTemperatureValue = 42;
    sepsisZombieHitChance = 0.04;
    sepsisKnifeHitChance = 0.04;
    sepsisBulletHitChance = 0.05;
    sepsisDirtySyringeChance = 0.75;
    sepsisDitryHandsBandageChance = 0.4;
    sepsisDitryHandsSyrgeryChance = 0.9;
    zvirusStage1TimeSec = 1200; // 20 min
    zvirusStage2TimeSec = 3600; // zvirusStage1TimeSec + 40 min
    zvirusDeathTimeSec = 900;
    zvirusBloodRegenPerSec = 4;
    zvirusZombieHitChance = 0.2;
    zvirusZombieBloodTransferChance = 0.1;
    zvirusAntidotBloodDmg01 = 0.15;
    zvirusAntidotHealthDmg01 = 0.2;
    painLvl1TimeSec = 300;
    painLvl2TimeSec = 900;
    painLvl3TimeSec = 1800;
    painMaxDurationSec = 2400;
    bleedingBullethitHealthlosePerSecond = 0.003;
    bleedingBullethitOpenPerSecond = 5;
    bleedingBullethitCupd1PerSecond = 0.3;
    bleedingBullethitCupd2PerSecond = 0.1;
    bleedingBullethitRemoveBandagedTimeSec = -1; // DISABLED
    bleedingKnifehitHealthlosePerSecond = 0.003;
    bleedingKnifehitOpenPerSecond = 6;
    bleedingKnifehitCupd1PerSecond = 0.35;
    bleedingKnifehitCupd2PerSecond = 0.1;
    bleedingKnifehitRemoveBandagedTimeSec = 1800;
    bleedingVisceraBloodlosePerSecond = 3;
    bleedingVisceraHealthlosePerSecond = 0.005;
    bleedingHematomaBloodlosePerSecond = 0;
    bleedingHematomaHealthlosePerSecond = 0.002;
    bleedingZombieHitChance = 0.3;
    hematomaPlayerhandsHitChance = 0.6;
    hematomaZombieHitChance = 0.7;
    hematomaRegenTimerSec = 600;
    hematomaRegenTimeBoostOnSalve = 8;
    hematomaPainChance = 0.5;
    cuthitRegenTimerSec = 300;
    visceraKnifehitTorsoChance = 0.4;
    visceraBullethitTorsoChance = 0.3;
    concussionRegenTimeSec = 1800; //30 min
    hemostaticEffectModifier = 0.4; // 40% of total bloodlose
    hematopoiesisEffectBloodPerSec = 5;
    adrenalinEffectShockUpPerSec[] = { 0.01666, 0.03333, 0.2 };
    adrenalinEffectStaminaDepletionMod[] = { 0.5, 0.25, 0.1 };
    overdoseDecrementPerSec = 0.001;
    overdoseUnconChangePerSec = 0.025;
    mindstateHealPerSec = 0.04;
    mindstateEmptyDeadtimeSec = 600;
    influenzaIncubatePeriodsSec[] = { 300, 1500, 1800 };
    influenzaTemperatureLevels[] = { -1.0, 37.0, 40.0 };
    influenzaSympthomChance[] = { 0.02, 0.04, 0.08 };
    influenzaDeathTime[] = {0, 0, 900};
    influenzaApplyOnColdWarnChance = 0.0003;
    influenzaApplyOnColdCritChance = 0.001;
    antibioticsGlobalEffectivityModifier = 0.006;
    stomatchpoisonVomitChance[] = { 0.008333, 0.016666, 0.033333 };
    stomatchpoisonWaterDrainFromVomit[] = { 100, 300, 500 };
    stomatchpoisonEnergyDrainFromVomit[] = { 150, 400, 1000 };
    stomatchhealModifier = 10;
    stomatchpoisonRawMeat[] = { 1, 300 }; // level, seconds * amount
    stomatchpoisonBurnedMeat[] = { 1, 300 }; // level, seconds * amount
    stomatchpoisonRottenMeat[] = { 2, 300 }; // level, seconds * amount
    stomatchpoisonBurnedFood[] = { 1, 300 }; // level, seconds * amount
    stomatchpoisonRottenFood[] = { 2, 300 }; // level, seconds * amount
    stomatchpoisonDirtyHands[] = { 1, 300 }; // level, seconds * amount
    stomatchpoisonInfection[] = { 1, 300 }; // level, seconds * amount
    stomatchpoisonChanceDrinkPond = 0.8;
    stomatchpoisonDrinkPond[] = { 1, 120 };
    stomatchpoisonChanceDrinkWell = 0.01;
    stomatchpoisonDrinkWell[] = { 1, 60 };
    stomatchpoisonDefaultTimes[] = { 1800, 900, 600 }; // lvl1, lvl2, lvl3
    glovesDamageOnApplyBandage = -5;
    glovesDamageOnSurgery = -15;
};

class AttackSystem
{
    damageNonWeaponItemInHandsOnAttack = 3.0;
    damageGlovesOnHandsOnAttack = 2.0;
    damageHandsOnAttackChance = 0.20;
};

class ZombieSystem
{
    zombieOpenDoorEnable = 1;
    zombieOpenDoorDistance = 1.8;
    zombieFindHouseDistance = 20.0;
};

class IngameSystem
{
    bookPagesCountToCut = 10;
};

class SkillsExperienceSystem
{
    skillsExpImmunityPain = 5;
    skillsExpImmunityHematoma = 5;
    skillsExpImmunityInfluenza = 50;
    skillsExpImmunityStomatch = 80;
    skillsExpImmunityZVirus = 250;
    skillsExpImmunitySepsis = 200;
    skillsExpImmunityOverdose = 10;
    
    skillsExpAthleticsSprintTime = 60;
    skillsExpAthleticsSprintIncrement = 10;
};