modded class MainMenu
{
	override void OnShow()
	{
		super.OnShow();
		if (m_Version) m_Version.Show(false);
		if (m_ModdedWarning) m_ModdedWarning.Show(false);
	}
};