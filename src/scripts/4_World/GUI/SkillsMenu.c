class SkillsMenu extends UIScriptedMenu
{
	bool m_active = false;
	bool m_dirty = false;
	
	ref TextListboxWidget m_skillsList;
	ref TextWidget m_totalLvlText;
	ref TextWidget m_currentLvlText;
	ref SimpleProgressBarWidget m_currentLvlProgress;
	
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
		m_currentLvlText = TextWidget.Cast(layoutRoot.FindAnyWidget("CurrentLvlText"));
		m_currentLvlProgress = SimpleProgressBarWidget.Cast(layoutRoot.FindAnyWidget("CurrentLvlProgress"));
		
		m_active = true;
		m_dirty = true;
        return layoutRoot;
    }

	private void UpdateSkillsList()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player) return;

		int currentSelection = m_skillsList.GetSelectedRow();		
		m_skillsList.ClearItems();
		for (int i = 0; i < SyberiaSkillType.SYBSKILL_TOTALCOUNT; ++i)
		{
			int rowId = m_skillsList.AddItem("#syb_skill" + i, null, 0);
			int currentSkillValue = (int)player.m_skills.GetValue(i);			
			m_skillsList.SetItem(rowId, currentSkillValue.ToString(), null, 1);
		}
		
		if (currentSelection < 0)
		{
			currentSelection = SyberiaSkillType.SYBSKILL_IMMUNITY;
		}
		
		m_skillsList.SelectRow(currentSelection);
		m_totalLvlText.SetText("#syb_skill" + currentSelection + ": " + player.m_skills.GetValueInt(currentSelection));
		
		float curLvlValue = Math.AbsFloat(player.m_skills.GetLevelValue(currentSelection));
		float maxLvlValue = Math.AbsFloat(player.m_skills.GetLevelSize(currentSelection));
		m_currentLvlText.SetText( curLvlValue.ToString() + "/" + maxLvlValue.ToString() );
		m_currentLvlProgress.SetCurrent( (curLvlValue / maxLvlValue) * 100.0 );
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_dirty)
		{
			m_dirty = false;
			UpdateSkillsList();
		}
		
		if (!m_active)
		{
			GetGame().GetUIManager().Back();
		}
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		return false;
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int  column,	int  oldRow, int  oldColumn)
	{
		if (w == m_skillsList && row != oldRow)
		{
			m_dirty = true;
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
}