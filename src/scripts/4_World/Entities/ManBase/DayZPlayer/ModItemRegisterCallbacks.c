modded class ModItemRegisterCallbacks
{
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterOneHanded(pType, pBehavior);
		
		pType.AddItemInHandsProfileIK("TabletsBase", "dz/anims/workspaces/player/player_main/props/player_main_1h_tablets.asi", pBehavior, "dz/anims/anm/player/ik/gear/charcoal_tablets.anm");
		pType.AddItemInHandsProfileIK("SyberiaMedicineAmpoule", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,	"dz/anims/anm/player/ik/gear/InjectionVial.anm");
		pType.AddItemInHandsProfileIK("SyringeEmpty", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/Syringe_Empty.anm");
		pType.AddItemInHandsProfileIK("SyringeDirty", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/Syringe_Empty.anm");
		pType.AddItemInHandsProfileIK("SyringeFull", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior,	"dz/anims/anm/player/ik/gear/Syringe_Full.anm");

	}
};