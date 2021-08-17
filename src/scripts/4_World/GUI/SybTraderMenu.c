class SybTraderMenu extends UIScriptedMenu
{
	const float SELL_ITEM_DEPTH_OFFSET = 30;
	const float SELL_ITEM_HEIGHT_OFFSET = 2;
	const float PROGRESS_BAR_PRICE_DIVIDER = 25;
	
	bool m_active = false;
	bool m_dirty = false;
	
	int m_traderId;
	ref PluginTrader_Trader m_traderInfo;
	ref PluginTrader_Data m_traderData;
	
	ref ScrollWidget m_sellItemsPanel;
	ref ScrollWidget m_buyItemsPanel;
	
	ref SimpleProgressBarWidget m_progressPositive;
	ref SimpleProgressBarWidget m_progressNegative;
	
	ref ButtonWidget m_barterBtn;
	
	ref array<ref Widget> m_sellWidgetsCache = new array<ref Widget>;
	ref array<ref Widget> m_buyWidgetsCache = new array<ref Widget>;
	ref array<ref SybTraderMenu_BuyData> m_buyData = new array<ref SybTraderMenu_BuyData>;
	ref array<EntityAI> m_previewItemsCache = new array<EntityAI>;
	
	ref array<string> m_filterData = new array<string>;
	static ref array<bool> m_filterMemory = new array<bool>;
	
	float m_currentBarterProgress = 0;
	
	void InitMetadata(int traderId, ref PluginTrader_Trader traderInfo, ref PluginTrader_Data traderData)
	{
		m_traderId = traderId;
		m_traderInfo = traderInfo;
		m_traderData = traderData;
		m_dirty = true;
	}
	
	void UpdateMetadata(ref PluginTrader_Data traderData)
	{
		if (m_traderData)
		{
			delete m_traderData;
		}
		
		m_traderData = traderData;
		m_dirty = true;
	}
	
	void CleanupBuyUI()
	{
		foreach (ref Widget w2 : m_buyWidgetsCache)
		{
			w2.Unlink();
		}
		m_buyWidgetsCache.Clear();
		
		foreach (ref SybTraderMenu_BuyData buyData : m_buyData)
		{
			delete buyData;
		}
		m_buyData.Clear();
		
		foreach (EntityAI item : m_previewItemsCache)
		{
			GetGame().ObjectDelete(item);
		}
		m_previewItemsCache.Clear();
	}
	
	void CleanupUI()
	{
		CleanupBuyUI();
		
		foreach (ref Widget w1 : m_sellWidgetsCache)
		{
			w1.Unlink();
		}		
		m_sellWidgetsCache.Clear();
	}
	
	void InitInventorySell()
	{
		PluginTrader pluginTrader = PluginTrader.Cast(GetPlugin(PluginTrader));
		if (!pluginTrader)
			return;
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (!player || !player.IsAlive())
			return;
		
		int nextItemIndex = -1;
		ItemBase item = ItemBase.Cast( player.GetItemInHands() );
		if (item)
		{
			nextItemIndex = InitItemSell(nextItemIndex + 1, 0, item, pluginTrader);
		}
		
		for ( int i = 0; i < player.GetInventory().GetAttachmentSlotsCount(); ++i )
		{
			item = ItemBase.Cast( player.GetInventory().FindAttachment(player.GetInventory().GetAttachmentSlotId(i)) );
			if ( item )
			{
				nextItemIndex = InitItemSell(nextItemIndex + 1, 0, item, pluginTrader);
			}
		}
	}
	
	int InitItemSell(int index, int depth, ItemBase item, PluginTrader pluginTrader)
	{		
		ref Widget itemSell = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/TraderMenuItemSell.layout" );		
		m_sellItemsPanel.AddChild(itemSell);
				
		float w, h;
		float contentWidth = m_sellItemsPanel.GetContentWidth() - (SELL_ITEM_DEPTH_OFFSET * depth);
		itemSell.GetSize(w, h);
		itemSell.SetPos(SELL_ITEM_DEPTH_OFFSET * depth, (h + SELL_ITEM_HEIGHT_OFFSET) * index);
		itemSell.SetSize(contentWidth, h);
		
		ref ButtonWidget actionButton = ButtonWidget.Cast( itemSell.FindAnyWidget( "ItemActionButton" ) );
		actionButton.SetUserData(item);
		actionButton.SetUserID(1001);
		actionButton.GetParent().SetUserID(depth);
		
		ref ItemPreviewWidget previewWidget = ItemPreviewWidget.Cast( itemSell.FindAnyWidget( "ItemPreviewWidget" ) );		
		previewWidget.SetItem(item);
		previewWidget.SetView(item.GetViewIndex());
		previewWidget.SetModelPosition(Vector(0,0,1));
		
		WidgetSetWidth(itemSell, "ItemNameWidget", contentWidth - 220);
		WidgetTrySetText(itemSell, "ItemNameWidget", item.GetDisplayName());
		WidgetTrySetText(itemSell, "ItemPriceWidget", pluginTrader.CalculateSellPrice(m_traderInfo, m_traderData, item).ToString());		
		UpdateItemInfoDamage(itemSell, item);
		UpdateItemInfoQuantity(itemSell, item);		
		m_sellWidgetsCache.Insert(itemSell);
		
		if (item.GetInventory() && depth < 8)
		{
			int i;
			for ( i = 0; i < item.GetInventory().GetAttachmentSlotsCount(); ++i )
			{
				ItemBase attachment = ItemBase.Cast( item.GetInventory().FindAttachment(item.GetInventory().GetAttachmentSlotId(i)) );
				if ( attachment )
				{
					index = InitItemSell(index + 1, depth + 1, attachment, pluginTrader);
				}
			}
			
			if (item.GetInventory().GetCargo())
			{
				for ( i = 0; i < item.GetInventory().GetCargo().GetItemCount(); ++i )
				{
					ItemBase cargo = ItemBase.Cast( item.GetInventory().GetCargo().GetItem(i) );
					if ( cargo )
					{
						index = InitItemSell(index + 1, depth + 1, cargo, pluginTrader);
					}
				}
			}
		}
		
		return index;
	}
	
	void InitInventoryBuy()
	{
		CleanupBuyUI();
		
		PluginTrader pluginTrader = PluginTrader.Cast(GetPlugin(PluginTrader));
		if (!pluginTrader)
			return;
		
		if (!m_traderData || !m_traderData.m_items)
			return;
		
		int nextItemIndex = -1;
		foreach ( string classname, float quantity : m_traderData.m_items )
		{
			if (pluginTrader.FilterByCategories(m_filterData, m_filterMemory, classname))
			{
				ItemBase item = ItemBase.Cast( GetGame().CreateObject(classname, "0 0 0", true, false, false) );
				if (item)
				{
					nextItemIndex = InitItemBuy(nextItemIndex + 1, item, classname, quantity, pluginTrader);
				}
			}
		}
	}
	
	int InitItemBuy(int index, ItemBase item, string classname, float quantity, PluginTrader pluginTrader)
	{
		ref Widget itemBuy = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/TraderMenuItemBuy.layout" );		
		m_buyItemsPanel.AddChild(itemBuy);
				
		float w, h;
		float contentWidth = m_sellItemsPanel.GetContentWidth();
		itemBuy.GetSize(w, h);
		itemBuy.SetPos(0, (h + SELL_ITEM_HEIGHT_OFFSET) * index);
		itemBuy.SetSize(contentWidth, h);
		itemBuy.SetUserID(index);
		
		ref SybTraderMenu_BuyData actionBtnParam = new ref SybTraderMenu_BuyData;
		actionBtnParam.m_classname = classname;
		actionBtnParam.m_totalQuantity = quantity;
		actionBtnParam.m_maxBuyQuantity = pluginTrader.CalculateBuyMaxQuantity(m_traderInfo, classname);
		actionBtnParam.m_selectedQuantity = Math.Clamp(quantity, 1, actionBtnParam.m_maxBuyQuantity);
		
		ref ButtonWidget actionButton = ButtonWidget.Cast( itemBuy.FindAnyWidget( "ItemActionButton" ) );
		actionButton.SetUserID(2001);
		
		ref ItemPreviewWidget previewWidget = ItemPreviewWidget.Cast( itemBuy.FindAnyWidget( "ItemPreviewWidget" ) );		
		previewWidget.SetItem(item);
		previewWidget.SetView(item.GetViewIndex());
		previewWidget.SetModelPosition(Vector(0,0,1));
		m_previewItemsCache.Insert(item);
		
		WidgetSetWidth(itemBuy, "ItemNameWidget", contentWidth - 220);
		WidgetTrySetText(itemBuy, "ItemNameWidget", item.GetDisplayName());
		WidgetTrySetText(itemBuy, "ItemPriceWidget", pluginTrader.CalculateBuyPrice(m_traderInfo, classname, quantity).ToString());		
		UpdateItemInfoQuantity(itemBuy, pluginTrader, classname, quantity);					
		UpdateItemInfoSelectedQuantity(itemBuy, classname, actionBtnParam.m_selectedQuantity, actionBtnParam.m_maxBuyQuantity);
		
		ref ButtonWidget minusButton = ButtonWidget.Cast( itemBuy.FindAnyWidget( "MinusActionBtn" ) );
		minusButton.SetUserID(3001);
		
		ref ButtonWidget plusButton = ButtonWidget.Cast( itemBuy.FindAnyWidget( "PlusActionBtn" ) );
		plusButton.SetUserID(3002);
		
		m_buyWidgetsCache.Insert(itemBuy);
		m_buyData.Insert(actionBtnParam);
		return index;
	}
	
	string FormatBuyQuantityStr(float quantity)
	{
		int quantityInt = (int)Math.Round(quantity * 10.0);
		string quantityStr = quantityInt.ToString();
		if (quantityInt % 10 != 0)
		{
			if (quantityStr.Length() == 1)
			{
				quantityStr = "0." + quantityStr;
			}
			else
			{
				quantityStr = quantityStr.Substring(0, quantityStr.Length() - 1) + "." + quantityStr.Substring(quantityStr.Length() - 1, 1);
			}
		}
		else
		{
			if (quantityStr.Length() > 1)
			{
				quantityStr = quantityStr.Substring(0, quantityStr.Length() - 1);
			}
		}
		
		return quantityStr;
	}
	
	void UpdateCurrentPriceProgress()
	{
		PluginTrader pluginTrader = PluginTrader.Cast(GetPlugin(PluginTrader));
		if (!pluginTrader)
			return;
		
		float value = 0;
		ref array<ItemBase> sellResult = new array<ItemBase>;
		GetSelectedSellItems(sellResult);
		foreach (ItemBase sellItem : sellResult)
		{
			value = value + pluginTrader.CalculateSellPrice(m_traderInfo, m_traderData, sellItem);
		}
		delete sellResult;
		
		ref map<string, float> buyResult = new map<string, float>;
		GetSelectedBuyItems(buyResult);
		foreach (string buyClassname, float buyQuantity : buyResult)
		{
			value = value - pluginTrader.CalculateBuyPrice(m_traderInfo, buyClassname, buyQuantity);
		}
		delete buyResult;
		
		value = value / PROGRESS_BAR_PRICE_DIVIDER;
		if (value > 0)
		{
			m_progressPositive.SetCurrent(Math.Min(100, value));
			m_progressNegative.SetCurrent(0);
			m_barterBtn.Enable(true);
		}
		else if (value < 0)
		{
			m_progressPositive.SetCurrent(0);
			m_progressNegative.SetCurrent(Math.Min(100, value * -1));
			m_barterBtn.Enable(false);
		}
		else
		{
			m_progressPositive.SetCurrent(0);
			m_progressNegative.SetCurrent(0);
			m_barterBtn.Enable(true);
		}
		
		m_currentBarterProgress = value;
	}
	
	void GetSelectedSellItems(ref array<ItemBase> result)
	{
		foreach (ref Widget w : m_sellWidgetsCache)
		{
			ref Widget btn = w.FindAnyWidget("ItemActionButton");
			if (btn.GetUserID() == 1002)
			{
				ItemBase item;
				btn.GetUserData(item);
				if (item)
				{
					result.Insert(item);
				}
			}
		}
	}
	
	void GetSelectedBuyItems(ref map<string, float> result)
	{
		int index;
		ref SybTraderMenu_BuyData buyData;
		foreach (ref Widget w : m_buyWidgetsCache)
		{
			ref Widget btn = w.FindAnyWidget("ItemActionButton");
			if (btn.GetUserID() == 2002)
			{
				index = w.GetUserID();
				buyData = m_buyData.Get(index);
				result.Insert(buyData.m_classname, buyData.m_selectedQuantity);
			}
		}
	}
	
	void InitializeFilter(ref Widget root, string name)
	{
		int id = m_filterData.Insert(name);
		ref ButtonWidget btn = ButtonWidget.Cast( root.FindAnyWidget("FilterActionBtn" + id) );		
		btn.SetUserID(5000 + id);
		
		ref TextWidget btnText = TextWidget.Cast( btn.GetChildren() );
		btnText.SetText("#syb_trader_filter_" + name);
		
		if (m_filterMemory.Count() <= id)
		{
			m_filterMemory.Insert(true);
		}
		
		SelectFilterItem(btn, m_filterMemory.Get(id));
	}
	
	override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/TraderMenu.layout" );
		
		m_sellItemsPanel = ScrollWidget.Cast( layoutRoot.FindAnyWidget( "SellItemsPanel" ) );
		m_buyItemsPanel = ScrollWidget.Cast( layoutRoot.FindAnyWidget( "BuyItemsPanel" ) );
		m_progressPositive = SimpleProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "ProgressPositive" ) );
		m_progressNegative = SimpleProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "ProgressNegative" ) );
		m_barterBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "TradeButton" ) );
		
		m_filterData.Clear();
		InitializeFilter(layoutRoot, "weapons");
		InitializeFilter(layoutRoot, "magazines");
		InitializeFilter(layoutRoot, "attachments");			
		InitializeFilter(layoutRoot, "ammo");	
		
		InitializeFilter(layoutRoot, "tools");		
		InitializeFilter(layoutRoot, "food");			
		InitializeFilter(layoutRoot, "clothing");
		InitializeFilter(layoutRoot, "medical");
		
		InitializeFilter(layoutRoot, "electronic");			
		InitializeFilter(layoutRoot, "base_building");
		InitializeFilter(layoutRoot, "vehicle_parts");
		InitializeFilter(layoutRoot, "other");
		
		m_active = true;
        return layoutRoot;
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_dirty)
		{
			CleanupUI();
			UpdateCurrentPriceProgress();
			InitInventorySell();
			InitInventoryBuy();
			m_dirty = false;
		}

		if (!m_active)
		{
			GetGame().GetUIManager().Back();
		}
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
		
		CleanupUI();
		
		if (m_traderInfo)
		{
			delete m_traderInfo;
		}
		
		if (m_traderData)
		{
			delete m_traderData;
		}

		delete m_buyData;
		delete m_sellWidgetsCache;
		delete m_buyWidgetsCache;
		delete m_filterData;
				
		Close();
	}
	
	private void SelectSellItem(ref ButtonWidget btn, bool enable)
	{
		ref Widget back = btn.GetParent();
		if (back)
		{
			int depth = back.GetUserID();
			int itemId = m_sellWidgetsCache.Find(back.GetParent());
			
			if (itemId != -1)
			{
				int index = itemId - 1;
				if (btn.GetUserID() == 1002)
				{
					while (index >= 0)
					{
						ref Widget prevItem = m_sellWidgetsCache.Get(index);
						ref ButtonWidget prevBtn = ButtonWidget.Cast( prevItem.FindAnyWidget("ItemActionButton") );
						ref Widget prevBack = prevBtn.GetParent();
						
						if (prevBack.GetUserID() < depth)
						{
							if (prevBtn.GetUserID() == 1002)
							{
								prevBack.SetColor(ARGB(200, 25, 25, 25));
								prevBtn.SetUserID(1001);
							}
							break;	
						}
						
						index--;
					}
				}
				
				if (enable)
				{
					back.SetColor(ARGB(200, 16, 87, 20));
					btn.SetUserID(1002);					
				}
				else
				{
					back.SetColor(ARGB(200, 25, 25, 25));
					btn.SetUserID(1001);
				}			

				index = itemId + 1;				
				while (index < m_sellWidgetsCache.Count())
				{
					ref Widget nextItem = m_sellWidgetsCache.Get(index);
					ref ButtonWidget nextBtn = ButtonWidget.Cast( nextItem.FindAnyWidget("ItemActionButton") );
					ref Widget nextBack = nextBtn.GetParent();
					
					if (depth >= nextBack.GetUserID())
					{
						break;	
					}
					
					if (enable)
					{
						nextBack.SetColor(ARGB(200, 16, 87, 20));
						nextBtn.SetUserID(1002);
					}
					else
					{
						nextBack.SetColor(ARGB(200, 25, 25, 25));
						nextBtn.SetUserID(1001);
					}
										
					index++;
				}
			}
		}
		
		UpdateCurrentPriceProgress();
	}
	
	private void SelectBuyItem(ref ButtonWidget btn, bool enable)
	{
		ref Widget back = btn.GetParent();
		if (back)
		{
			if (enable)
			{
				back.SetColor(ARGB(200, 16, 87, 20));
				btn.SetUserID(2002);
			}
			else
			{
				back.SetColor(ARGB(200, 25, 25, 25));
				btn.SetUserID(2001);
			}
		}
		
		UpdateCurrentPriceProgress();
	}
	
	private void SwitchFilterItem(ref ButtonWidget btn)
	{
		ref Widget back = btn.GetParent();
		if (back)
		{
			int value = back.GetUserID();
			if (value == 0)
			{
				SelectFilterItem(btn, true);
			}
			else
			{
				SelectFilterItem(btn, false);
			}
		}
		
		InitInventoryBuy();
		UpdateCurrentPriceProgress();
	}
	
	private void SelectFilterItem(ref ButtonWidget btn, bool enable)
	{
		m_filterMemory.Set( btn.GetUserID() - 5000, enable );
		ref Widget back = btn.GetParent();
		if (back)
		{
			if (enable)
			{
				back.SetColor(ARGB(200, 16, 87, 20));
				back.SetUserID(1);
			}
			else
			{
				back.SetColor(ARGB(200, 25, 25, 25));
				back.SetUserID(0);
			}
		}
	}
	
	private void ChangeBuyQuantity(ref ButtonWidget btn, float value)
	{
		PluginTrader pluginTrader = PluginTrader.Cast(GetPlugin(PluginTrader));
		if (!pluginTrader)
			return;
		
		ref Widget mainWidget = btn.GetParent().GetParent().GetParent().GetParent();
		int id = mainWidget.GetUserID();
		
		ref ButtonWidget mainButton = ButtonWidget.Cast( mainWidget.FindAnyWidget("ItemActionButton") );
		SelectBuyItem(mainButton, true);
				
		ref SybTraderMenu_BuyData mainParam = m_buyData.Get(id);	
		
		float stepSize = pluginTrader.CalculateItemSelectedQuantityStep(mainParam.m_classname);
		if (value < 0 && mainParam.m_selectedQuantity <= 1)
		{
			value = stepSize * -1;
		}
		else if (value > 0 && mainParam.m_selectedQuantity < 1)
		{
			value = stepSize;
		}
			
		if ((mainParam.m_selectedQuantity + value) > 0 && (mainParam.m_selectedQuantity + value) <= mainParam.m_maxBuyQuantity)
		{
			mainParam.m_selectedQuantity = mainParam.m_selectedQuantity + value;
			mainParam.m_selectedQuantity = Math.Min(mainParam.m_selectedQuantity, mainParam.m_maxBuyQuantity);
			UpdateItemInfoSelectedQuantity(mainWidget, mainParam.m_classname, mainParam.m_selectedQuantity, mainParam.m_maxBuyQuantity);
		}
		
		UpdateCurrentPriceProgress();
	}
	
	private void DoBarter()
	{
		if (m_currentBarterProgress < 0)
			return;
		
		PluginTrader pluginTrader = PluginTrader.Cast(GetPlugin(PluginTrader));
		if (!pluginTrader)
			return;
		
		ref array<ItemBase> sellItems = new array<ItemBase>;
		GetSelectedSellItems(sellItems);
		
		ref map<string, float> buyItems = new map<string, float>;
		GetSelectedBuyItems(buyItems);
		
		pluginTrader.DoBarter(m_traderId, sellItems, buyItems);
		delete sellItems;
		delete buyItems;
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{					
			if (w.GetUserID() == 1001) // sell item select
			{				
				SelectSellItem(ButtonWidget.Cast(w), true);
			}
			else if (w.GetUserID() == 1002) // sell item unselect
			{
				SelectSellItem(ButtonWidget.Cast(w), false);
			}
			else if (w.GetUserID() == 2001) // buy item select
			{
				SelectBuyItem(ButtonWidget.Cast(w), true);
			}
			else if (w.GetUserID() == 2002) // buy item unselect
			{
				SelectBuyItem(ButtonWidget.Cast(w), false);
			}
			else if (w.GetUserID() == 3001) // minus buy quantity
			{
				ChangeBuyQuantity(ButtonWidget.Cast(w), -1);
			}
			else if (w.GetUserID() == 3002) // plus buy quantity
			{
				ChangeBuyQuantity(ButtonWidget.Cast(w), 1);
			}
			else if (w.GetUserID() >= 5000 && w.GetUserID() < 6000) // switch filter
			{
				SwitchFilterItem(ButtonWidget.Cast(w));
			}
			else if (w == m_barterBtn)
			{
				DoBarter();
			}
		}
		
		return false;
	}
	
	private void UpdateItemInfoDamage(Widget root_widget, ItemBase item)
	{
		int damageLevel = item.GetHealthLevel();		
		switch (damageLevel)
		{
			case GameConstants.STATE_RUINED:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "#inv_inspect_ruined", Colors.COLOR_RUINED);
				break;
			}
			case GameConstants.STATE_BADLY_DAMAGED:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "#inv_inspect_badly", Colors.COLOR_BADLY_DAMAGED);
				break;
			}
			
			case GameConstants.STATE_DAMAGED:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "#inv_inspect_damaged", Colors.COLOR_DAMAGED);
				break;
			}
			
			case GameConstants.STATE_WORN:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "#inv_inspect_worn", Colors.COLOR_WORN);
				break;
			}
			
			case GameConstants.STATE_PRISTINE:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "#inv_inspect_pristine", Colors.COLOR_PRISTINE);
				break;
			}
					
			default:
			{
				WidgetTrySetText(root_widget, "ItemDamageWidget", "ERROR", Colors.COLOR_PRISTINE);
				break;
			}
		}
	
	}
	
	private void UpdateItemInfoQuantity(Widget root_widget, ItemBase item_base)
	{
		float item_quantity = item_base.GetQuantity();
		int max_quantity = item_base.GetQuantityMax();
		
		float quantity_ratio;
		
		if( max_quantity > 0 )
		{
			string quantity_str;
			if( item_base.ConfigGetString("stackedUnit") == "pc." )
			{
				WidgetTrySetText( root_widget, "ItemQuantityWidget", item_quantity.ToString() + "/" + max_quantity.ToString() + " " + "#inv_inspect_pieces" );		
			}
			else if( item_base.ConfigGetString("stackedUnit") == "percentage" )
			{
				quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );				
				quantity_str = quantity_ratio.ToString() + "#inv_inspect_percent";
				WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_str );			
			}
			else if( item_base.ConfigGetString("stackedUnit") == "g" )
			{
				quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );				
				quantity_str = quantity_ratio.ToString() + "#inv_inspect_percent";
				WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_str );			
			}
			else if( item_base.ConfigGetString("stackedUnit") == "ml" )
			{
				quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );				
				quantity_str = quantity_ratio.ToString() + "#inv_inspect_percent";
				WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_str );
			}
			else if ( item_base.IsInherited( Ammunition_Base ) )
			{
				Magazine magazine_item;
				Class.CastTo(magazine_item, item_base);
				
				WidgetTrySetText( root_widget, "ItemQuantityWidget",  magazine_item.GetAmmoCount().ToString() + "/" + magazine_item.GetAmmoMax().ToString() + " " + "#inv_inspect_pieces" );
			}
			else if ( item_base.IsInherited( Magazine ) )
			{
				WidgetTrySetText( root_widget, "ItemQuantityWidget",  "" );
			}
			else
			{
				WidgetTrySetText( root_widget, "ItemQuantityWidget", "" );
			}
		}
		else
		{
			WidgetTrySetText( root_widget, "ItemQuantityWidget", "" );
		}
	}
	
	private void UpdateItemInfoQuantity(Widget root_widget, PluginTrader pluginTrader, string classname, float quantity)
	{
		int maxStackSize = 0;		
		if (GetGame().ConfigIsExisting(CFG_VEHICLESPATH + " " + classname))
		{
			maxStackSize = GetGame().ConfigGetInt( CFG_VEHICLESPATH + " " + classname + " varQuantityMax" );
		}
		else if (GetGame().ConfigIsExisting(CFG_MAGAZINESPATH + " " + classname))
		{
			maxStackSize = GetGame().ConfigGetInt( CFG_MAGAZINESPATH + " " + classname + " count" );
		}
		else if (GetGame().ConfigIsExisting(CFG_WEAPONSPATH + " " + classname))
		{
			maxStackSize = GetGame().ConfigGetInt( CFG_WEAPONSPATH + " " + classname + " varQuantityMax" );
		}
		
		int maxStacksCount = pluginTrader.CalculateTraiderItemQuantityMax(m_traderInfo, classname);
		if ( maxStackSize > 0 )
		{
			string stackedUnits = "";
			if (GetGame().ConfigIsExisting(CFG_VEHICLESPATH + " " + classname))
			{
				stackedUnits = GetGame().ConfigGetTextOut( CFG_VEHICLESPATH + " " + classname + " stackedUnit" );
			}
			else if (GetGame().ConfigIsExisting(CFG_MAGAZINESPATH + " " + classname))
			{
				stackedUnits = GetGame().ConfigGetTextOut( CFG_MAGAZINESPATH + " " + classname + " stackedUnit" );
			}
			else if (GetGame().ConfigIsExisting(CFG_WEAPONSPATH + " " + classname))
			{
				stackedUnits = GetGame().ConfigGetTextOut( CFG_WEAPONSPATH + " " + classname + " stackedUnit" );
			}
			
			float item_quantity;
			int max_quantity;
			if ( stackedUnits == "pc." )
			{
				item_quantity = quantity * maxStackSize;
				max_quantity = maxStacksCount * maxStackSize;
				WidgetTrySetText( root_widget, "ItemQuantityWidget", FormatBuyQuantityStr(item_quantity) + "/" + max_quantity.ToString() + " " + "#inv_inspect_pieces" );	
			}
			else if ( GetGame().IsKindOf(classname, "Ammunition_Base") )
			{
				item_quantity = quantity * maxStackSize;
				max_quantity = maxStacksCount * maxStackSize;
				WidgetTrySetText( root_widget, "ItemQuantityWidget", FormatBuyQuantityStr(item_quantity) + "/" + max_quantity.ToString() + " " + "#inv_inspect_pieces" );
			}
			else
			{
				WidgetTrySetText( root_widget, "ItemQuantityWidget", FormatBuyQuantityStr(quantity) + "/" + maxStacksCount + " " + "#inv_inspect_pieces" );
			}
		}
		else
		{
			WidgetTrySetText( root_widget, "ItemQuantityWidget", FormatBuyQuantityStr(quantity) + "/" + maxStacksCount + " " + "#inv_inspect_pieces" );
		}
	}
	
	private void UpdateItemInfoSelectedQuantity(Widget root_widget, string classname, float quantity, float maxQuantity)
	{		
		int maxStackSize = 0;		
		if (GetGame().ConfigIsExisting(CFG_VEHICLESPATH + " " + classname))
		{
			maxStackSize = GetGame().ConfigGetInt( CFG_VEHICLESPATH + " " + classname + " varQuantityMax" );
		}
		else if (GetGame().ConfigIsExisting(CFG_MAGAZINESPATH + " " + classname))
		{
			maxStackSize = GetGame().ConfigGetInt( CFG_MAGAZINESPATH + " " + classname + " count" );
		}
		else if (GetGame().ConfigIsExisting(CFG_WEAPONSPATH + " " + classname))
		{
			maxStackSize = GetGame().ConfigGetInt( CFG_WEAPONSPATH + " " + classname + " varQuantityMax" );
		}
		
		if ( maxStackSize > 0 )
		{
			string stackedUnits = "";
			if (GetGame().ConfigIsExisting(CFG_VEHICLESPATH + " " + classname))
			{
				stackedUnits = GetGame().ConfigGetTextOut( CFG_VEHICLESPATH + " " + classname + " stackedUnit" );
			}
			else if (GetGame().ConfigIsExisting(CFG_MAGAZINESPATH + " " + classname))
			{
				stackedUnits = GetGame().ConfigGetTextOut( CFG_MAGAZINESPATH + " " + classname + " stackedUnit" );
			}
			else if (GetGame().ConfigIsExisting(CFG_WEAPONSPATH + " " + classname))
			{
				stackedUnits = GetGame().ConfigGetTextOut( CFG_WEAPONSPATH + " " + classname + " stackedUnit" );
			}
			
			float item_quantity;
			float item_max_quantity;
			if ( stackedUnits == "pc." )
			{
				item_quantity = quantity * maxStackSize;
				item_max_quantity = maxQuantity * maxStackSize;
				WidgetTrySetText( root_widget, "ItemSelectedCountWidget", FormatBuyQuantityStr(item_quantity) + "/" + FormatBuyQuantityStr(item_max_quantity) + " " + "#inv_inspect_pieces" );	
			}
			else if ( GetGame().IsKindOf(classname, "Ammunition_Base") )
			{
				item_quantity = quantity * maxStackSize;
				item_max_quantity = maxQuantity * maxStackSize;
				WidgetTrySetText( root_widget, "ItemSelectedCountWidget", FormatBuyQuantityStr(item_quantity) + "/" + FormatBuyQuantityStr(item_max_quantity) + " " + "#inv_inspect_pieces" );
			}
			else
			{
				WidgetTrySetText( root_widget, "ItemSelectedCountWidget", FormatBuyQuantityStr(quantity) + "/" + FormatBuyQuantityStr(maxQuantity) + " " + "#inv_inspect_pieces" );
			}
		}
		else
		{
			WidgetTrySetText( root_widget, "ItemSelectedCountWidget", FormatBuyQuantityStr(quantity) + "/" + FormatBuyQuantityStr(maxQuantity) + " " + "#inv_inspect_pieces" );
		}
	}
	
	private void WidgetTrySetText(Widget root_widget, string widget_name, string text, int color = 0)
	{
		TextWidget widget = TextWidget.Cast( root_widget.FindAnyWidget(widget_name) );
		if (widget)
		{
			widget.SetText(text);			
			if (color != 0)
			{
				widget.SetColor(color | 0xFF000000);
			}
		}
	}
	
	private void WidgetSetWidth(Widget root_widget, string widget_name, float diff)
	{
		float w, h;
		ref Widget widget = root_widget.FindAnyWidget(widget_name);
		root_widget.GetSize(w, h);
		widget.SetSize(Math.Max(1, w - diff), h);
	}
};

class SybTraderMenu_BuyData
{
	string m_classname;
	float m_totalQuantity;
	float m_selectedQuantity;
	float m_maxBuyQuantity;
};