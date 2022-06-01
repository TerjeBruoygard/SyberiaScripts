modded class ModItemRegisterCallbacks
{
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterOneHanded(pType, pBehavior);
		
		pType.AddItemInHandsProfileIK("TabletsBase", "dz/anims/workspaces/player/player_main/props/player_main_1h_tablets.asi", pBehavior, "dz/anims/anm/player/ik/gear/charcoal_tablets.anm");
		pType.AddItemInHandsProfileIK("SyberiaMedicineAmpoule", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/InjectionVial.anm");
		pType.AddItemInHandsProfileIK("SyringeEmpty", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/Syringe_Empty.anm");
		pType.AddItemInHandsProfileIK("SyringeFull", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/Syringe_Full.anm");
		pType.AddItemInHandsProfileIK("InjectorBase", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior, "dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("BandageHemostatic", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/StartKit.anm");
		pType.AddItemInHandsProfileIK("SurgicalKit",  "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/sewing_kit.anm");
		pType.AddItemInHandsProfileIK("SalveBase", "dz/anims/workspaces/player/player_main/props/player_main_1h_pills.asi", pBehavior, "dz/anims/anm/player/ik/gear/VitaminBottle.anm");
        pType.AddItemInHandsProfileIK("ItemPDA", "dz/anims/workspaces/player/player_main/props/player_main_1h_compass.asi", pBehavior,	"dz/anims/anm/player/ik/gear/compass_modern.anm");
		pType.AddItemInHandsProfileIK("Stethoscope", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "dz/anims/anm/player/ik/gear/steak_knife.anm");
        pType.AddItemInHandsProfileIK("MedContainerSmall", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/first_aid_kit.anm");
        pType.AddItemInHandsProfileIK("MedContainerMedium", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "dz/anims/anm/player/ik/gear/screwdriver.anm");
        pType.AddItemInHandsProfileIK("MedContainerLarge", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_knife.asi", pBehavior, "dz/anims/anm/player/ik/gear/screwdriver.anm");
	}
	
	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterTwoHanded(pType, pBehavior);
	
		pType.AddItemInHandsProfileIK("SleepingBag_BaseColor", "dz/anims/workspaces/player/player_main/weapons/player_main_2h_extinguisher.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/WaterproofBag.anm");	
	}
};
