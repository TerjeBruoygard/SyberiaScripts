class ScreenNewchar extends ScreenBase
{
	bool m_updateFacePreview = false;
	ref RpcNewCharContainer m_metadata;
	
	const int m_maxNameLength = 32;
	
	ref XComboBoxWidget m_genderSelector;
	ref XComboBoxWidget m_faceSelector;
	ref ImageWidget m_playerPreview;
	ref EditBoxWidget m_charNameEdit;
	ref ButtonWidget m_NextBtn;
	
	bool m_isRpcSended = false;
	
	void ScreenNewchar(ref RpcNewCharContainer metadata)
	{
		m_metadata = metadata;
	}
	
	void ~ScreenNewchar()
	{
		delete m_metadata;
	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenNewchar.layout" );
		m_genderSelector = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "GenderSelector" ) );
		m_faceSelector = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "FaceSelector" ) );	
		m_playerPreview = ImageWidget.Cast( layoutRoot.FindAnyWidget( "PlayerPreview" ) );	
		m_charNameEdit = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "CharNameEdit" ) );	
		m_NextBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "NextBtn" ) );
        return layoutRoot;
    }
	
	override void OnShow()
	{
		super.OnShow();
		m_charNameEdit.SetText(m_metadata.m_name);
		m_updateFacePreview = true;
	}

	private void UpdatePlayerPreview()
	{
		bool isMale = (m_genderSelector.GetCurrentItem() == 0);
		int faceId = m_faceSelector.GetCurrentItem();
		string prefix = "";
		
		ref array<ref CharacterMetadata> faces;
		if (isMale) 
		{
			faces = m_metadata.m_maleCharsMetadata;
			prefix = "m";
		}
		else 
		{
			faces = m_metadata.m_femaleCharsMetadata;
			prefix = "f";
		}
		
		if (faceId >= faces.Count())
		{
			faceId = 0;
		}
		
		m_faceSelector.ClearAll();
		for (int i = 0; i < faces.Count(); i++)
		{
			int visuaId = i + 1;
			m_faceSelector.AddItem("" + visuaId);
		}
		
		string texPath = "SyberiaScripts\\data\\faces\\" + prefix + faceId + ".paa";
		m_playerPreview.LoadImageFile(0, texPath);
		m_faceSelector.SetCurrentItem(faceId);
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_updateFacePreview)
		{
			m_updateFacePreview = false;
			UpdatePlayerPreview();
		}
		
		if (m_isRpcSended)
		{
			m_NextBtn.Show(false);
		}
		
		m_NextBtn.Show(m_charNameEdit.GetText().LengthUtf8() == 0 || (m_charNameEdit.GetText().LengthUtf8() >= 4 && m_charNameEdit.GetText().LengthUtf8() <= m_maxNameLength) );
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{			
			if (w == m_NextBtn)
			{
				m_isRpcSended = true;
				
				ref RpcCreateNewCharContainer requestParams = new RpcCreateNewCharContainer();
				requestParams.m_name = m_charNameEdit.GetText();
				requestParams.m_isMale = (m_genderSelector.GetCurrentItem() == 0);
				requestParams.m_faceId = m_faceSelector.GetCurrentItem();
				
				GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_CREATENEWCHAR_REQUEST, new Param1<ref RpcCreateNewCharContainer>(requestParams));
				delete requestParams;
				return true;
			}
			if (w == m_faceSelector)
			{
				m_updateFacePreview = true;
				return true;
			}
			if (w == m_genderSelector)
			{
				m_updateFacePreview = true;
				return true;
			}
		}
		
		return false;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		super.OnChange(w, x, y, finished);
	
		string text;
		if (w.GetName() == m_charNameEdit.GetName()) {			
			text = m_charNameEdit.GetText();
			if (text.LengthUtf8() > m_maxNameLength) {
				m_charNameEdit.SetText(text.Substring(0, m_maxNameLength));
			}
			
			return true;
		}
		if (w.GetName() == m_genderSelector.GetName())
		{
			m_updateFacePreview = true;
			return true;
		}
		if (w.GetName() == m_faceSelector.GetName())
		{
			m_updateFacePreview = true;
			return true;
		}
		
		return false;
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key) {
		string text;
		
		if (w.GetName() == m_charNameEdit.GetName()) {
			text = m_charNameEdit.GetText();
			if (text.LengthUtf8() >= m_maxNameLength) {
				return true;
			}
		}

		return false;
	}
}