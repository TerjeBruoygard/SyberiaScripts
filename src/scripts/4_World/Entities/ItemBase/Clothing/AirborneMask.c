modded class AirborneMask
{
	override void EEInit()
	{
		super.EEInit();
		
		UpdateVisualStyleLater();
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		UpdateVisualStyle();
	}	
	
    override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		UpdateVisualStyle();
	}
	
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		
		UpdateVisualStyle();
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		
		UpdateVisualStyle();
	}
	
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		
		UpdateVisualStyle();
	}
	
	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent, slot_id);
		
		UpdateVisualStyle();
	}
	
	void UpdateVisualStyleLater()
	{
		if (GetGame().IsClient())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateVisualStyle, 1000, false);
		}
	}
	
	void UpdateVisualStyle()
	{
		if (GetGame().IsClient())
		{
			TStringArray textures = GetHiddenSelectionsTextures();
			if (FindAttachmentBySlotName("GasMaskFilter"))
			{				
        		SetObjectTexture(3, textures.Get(5));
			}
			else
            {
        		SetObjectTexture(3, textures.Get(3));
            }
		}
	}
};