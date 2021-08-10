class SkillsMenu extends UIScriptedMenu
{
	static int m_storedSkillId = 0;
	static int m_storedLevelId = 0;
	static int m_storedPerkId = 0;
	
	bool m_active = false;
	bool m_dirty = false;
	bool m_refresh = false;
	
	int m_currentSelectedSkill = -1;
	int m_currentSelectedLevel = -1;
	
	ref TextListboxWidget m_skillsList;
	ref TextWidget m_totalLvlText;
	ref MultilineTextWidget m_totalLvlDesc;
	ref TextWidget m_currentLvlText;
	ref SimpleProgressBarWidget m_currentLvlProgress;
	
	ref TextListboxWidget m_skillLevelsList;
	ref TextListboxWidget m_skillPerksList;
	
	ref TextWidget m_perkName;
	ref MultilineTextWidget m_perkDesc;
	ref MultilineTextWidget m_perkHint;
	ref MultilineTextWidget m_perkErr;
	ref ButtonWidget m_activatePerkBtn;
	ref Widget m_activatePerkBack;
	
	ref Widget m_panelSkillEditing;
	ref Widget m_panelSkillDisabled;
	
	void SkillsMenu()
	{

	}
	
	void ~SkillsMenu()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
	}

    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/SkillsMenu.layout" );

		m_skillsList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("SkillsWidget"));
		m_totalLvlText = TextWidget.Cast(layoutRoot.FindAnyWidget("TotalLvlText"));
		m_totalLvlDesc = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("TotalLvlDesc"));
		m_currentLvlText = TextWidget.Cast(layoutRoot.FindAnyWidget("CurrentLvlText"));
		m_currentLvlProgress = SimpleProgressBarWidget.Cast(layoutRoot.FindAnyWidget("CurrentLvlProgress"));
		
		m_skillLevelsList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("SkillLevelsList"));
		m_skillPerksList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("SkillPerksList"));
		
		m_perkName = TextWidget.Cast(layoutRoot.FindAnyWidget("PerkName"));
		m_perkDesc = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("PerkDesc"));
		m_perkHint = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("PerkHint"));
		m_perkErr = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("PerkErr"));
		m_activatePerkBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("PerkSelectBtn"));
		m_activatePerkBack = layoutRoot.FindAnyWidget("PerkSelectBack");
		
		m_panelSkillEditing = layoutRoot.FindAnyWidget("PanelSkillEditing");
		m_panelSkillDisabled = layoutRoot.FindAnyWidget("PanelSkillDisabled");
		
		UpdateSkillsList();
		
		m_active = true;
		m_dirty = true;
        return layoutRoot;
    }

	private void UpdateSkillsList()
	{
		SybLog("UpdateSkillsList");
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.m_skills) return;

		int rowId = -1;
		int currentSelection = m_skillsList.GetSelectedRow();		
		m_skillsList.ClearItems();
		for (int q = 0; q < SYBERIA_ENABLED_SKILLS_COUNT; ++q)
		{
			int i = SYBERIA_ENABLED_SKILLS_LIST[q];
			rowId = m_skillsList.AddItem("#syb_skill" + i, null, 0);
			int currentSkillValue = player.m_skills.GetSkillValueInt(i);			
			m_skillsList.SetItem(rowId, currentSkillValue.ToString(), null, 1);
		}
		
		if (currentSelection < 0)
		{
			currentSelection = 0;
		}
		
		int currentSelectionSkill = SYBERIA_ENABLED_SKILLS_LIST[currentSelection];
		int currentValue = player.m_skills.GetSkillValueInt(currentSelectionSkill);
		m_skillsList.SelectRow(currentSelection);
		m_totalLvlText.SetText("#syb_skill" + currentSelectionSkill + ": " + currentValue);
		m_totalLvlDesc.SetText("#syb_skill_desc" + currentSelectionSkill);
				
		int curLvlValue = (int)Math.Round(player.m_skills.GetSkillLevelValue(currentSelectionSkill));
		int maxLvlValue = (int)Math.Round(player.m_skills.GetSkillLevelSize(currentSelectionSkill));
		if (currentValue != player.m_skills.GetSkillMax(currentSelectionSkill))
		{
			m_currentLvlText.SetText( curLvlValue.ToString() + "/" + maxLvlValue.ToString() );
			m_currentLvlProgress.SetCurrent( (curLvlValue / maxLvlValue) * 100.0 );
		}
		else
		{
			m_currentLvlText.SetText( "MAX" );
			m_currentLvlProgress.SetCurrent( 100 );
		}
		
		int selectedLevelRow = -1;
		int selectedLevelValue = -1;
		array<int> perkUnlockLevels = new array<int>;
		PerksCollection.m_Instance.GetUnlockLevelsOfSkill(currentSelectionSkill, perkUnlockLevels);
		perkUnlockLevels.Sort();
		m_skillLevelsList.ClearItems();
		
		// TODO REMOVE AFTER ALL SKILLS IS READY
		m_panelSkillEditing.Show( perkUnlockLevels.Count() > 0 );
		m_panelSkillDisabled.Show( perkUnlockLevels.Count() == 0 );
		
		foreach (int perkUnlockLevel : perkUnlockLevels)
		{			
			rowId = m_skillLevelsList.AddItem("#syb_skill_level " + perkUnlockLevel, new Param1<int>(perkUnlockLevel), 0);
			
			int visualState = player.m_skills.GetSkillLevelVisualStatus(currentSelectionSkill, perkUnlockLevel);
			if (visualState == -1) visualState = ARGB(255, 255, 0, 0);
			else if (visualState == 1) visualState = ARGB(255, 0, 255, 0);
			else visualState = ARGB(255, 255, 255, 255);
			m_skillLevelsList.SetItemColor(rowId, 0, visualState);
			
			if (selectedLevelValue < perkUnlockLevel && perkUnlockLevel <= currentValue)
			{
				selectedLevelValue = perkUnlockLevel;
				selectedLevelRow = rowId;				
			}
		}
		
		if (perkUnlockLevels.Count() > 0)
		{
			selectedLevelRow = 0;
		}
		
		m_currentSelectedLevel = -1;
		m_skillLevelsList.SelectRow(selectedLevelRow);
	}
	
	private void UpdatePerksList()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.m_skills) return;
		
		int selectedPerk = m_skillPerksList.GetSelectedRow();
		int selectedSkillRow = m_skillsList.GetSelectedRow();
		int selectedLevel = m_skillLevelsList.GetSelectedRow();
		
		m_skillPerksList.ClearItems();
		if (selectedSkillRow == -1 || selectedLevel == -1)
			return;
		
		int selectedSkill = SYBERIA_ENABLED_SKILLS_LIST[selectedSkillRow];		
		Param1<int> selectedLevelValue;
		m_skillLevelsList.GetItemData(selectedLevel, 0, selectedLevelValue);
		
		array<ref PerkInfo> perks = new array<ref PerkInfo>;
		PerksCollection.m_Instance.GetFilteredPerks(selectedSkill, selectedLevelValue.param1, perks);
		
		int visualState = player.m_skills.GetSkillLevelVisualStatus(selectedSkill, selectedLevelValue.param1);
		foreach (ref PerkInfo perk : perks)
		{
			int rowId = m_skillPerksList.AddItem(perk.GetName(), perk, 0);
			if (visualState == -1)
			{
				m_skillPerksList.SetItemColor(rowId, 0, ARGB(255, 255, 0, 0));
			}
			else if (visualState == 1)
			{
				if (player.m_skills.GetPerkLevel(perk.GetId()) >= selectedLevelValue.param1)
				{
					m_skillPerksList.SetItemColor(rowId, 0, ARGB(255, 0, 255, 0));
				}
				else
				{
					m_skillPerksList.SetItemColor(rowId, 0, ARGB(255, 255, 0, 0));
				}
			}
		}
		
		if (selectedPerk < 0 || selectedPerk >= perks.Count())
		{
			selectedPerk = 0;
		}
		
		if (perks.Count() > 0)
		{
			m_skillPerksList.SelectRow(selectedPerk);
		}
	}
	
	private void UpdatePerkInfo()
	{	
		bool showHint = false;
		string perkName = "";
		string perkDesc = "";
		string errorText = "";
		int perkStatus = -3;
		int selectedSkillRow = m_skillsList.GetSelectedRow();	
		int selectedPerk = m_skillPerksList.GetSelectedRow();
		int selectedLevel = m_skillLevelsList.GetSelectedRow();
		if (selectedSkillRow >= 0 && selectedPerk >= 0 && selectedLevel >= 0)
		{
			int selectedSkill = SYBERIA_ENABLED_SKILLS_LIST[selectedSkillRow];
			Param1<int> selectedLevelValue;
			m_skillLevelsList.GetItemData(selectedLevel, 0, selectedLevelValue);
			if (selectedLevelValue && selectedLevelValue.param1 > 0)
			{
				PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());	
				ref PerkInfo perk;
				
				m_skillPerksList.GetItemData(selectedPerk, 0, perk);
				if (perk && player && player.m_skills)
				{
					perkName = perk.GetName();
					perkDesc = perk.GetDesc(selectedLevelValue.param1);
					perkStatus = player.m_skills.GetPerkStatus( perk.GetId(), selectedLevelValue.param1 );
					
					if (perkStatus == -1) errorText = "#syb_perk_err1";
					else if (perkStatus == -2) errorText = "#syb_perk_err3";
					else if (perkStatus == -3) errorText = "#syb_perk_err2 (#syb_skill" + selectedSkill + " " + perk.GetPrevUnlockLevel(selectedLevelValue.param1) + " #syb_skill_level3)";
				}
			}
		}
		
		if (perkStatus == 0 && m_skillPerksList.GetNumItems() > 1)
		{
			showHint = true;
		}
		
		m_perkName.SetText(perkName);
		m_perkDesc.SetText(perkDesc);
		m_activatePerkBack.Show(perkStatus == 0);
		m_perkHint.Show(showHint);
		m_perkErr.Show(perkStatus < 0);
		m_perkErr.SetText(errorText);
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_refresh)
		{
			m_refresh = false;
			UpdateSkillsList();
			UpdatePerksList();
			UpdatePerkInfo();
		}
		
		if (m_dirty)
		{
			m_dirty = false;
			
			m_skillsList.SelectRow(m_storedSkillId);
			m_skillLevelsList.SelectRow(m_storedLevelId);
			m_skillPerksList.SelectRow(m_storedPerkId);
		}

		if (!m_active)
		{
			m_storedSkillId = m_skillsList.GetSelectedRow();
			m_storedLevelId = m_skillLevelsList.GetSelectedRow();
			m_storedPerkId = m_skillPerksList.GetSelectedRow();
			GetGame().GetUIManager().Back();
		}
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (w == m_activatePerkBtn)
		{
			int selectedSkillRow = m_skillsList.GetSelectedRow();
			int selectedLevel = m_skillLevelsList.GetSelectedRow();
			int selectedPerk = m_skillPerksList.GetSelectedRow();
			if (selectedPerk >= 0 && selectedLevel >= 0 && selectedSkillRow >= 0)
			{
				Param1<int> selectedLevelValue;
				m_skillLevelsList.GetItemData(selectedLevel, 0, selectedLevelValue);
				
				ref PerkInfo perk;				
				m_skillPerksList.GetItemData(selectedPerk, 0, perk);
				if (perk)
				{
					m_storedSkillId = selectedSkillRow;
					m_storedLevelId = selectedLevel;
					m_storedPerkId = selectedPerk;
					m_activatePerkBack.Show(false);
					GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_SKILLS_ACTIVATE, new Param2< int, int >( perk.GetId(), selectedLevelValue.param1 ) );
				}	
			}
		}
		
		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int  column,	int  oldRow, int  oldColumn)
	{
		if (w == m_skillsList && row != m_currentSelectedSkill)
		{
			m_currentSelectedSkill = row;
			UpdateSkillsList();
		}
		
		if (w == m_skillLevelsList && row != m_currentSelectedLevel)
		{
			UpdatePerksList();
		}
		
		if (w == m_skillPerksList)
		{
			UpdatePerkInfo();
		}
		
		return super.OnItemSelected(w, x, y, row, column, oldRow, oldColumn);
	}
	
	override void OnShow()
	{
		super.OnShow();

		GetGame().GetInput().ChangeGameFocus(1);

		SetFocus( layoutRoot );
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(true);
		player.GetActionManager().EnableActions(false);
	}

	override void OnHide()
	{
		super.OnHide();

		GetGame().GetInput().ResetGameFocus();
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.GetInputController().SetDisabled(false);
		player.GetActionManager().EnableActions(true);
		
		Close();
	}
};