class TabletsBase extends Edible_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionForceConsumeSingle);
		AddAction(ActionConsumeSingle);
	}
	
	override bool CanHaveTemperature()
	{
		return false;
	}
	
	override string GetTooltip()
	{
		string additionalText = "";
		PlayerBase sourcePlayer = PlayerBase.Cast( GetHierarchyRootPlayer() );
		if (sourcePlayer && sourcePlayer.GetPerkBoolValue(SyberiaPerkType.SYBPERK_MEDICINE_TABLETS_RESEARCH))
		{
			array<string> effects = new array<string>;
			GameHelpers.GetMedicineItemVisualEffects(GetType(), effects);
			if (effects.Count() > 0)
			{
				additionalText = " #syb_med_research ";
				for (int i = 0; i < effects.Count(); i++)
				{
					if (i > 0) additionalText = additionalText + ", ";
					additionalText = additionalText + effects.Get(i);
				}
			}
		}
		
		return super.GetTooltip() + additionalText;
	}
};