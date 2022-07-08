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
	ref TextListboxWidget m_skillsResult;
	
	ref TextListboxWidget m_perksTotal;
	ref TextListboxWidget m_perksUsed;
	ref TextWidget m_totalScore;
	ref TextWidget m_perkDesc;
	ref ButtonWidget m_addPerkBtn;
	ref ButtonWidget m_delPerkBtn;
	
	bool m_isRpcSended = false;
	bool m_updatePerks = false;
	int m_currentScore = 0;
	
	ref array<ref PerkDescription> m_allPerksDesc;
	ref array<int> m_usedPerks;
	
	void ScreenNewchar(ref RpcNewCharContainer metadata)
	{
		m_metadata = metadata;
		
		m_allPerksDesc = new array<ref PerkDescription>;
		GetPerkDescriptions(m_allPerksDesc);
		
		m_usedPerks = new array<int>();
	}
	
	void ~ScreenNewchar()
	{
		delete m_metadata;
		delete m_allPerksDesc;
		delete m_usedPerks;
	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenNewchar.layout" );
		m_genderSelector = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "GenderSelector" ) );
		m_faceSelector = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "FaceSelector" ) );	
		m_playerPreview = ImageWidget.Cast( layoutRoot.FindAnyWidget( "PlayerPreview" ) );	
		m_charNameEdit = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "CharNameEdit" ) );	
		m_skillsResult = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "SkillsResult" ) );
		m_NextBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "NextBtn" ) );
		
		m_perksTotal = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "TotalPerksList" ) );
		m_perksUsed = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "UsedPerksList" ) );
		m_totalScore = TextWidget.Cast( layoutRoot.FindAnyWidget( "TotalScore" ) );
		m_perkDesc = TextWidget.Cast( layoutRoot.FindAnyWidget( "PerkDesc" ) );
		m_addPerkBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "AddPerk" ) );
		m_delPerkBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "DelPerk" ) );
		
        return layoutRoot;
    }
	
	override void OnShow()
	{
		super.OnShow();
		m_charNameEdit.SetText(m_metadata.m_name);
		m_updateFacePreview = true;
		m_updatePerks = true;
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
	
	private void UpdatePerks()
	{		
		int rowId;
		ref array<ref PerkDescription> sortedPerks = new array<ref PerkDescription>;
		foreach (ref PerkDescription perkDesc : m_allPerksDesc)
		{
			bool isAdded = false;
			for (int i = 0; i < sortedPerks.Count() && !isAdded; i++)
			{
				if (perkDesc.m_cost > sortedPerks.Get(i).m_cost)
				{
					sortedPerks.InsertAt(perkDesc, i);
					isAdded = true;
				}
			}
			
			if (!isAdded)
			{
				sortedPerks.Insert(perkDesc);
			}
		}
		
		m_currentScore = m_metadata.m_score;
		m_perksUsed.ClearItems();
		foreach (int perkId : m_usedPerks)
		{
			ref PerkDescription usedPerkData = m_allPerksDesc.Get(perkId);

			rowId = m_perksUsed.AddItem(usedPerkData.m_name, usedPerkData, 0);
			if (usedPerkData.m_cost > 0) m_perksUsed.SetItemColor(rowId, 0, ARGBF(1, 0, 0.639, 0));
			if (usedPerkData.m_cost < 0) m_perksUsed.SetItemColor(rowId, 0, ARGBF(1, 0.933, 0.067, 0.067));			
			m_currentScore = m_currentScore - usedPerkData.m_cost;
		}
		
		m_perksTotal.ClearItems();
		foreach (ref PerkDescription perkInfo : sortedPerks)
		{
			int fperkId = m_allPerksDesc.Find(perkInfo);
			if (m_usedPerks.Find(fperkId) != -1) continue;
			
			fperkId = GetPerkIdByName(m_allPerksDesc, perkInfo.m_antiperk);
			if (m_usedPerks.Find(fperkId) != -1) continue;
			
			rowId = m_perksTotal.AddItem(perkInfo.m_name, perkInfo, 0);
			m_perksTotal.SetItem(rowId, "" + perkInfo.m_cost, perkInfo, 1);
			if (perkInfo.m_cost > 0)
			{
				m_perksTotal.SetItemColor(rowId, 1, ARGBF(1, 0, 0.639, 0));
			}
			if (perkInfo.m_cost < 0)
			{
				m_perksTotal.SetItemColor(rowId, 1, ARGBF(1, 0.933, 0.067, 0.067));
			}
		}
		
		m_totalScore.SetText("#syb_totalpoints " + m_currentScore);
		
		delete sortedPerks;
		
		UpdateSkills();
	}
	
	void UpdateSkills()
	{
		m_skillsResult.ClearItems();
		
		foreach (ref SkillContainer skillData : m_metadata.m_skillsContainer.m_skills)
		{
			float addValue = 0;
			
			foreach (int perkId : m_usedPerks)
			{
				ref PerkDescription perkInfo = m_allPerksDesc.Get(perkId);
				if (perkInfo.m_effects && perkInfo.m_effects.Contains(skillData.m_name))
				{
					addValue = addValue + perkInfo.m_effects.Get(skillData.m_name);
				}
			}
			
			string skillStr = "" + (int)skillData.m_value;			
			if (addValue > 0) skillStr = (int)(skillData.m_value + addValue) + " (" + skillStr + "+" + (int)addValue + ")"; 
			if (addValue < 0) skillStr = (int)(skillData.m_value + addValue) + " (" + skillStr + "-" + (int)(addValue * -1) + ")"; 
			
			int rowId = m_skillsResult.AddItem(skillData.m_name, null, 0);
			m_skillsResult.SetItem(rowId, skillStr, null, 1);
			
			if (addValue > 0) m_skillsResult.SetItemColor(rowId, 1, ARGBF(1, 0, 0.639, 0));
			if (addValue < 0) m_skillsResult.SetItemColor(rowId, 1, ARGBF(1, 0.933, 0.067, 0.067));
		}
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);

		if (m_updateFacePreview)
		{
			m_updateFacePreview = false;
			UpdatePlayerPreview();
		}
		
		if (m_updatePerks)
		{
			m_updatePerks = false;
			UpdatePerks();
		}
		
		if (m_isRpcSended)
		{
			m_NextBtn.Show(false);
		}
		
		m_NextBtn.Show(m_currentScore < 0 || m_charNameEdit.GetText().LengthUtf8() == 0 || (m_charNameEdit.GetText().LengthUtf8() >= 4 && m_charNameEdit.GetText().LengthUtf8() <= m_maxNameLength) );
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		bool result = super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{			
			if (w == m_NextBtn)
			{
				if (m_currentScore >= 0)
				{
					m_isRpcSended = true;
					
					ref RpcCreateNewCharContainer requestParams = new RpcCreateNewCharContainer();
					requestParams.m_name = m_charNameEdit.GetText();
					requestParams.m_isMale = (m_genderSelector.GetCurrentItem() == 0);
					requestParams.m_faceId = m_faceSelector.GetCurrentItem();					
					requestParams.m_perks = m_usedPerks;
					
					
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
			if (w == m_addPerkBtn)
			{
				int perkToAdd = m_perksTotal.GetSelectedRow();
				if (perkToAdd >= 0)
				{
					ref PerkDescription perkDescToAdd;
					m_perksTotal.GetItemData(perkToAdd, 0, perkDescToAdd);
					
					int perkToAddId = GetPerkIdByName(m_allPerksDesc, perkDescToAdd.m_name);
					m_usedPerks.Insert(perkToAddId);
				}
				
				m_updatePerks = true;
				return true;
			}
			if (w == m_delPerkBtn)
			{
				int perkToDel = m_perksUsed.GetSelectedRow();
				if (perkToDel >= 0)
				{
					ref PerkDescription perkDescToDel;
					m_perksUsed.GetItemData(perkToDel, 0, perkDescToDel);
					
					int perkToDelId = GetPerkIdByName(m_allPerksDesc, perkDescToDel.m_name);
					m_usedPerks.RemoveItem(perkToDelId);
				}
				
				m_updatePerks = true;
				return true;
			}
		}
		
		return result;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		bool result = super.OnChange(w, x, y, finished);
	
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
		
		return result;
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