modded class ItemActionsWidget
{
    override protected void Update()
	{
		if (!g_Game || !m_Hud)
		{
			return; // Fix null reference exception
		}
		
		super.Update();
	}
}