class ScreenNewchar extends ScreenBase
{
	bool m_updateFacePreview = false;
	ref RpcNewCharContainer m_metadata;
	
	const int m_maxNameLength = 16;
	
	ref XComboBoxWidget m_genderSelector;
	ref XComboBoxWidget m_faceSelector;
	ref ImageWidget m_playerPreview;
	ref ButtonWidget m_NextBtn;	
	ref MultilineTextWidget m_nameHintBox;
	
	ref TextWidget m_totalScore;
	
	ref TextWidget m_charNameText1;
	ref TextWidget m_charNameText2;
	ref EditBoxWidget m_charNameEdit1;
	ref EditBoxWidget m_charNameEdit2;
	
	bool m_isRpcError = false;
	bool m_isRpcSended = false;
	int m_currentScore = 0;
	
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
		m_nameHintBox = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "NameHintBox" ) );
		m_NextBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "NextBtn" ) );
		
		m_charNameEdit1 = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "CharNameEdit1" ) );
		m_charNameEdit2 = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "CharNameEdit2" ) );
		m_charNameText1 = TextWidget.Cast( layoutRoot.FindAnyWidget( "CharNameText1" ) );	
		m_charNameText2 = TextWidget.Cast( layoutRoot.FindAnyWidget( "CharNameText2" ) );		
		m_totalScore = TextWidget.Cast( layoutRoot.FindAnyWidget( "TotalScore" ) );
		
        return layoutRoot;
    }
	
	override void OnShow()
	{
		super.OnShow();
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
		
		if (m_isRpcError)
		{
			m_isRpcError = false;
			m_isRpcSended = false;
			m_nameHintBox.SetText("#syb_name_already_exist");
			return;
		}
		
		if (m_isRpcSended)
		{
			m_NextBtn.Enable(false);
			return;
		}
		
		if (m_updateFacePreview)
		{
			m_updateFacePreview = false;
			UpdatePlayerPreview();
		}
		
		string fname = CharacterMetadata.FormatNamePart(m_charNameEdit1.GetText());
		string sname = CharacterMetadata.FormatNamePart(m_charNameEdit2.GetText());
		m_charNameText1.SetText(fname);
		m_charNameText2.SetText(sname);
		
		m_NextBtn.Enable(m_currentScore >= 0 && CharacterMetadata.ValidateCharacterNamePart(fname) && CharacterMetadata.ValidateCharacterNamePart(sname));
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		bool result = super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{			
			if (w == m_NextBtn)
			{
				string fname = CharacterMetadata.FormatNamePart(m_charNameEdit1.GetText());
				string sname = CharacterMetadata.FormatNamePart(m_charNameEdit2.GetText());				
				if (m_currentScore >= 0 && CharacterMetadata.ValidateCharacterNamePart(fname) && CharacterMetadata.ValidateCharacterNamePart(sname))
				{
					m_isRpcSended = true;
					
					ref RpcCreateNewCharContainer requestParams = new RpcCreateNewCharContainer();
					requestParams.m_name = fname + " " + sname;
					requestParams.m_isMale = (m_genderSelector.GetCurrentItem() == 0);
					requestParams.m_faceId = m_faceSelector.GetCurrentItem();					
					requestParams.m_skills = m_metadata.m_skills;
										
					GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_CREATENEWCHAR_REQUEST, new Param1<ref RpcCreateNewCharContainer>(requestParams));
					delete requestParams;
				}
				
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
		
		return result;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		bool result = super.OnChange(w, x, y, finished);
	
		string text;
		if (w.GetName() == m_charNameEdit1.GetName()) {			
			text = m_charNameEdit1.GetText();
			if (text.LengthUtf8() > m_maxNameLength) {
				m_charNameEdit1.SetText(text.Substring(0, m_maxNameLength));
			}
			
			return true;
		}
		if (w.GetName() == m_charNameEdit2.GetName()) {			
			text = m_charNameEdit2.GetText();
			if (text.LengthUtf8() > m_maxNameLength) {
				m_charNameEdit2.SetText(text.Substring(0, m_maxNameLength));
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
		
		return result;
	}
	
	override bool OnKeyPress(Widget w, int x, int y, int key) {
		string text;
		
		if (w.GetName() == m_charNameEdit1.GetName()) {
			text = m_charNameEdit1.GetText();
			if (text.LengthUtf8() > m_maxNameLength) {
				return true;
			}
		}
		
		if (w.GetName() == m_charNameEdit2.GetName()) {
			text = m_charNameEdit2.GetText();
			if (text.LengthUtf8() > m_maxNameLength) {
				return true;
			}
		}

		return false;
	}
}