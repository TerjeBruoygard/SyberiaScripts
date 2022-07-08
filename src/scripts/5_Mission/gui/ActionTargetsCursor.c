modded class ActionTargetsCursor
{
	protected override void SetItemDesc(string descText, int cargoCount, string itemWidget, string descWidget)
	{
		if (m_Target && m_Target.GetObject() && m_Target.GetObject().IsInherited(ZombieBase))
		{
			// Hide "+" when looting zombies
			cargoCount = 0;
		}
		
		super.SetItemDesc(descText, cargoCount, itemWidget, descWidget);
	}
}