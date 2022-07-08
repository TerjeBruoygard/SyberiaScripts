modded class GP5GasMask
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
			int texIndex = 0;
			if (FindAttachmentBySlotName("GasMaskFilter"))
			{
				texIndex = 3;
			}
			
			SetVisualStyle(texIndex);
		}
	}
	
	void SetVisualStyle(int id)
	{
		TStringArray textures = GetHiddenSelectionsTextures();
		SetObjectTexture(0, textures.Get(id + 0));
		SetObjectTexture(1, textures.Get(id + 1));
		SetObjectTexture(2, textures.Get(id + 2));
	}
};