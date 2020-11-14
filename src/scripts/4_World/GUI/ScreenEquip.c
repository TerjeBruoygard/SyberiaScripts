class ScreenEquip extends ScreenBase
{
	ref PlayerPreviewWidget m_playerPreview;
	ref ButtonWidget m_StartBtn;
	
	ref TextListboxWidget m_selection;
	ref array<ref ButtonWidget> m_pages;
	ref array<int> m_selectedIndexes;
	ref array<ref array<string>> m_equip;
	int m_currentPage = 0;
	bool m_updateCurrentPage = false;
	bool m_updatePlayerPreview = false;
	ref array<ref EntityAI> m_previewEntities;
	
	bool m_isRpcSended = false;
	
	void ScreenEquip(ref array<ref array<string>> equip)
	{
		m_pages = new array<ref ButtonWidget>;
		m_selectedIndexes = new array<int>;
		m_previewEntities = new array<ref EntityAI>;		
		m_equip = equip;
		
		for (int i = 0; i < m_equip.Count(); i++)
		{
			m_previewEntities.Insert(null);
			if (m_equip.Get(i).Count() > 0)
			{
				m_selectedIndexes.Insert(0);
			}
			else
			{
				m_selectedIndexes.Insert(-1);
			}
		}
	}
	
	void ~ScreenEquip()
	{
		delete m_pages;
		delete m_selectedIndexes;
		
		foreach (ref array<string> items : m_equip)
		{
			delete items;
		}
		delete m_equip;
		
		foreach (ref EntityAI entity : m_previewEntities)
		{
			if (entity) GetGame().ObjectDelete(entity);
		}
		delete m_previewEntities;
	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenEquip.layout" );

		m_playerPreview = PlayerPreviewWidget.Cast( layoutRoot.FindAnyWidget( "PlayerPreview" ) );
		m_StartBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "StartBtn" ) );
		
		m_selection = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "ItemsSelector" ) );
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "SpawnPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BodyPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "PantsPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "FootPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "HeadPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "WeaponPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ItemsPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "SpecialPage" ) ));
		m_updateCurrentPage = true;
		m_updatePlayerPreview = true;
			
		m_playerPreview.SetPlayer(GetGame().GetPlayer());
				
        return layoutRoot;
    }
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_isRpcSended)
		{
			m_StartBtn.Show(false);
		}
		
		if (m_updateCurrentPage)
		{
			m_updateCurrentPage = false;
			UpdateCurrentPage();
		}
		
		int rowId = m_selection.GetSelectedRow();
		if (m_updatePlayerPreview || m_selectedIndexes.Get(m_currentPage) != rowId)
		{
			m_updatePlayerPreview = false;
			m_selectedIndexes.Set(m_currentPage, rowId);
			ReequipPreview();
		}
	}
	
	private void UpdateCurrentPage()
	{
		m_selection.ClearItems();
		
		ref array<string> items = m_equip.Get(m_currentPage);
		foreach (string item : items)
		{
			m_selection.AddItem(item, null, 0);
		}
		
		m_selection.SelectRow(m_selectedIndexes.Get(m_currentPage));
	}
	
	private void ReequipPreview()
	{	
		int index;
		int i;
		EntityAI newEntity;
		EntityAI oldEntity;
		DayZPlayer player = GetGame().GetPlayer();
		
		for (i = 1; i <= 5; i++)
		{
			index = m_selectedIndexes.Get(i);
			oldEntity = m_previewEntities.Get(i);
			if (index != -1)
			{
				string itemName = m_equip.Get(i).Get(index);
				newEntity = EntityAI.Cast(GetGame().CreateObject(itemName, "0 0 0", true));
				if (i == 5)
				{
					m_playerPreview.UpdateItemInHands(newEntity);
					if (oldEntity) GetGame().ObjectDelete(oldEntity);
				}
				else
				{
					if (oldEntity == null)
					{
						if (player.GetHumanInventory().TakeEntityToInventory(InventoryMode.LOCAL, FindInventoryLocationType.ATTACHMENT, newEntity))
						{
							m_previewEntities.Set(i, newEntity);
						}
						else
						{
							GetGame().ObjectDelete(newEntity);
							SybLog("FAILED to take entity " + itemName + " to inventory.");
						}
					}
					else
					{
						if (player.LocalSwapEntities(oldEntity, newEntity))
						{
							GetGame().ObjectDelete(oldEntity);
							m_previewEntities.Set(i, newEntity);
						}
						else
						{
							GetGame().ObjectDelete(newEntity);
							SybLog("FAILED to swap entity " + itemName + " to inventory.");
						}
					}
				}
			}
			else if (oldEntity != null)
			{
				if (i == 5)
				{
					m_playerPreview.UpdateItemInHands(null);
				}
				
				GetGame().ObjectDelete(oldEntity);
				m_previewEntities.Set(i, null);
			}
		}
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{
			if (w == m_StartBtn)
			{
				m_isRpcSended = true;

				auto requestParams = new Param1<ref array<int>>(m_selectedIndexes); 
				GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_STARTGAME_REQUEST, requestParams);
				delete requestParams;
				return true;
			}
			
			foreach (ref ButtonWidget pageBtn : m_pages)
			{
				if (w == pageBtn)
				{
					m_selectedIndexes.Set(m_currentPage, m_selection.GetSelectedRow());
					m_currentPage = m_pages.Find(pageBtn);
					m_updateCurrentPage = true;
					return true;
				}
			}
		}
		
		return false;
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		super.OnChange(w, x, y, finished);
		return false;
	}
}