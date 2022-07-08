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
	ref array<ItemBase> m_previewEntities;
	
	bool m_isRpcSended = false;
	
	void ScreenEquip(ref array<ref array<string>> equip)
	{
		m_pages = new array<ref ButtonWidget>;
		m_selectedIndexes = new array<int>;		
		m_previewEntities = new array<ItemBase>;		
		m_equip = equip;
		
		for (int i = 0; i < m_equip.Count(); i++)
		{
			m_previewEntities.Insert(null);
			if (m_equip.Get(i).Count() > 0)
			{
				if (i < SyberiaScreenEquipPages.SYBSEP_ITEMS_PAGE)
				{
					m_selectedIndexes.Insert( Math.RandomInt(0, m_equip.Get(i).Count()) );
				}
				else
				{
					m_selectedIndexes.Insert( 0 );
				}
			}
			else
			{
				m_selectedIndexes.Insert(-1);
			}
		}
	}
	
	void ~ScreenEquip()
	{
		if (m_pages) delete m_pages;
		if (m_selectedIndexes) delete m_selectedIndexes;
		
		if (m_equip)
		{
			foreach (ref array<string> items : m_equip)
			{
				delete items;
			}
			delete m_equip;
		}
		
		if (m_previewEntities)
		{
			foreach (ItemBase entity : m_previewEntities)
			{
				if (entity) GetGame().ObjectDelete(entity);
			}
			delete m_previewEntities;
		}
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
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "MaskPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "GlovesPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "VestPage" ) ));
		m_pages.Insert(ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BackpackPage" ) ));
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
		
		/*PlayerBase dummyPlayer = PlayerBase.Cast( m_playerPreview.GetDummyPlayer() );
		if (dummyPlayer)
		{
			if (dummyPlayer.GetEmoteManager() && dummyPlayer.GetEmoteManager().CanPlayEmote(EmoteConstants.ID_EMOTE_HEART))
			{
				dummyPlayer.GetEmoteManager().PlayEmote(EmoteConstants.ID_EMOTE_HEART);
				SybLog("PLAY EMOTE!!!");
			}
		}*/
		
		if (m_isRpcSended)
		{
			m_StartBtn.Show(false);
		}
		
		if (m_updateCurrentPage)
		{
			m_updateCurrentPage = false;
			
			for (int i = 0; i < m_pages.Count(); i++)
			{
				ref ButtonWidget pageBtn = m_pages.Get(i);
				if (m_currentPage == i)
				{
					pageBtn.Enable(false);
				}
				else
				{
					pageBtn.Enable(true);
				}
			}
			
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
		foreach (string itemClass : items)
		{
			string itemName;
			if (m_currentPage > SyberiaScreenEquipPages.SYBSEP_SPAWN_PAGE && m_currentPage < SyberiaScreenEquipPages.SYBSEP_ITEMS_PAGE)
			{
				string magName;
				float health, quantity;
				TStringArray attachments = new TStringArray();
				EquipItemData.Parse(itemClass, itemName, attachments, health, quantity, magName);
				itemName = GameHelpers.GetItemDisplayName(itemName);
			}
			else
			{
				itemName = itemClass;
			}
			
			m_selection.AddItem(itemName, null, 0);
		}
		
		m_selection.SelectRow(m_selectedIndexes.Get(m_currentPage));
	}
	
	private void ReequipPreview()
	{	
		int index;
		int i;
		ItemBase newEntity;
		ItemBase oldEntity;
		DayZPlayer player = GetGame().GetPlayer();
		
		for (i = SyberiaScreenEquipPages.SYBSEP_BODY_PAGE; i <= SyberiaScreenEquipPages.SYBSEP_WEAPON_PAGE; i++)
		{
			index = m_selectedIndexes.Get(i);
			oldEntity = m_previewEntities.Get(i);
			if (index != -1)
			{
				string itemName, magName;
				float health, quantity;
				string itemData = m_equip.Get(i).Get(index);
				TStringArray attachments = new TStringArray();
				EquipItemData.Parse(itemData, itemName, attachments, health, quantity, magName);
				
				newEntity = ItemBase.Cast(GetGame().CreateObject(itemName, "0 0 0", true));
				foreach (string attachment : attachments)
				{
					EntityAI attachmentItem = EntityAI.Cast( GetGame().CreateObject(attachment, "0 0 0", true) );
					if (attachmentItem)
					{
						newEntity.GetInventory().TakeEntityAsAttachment(InventoryMode.LOCAL, attachmentItem);
					}
				}
						
				if (i == SyberiaScreenEquipPages.SYBSEP_WEAPON_PAGE)
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
				if (i == SyberiaScreenEquipPages.SYBSEP_WEAPON_PAGE)
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
				//delete requestParams;
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