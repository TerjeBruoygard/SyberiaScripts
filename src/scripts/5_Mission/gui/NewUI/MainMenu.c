modded class MainMenu
{
	override void OnShow()
	{
		super.OnShow();
		if (m_Version) m_Version.Show(false);
		if (m_ModdedWarning) m_ModdedWarning.Show(false);
		if (m_DlcFrame) m_DlcFrame.Show(false);
		if (m_ModdedWarning) m_ModdedWarning.Show(false);
		
		Widget modsDetailed = layoutRoot.FindAnyWidget("ModsDetailed");
		if (modsDetailed) modsDetailed.Show(false);
		
		Widget modsSimple = layoutRoot.FindAnyWidget("ModsSimple");
		if (modsSimple) modsSimple.Show(false);
	}
};