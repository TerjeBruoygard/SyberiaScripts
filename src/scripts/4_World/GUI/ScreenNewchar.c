class ScreenNewchar extends ScreenBase
{
	bool m_updateFacePreview = false;
	bool m_updateSkills = false;
	ref RpcNewCharContainer m_metadata;
	
	const int m_maxNameLength = 16;
	
	ref XComboBoxWidget m_genderSelector;
	ref XComboBoxWidget m_faceSelector;
	ref ImageWidget m_playerPreview;
	ref ButtonWidget m_NextBtn;	
	ref MultilineTextWidget m_nameHintBox;
	ref TextWidget m_charNameText1;
	ref TextWidget m_charNameText2;
	ref EditBoxWidget m_charNameEdit1;
	ref EditBoxWidget m_charNameEdit2;
	
	ref TextWidget m_totalScore;
	ref TextListboxWidget m_skillsList;
	ref TextWidget m_currentSkillName;
	ref MultilineTextWidget m_currentSkillDesc;
	ref ButtonWidget m_currentSkillInc, m_currentSkillDec;
	
	bool m_isRpcError = false;
	bool m_isRpcSended = false;
	int m_currentScore = 0;
	
	void ScreenNewchar(ref RpcNewCharContainer metadata)
	{
		m_metadata = metadata;
	}
	
	void ~ScreenNewchar()
	{
		if (m_metadata) delete m_metadata;
	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenNewchar.layout" );
		
		m_genderSelector = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "GenderSelector" ) );
		m_faceSelector = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "FaceSelector" ) );	
		m_playerPreview = ImageWidget.Cast( layoutRoot.FindAnyWidget( "PlayerPreview" ) );		
		m_nameHintBox = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "NameHintBox" ) );
		m_charNameEdit1 = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "CharNameEdit1" ) );
		m_charNameEdit2 = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "CharNameEdit2" ) );
		m_charNameText1 = TextWidget.Cast( layoutRoot.FindAnyWidget( "CharNameText1" ) );	
		m_charNameText2 = TextWidget.Cast( layoutRoot.FindAnyWidget( "CharNameText2" ) );	
		m_NextBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "NextBtn" ) );
			
		m_totalScore = TextWidget.Cast( layoutRoot.FindAnyWidget( "TotalScore" ) );
		m_skillsList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "SkillsList" ) );
		m_currentSkillName = TextWidget.Cast( layoutRoot.FindAnyWidget( "CurrentSkillName" ) );
		m_currentSkillDesc = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "CurrentSkillDesc" ) );
		m_currentSkillInc = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "CurrentSkillInc" ) );
		m_currentSkillDec = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "CurrentSkillDec" ) );
		
        return layoutRoot;
    }
	
	override void OnShow()
	{
		super.OnShow();
		m_updateFacePreview = true;
		m_updateSkills = true;
	}

	private void UpdateSkillsPreview()
	{
		int currentScore = m_metadata.m_score - (int)m_metadata.m_skills.GetTotalScore();
		m_totalScore.SetText("#syb_totalpoints " + currentScore);
		
		int currentSelection = m_skillsList.GetSelectedRow();		
		m_skillsList.ClearItems();
		for (int q = 0; q < SYBERIA_ENABLED_SKILLS_COUNT; ++q)
		{
			int i = SYBERIA_ENABLED_SKILLS_LIST[q];
			int currentSkillValue = (int)m_metadata.m_skills.GetSkillValue(i);
			int rowId = m_skillsList.AddItem("#syb_skill" + i, null, 0);
			m_skillsList.SetItem(rowId, currentSkillValue.ToString(), null, 1);
		}
		
		if (currentSelection < 0)
		{
			currentSelection = 0;
		}
		
		int selectedSkillValue = (int)m_metadata.m_skills.GetSkillValue(SYBERIA_ENABLED_SKILLS_LIST[currentSelection]);
		m_skillsList.SelectRow(currentSelection);
		m_currentSkillName.SetText( "#syb_skill" + SYBERIA_ENABLED_SKILLS_LIST[currentSelection] + ": " + selectedSkillValue );
		m_currentSkillDesc.SetText( "#syb_skill_desc" + SYBERIA_ENABLED_SKILLS_LIST[currentSelection] );
		m_currentSkillInc.GetParent().Show( currentScore > 0 && selectedSkillValue < 100 );
		m_currentSkillDec.GetParent().Show( selectedSkillValue > 0 );
	}
	
	private void UpdatePlayerPreview()
	{
		bool isMale = (m_genderSelector.GetCurrentItem() == 0);
		int faceId = m_faceSelector.GetCurrentItem();

		ref array<ref CharacterMetadata> faces;
		if (isMale) 
		{
			faces = m_metadata.m_maleCharsMetadata;
		}
		else 
		{
			faces = m_metadata.m_femaleCharsMetadata;
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
		
		ref CharacterMetadata currentFace = faces.Get(faceId);
		m_playerPreview.LoadImageFile(0, currentFace.m_facelogo);
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
		
		if (m_updateSkills)
		{
			m_updateSkills = false;
			UpdateSkillsPreview();
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
					//delete requestParams;
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
			if (w == m_currentSkillInc && m_skillsList.GetSelectedRow() >= 0)
			{
				m_metadata.m_skills.AddSkillValue( SYBERIA_ENABLED_SKILLS_LIST[m_skillsList.GetSelectedRow()], 1 );
				m_updateSkills = true;
				return true;
			}
			if (w == m_currentSkillDec && m_skillsList.GetSelectedRow() >= 0)
			{
				m_metadata.m_skills.AddSkillValue( SYBERIA_ENABLED_SKILLS_LIST[m_skillsList.GetSelectedRow()], -1 );
				m_updateSkills = true;
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
				m_charNameEdit1.SetText(text.SubstringUtf8(0, m_maxNameLength));
			}
			
			return true;
		}
		if (w.GetName() == m_charNameEdit2.GetName()) {			
			text = m_charNameEdit2.GetText();
			if (text.LengthUtf8() > m_maxNameLength) {
				m_charNameEdit2.SetText(text.SubstringUtf8(0, m_maxNameLength));
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
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int  column,	int  oldRow, int  oldColumn)
	{
		if (w == m_skillsList)
		{
			if (row != oldRow)
			{
				m_updateSkills = true;	
			}
		}
		
		return super.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
	}
}