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
    sleepingHealInfluenzaChance = 0.0025;
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
    sepsisStage1TimeSec = 60 * 10;
    sepsisStage2TimeSec = 60 * 40;
    sepsisDeathTimeSec = 60 * 15;
    sepsisHighTemperatureValue = 42;
    sepsisZombieHitChance = 0.04;
    sepsisKnifeHitChance = 0.04;
    sepsisBulletHitChance = 0.05;
    sepsisDirtySyringeChance = 0.6;
    sepsisDitryHandsBandageChance = 0.2;
    sepsisDitryHandsSyrgeryChance = 0.8;
    zvirusStage1TimeSec = 20 * 60; // 20 min
    zvirusStage2TimeSec = 60 * 60; // zvirusStage1TimeSec + 40 min
    zvirusDeathTimeSec = 60 * 15;
    zvirusBloodRegenPerSec = 4;
    zvirusZombieHitChance = 0.25;
    zvirusAntidotBloodDmg01 = 0.15;
    zvirusAntidotHealthDmg01 = 0.2;
    painLvl1TimeSec = 60 * 5;
    painLvl2TimeSec = 60 * 30;
    painLvl3TimeSec = 60 * 60;
    painMaxDurationSec = 60 * 60 * 4;
    bleedingBullethitHealthlosePerSecond = 0.003;
    bleedingBullethitOpenPerSecond = 5;
    bleedingBullethitCupd1PerSecond = 0.3;
    bleedingBullethitCupd2PerSecond = 0.1;
    bleedingBullethitRemoveBandagedTimeSec = -1; // DISABLED
    bleedingKnifehitHealthlosePerSecond = 0.003;
    bleedingKnifehitOpenPerSecond = 6;
    bleedingKnifehitCupd1PerSecond = 0.35;
    bleedingKnifehitCupd2PerSecond = 0.1;
    bleedingKnifehitRemoveBandagedTimeSec = 60 * 20; // 30 min
    bleedingVisceraBloodlosePerSecond = 3;
    bleedingVisceraHealthlosePerSecond = 0.005;
    bleedingHematomaBloodlosePerSecond = 0;
    bleedingHematomaHealthlosePerSecond = 0.002;
    bleedingZombieHitChance = 0.3;
    hematomaPlayerhandsHitChance = 0.4;
    hematomaZombieHitChance = 0.7;
    hematomaRegenTimerSec = 60 * 10;
    hematomaRegenTimeBoostOnSalve = 5;
    cuthitRegenTimerSec = 60 * 5;
    visceraKnifehitTorsoChance = 0.4;
    visceraBullethitTorsoChance = 0.3;
    concussionRegenTimeSec = 60 * 30; //30 min
    hemostaticEffectModifier = 0.4; // 40% of total bloodlose
    hematopoiesisEffectBloodPerSec = 5;
    adrenalinEffectShock01Lvl1PerSec = 1 / 60;
    adrenalinEffectShock01Lvl2PerSec = 1 / 30;
    adrenalinEffectShock01Lvl3PerSec = 1 / 5;
    overdoseDecrementPerSec = 0.001;
    overdoseUnconChangePerSec = 0.025;
    mindstateHealPerSec = 0.04;
    mindstateEmptyDeadtimeSec = 10 * 60;
    influenzaIncubatePeriodsSec[] = { 60 * 5, 60 * 25, 60 * 30 };
    influenzaTemperatureLevels[] = { -1.0, 37.0, 40.0 };
    influenzaSympthomChance[] = { 0.02, 0.04, 0.08 };
    influenzaDeathTime[] = {0, 0, 60 * 15};
    influenzaApplyOnColdWarnChance = 0.0003;
    influenzaApplyOnColdCritChance = 0.001;
    antibioticsGlobalEffectivityModifier = 0.006;
    stomatchpoisonVomitChance[] = { 1 / 120, 1 / 60, 1 / 30 };
    stomatchpoisonWaterDrainFromVomit[] = { 100, 300, 500 };
    stomatchpoisonEnergyDrainFromVomit[] = { 150, 400, 1000 };
    stomatchhealModifier = 10;
    stomatchpoisonRawMeat[] = { 1, 5 * 60 }; // level, seconds * amount
    stomatchpoisonBurnedMeat[] = { 1, 5 * 60 }; // level, seconds * amount
    stomatchpoisonRottenMeat[] = { 2, 5 * 60 }; // level, seconds * amount
    stomatchpoisonBurnedFood[] = { 1, 5 * 60 }; // level, seconds * amount
    stomatchpoisonRottenFood[] = { 2, 5 * 60 }; // level, seconds * amount
    stomatchpoisonDirtyHands[] = { 1, 5 * 60 }; // level, seconds * amount
    stomatchpoisonInfection[] = { 1, 5 * 60 }; // level, seconds * amount
    stomatchpoisonChanceDrinkPond = 0.8;
    stomatchpoisonDrinkPond[] = { 1, 2 * 60 };
    stomatchpoisonChanceDrinkWell = 0.01;
    stomatchpoisonDrinkWell[] = { 1, 60 };
    stomatchpoisonDefaultTimes[] = { 30 * 60, 15 * 60, 10 * 60 }; // lvl1, lvl2, lvl3
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