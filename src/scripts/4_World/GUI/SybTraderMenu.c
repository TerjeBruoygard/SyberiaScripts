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
	ref array<EntityAI> m_previewItemsCache = new array<EntityAI>;
	
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
	
	void CleanupUI()
	{
		foreach (ref Widget w1 : m_sellWidgetsCache)
		{
			w1.Unlink();
		}		
		m_sellWidgetsCache.Clear();
		
		foreach (ref Widget w2 : m_buyWidgetsCache)
		{
			w2.Unlink();
		}
		m_buyWidgetsCache.Clear();
		
		foreach (EntityAI item : m_previewItemsCache)
		{
			GetGame().ObjectDelete(item);
		}
		m_previewItemsCache.Clear();
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
		PluginTrader pluginTrader = PluginTrader.Cast(GetPlugin(PluginTrader));
		if (!pluginTrader)
			return;
		
		if (!m_traderData || !m_traderData.m_items)
			return;
		
		int nextItemIndex = -1;
		foreach ( string classname, float quantity : m_traderData.m_items )
		{
			ItemBase item = ItemBase.Cast( GetGame().CreateObject(classname, "0 0 0", true, false, false) );
			if (item)
			{
				nextItemIndex = InitItemBuy(nextItemIndex + 1, item, classname, quantity, pluginTrader);
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
		
		ref ButtonWidget actionButton = ButtonWidget.Cast( itemBuy.FindAnyWidget( "ItemActionButton" ) );
		actionButton.SetUserData(new Param2<string, float>(classname, quantity));
		actionButton.SetUserID(2001);
		
		ref ItemPreviewWidget previewWidget = ItemPreviewWidget.Cast( itemBuy.FindAnyWidget( "ItemPreviewWidget" ) );		
		previewWidget.SetItem(item);
		previewWidget.SetView(item.GetViewIndex());
		previewWidget.SetModelPosition(Vector(0,0,1));
		m_previewItemsCache.Insert(item);
		
		WidgetSetWidth(itemBuy, "ItemNameWidget", contentWidth - 220);
		WidgetTrySetText(itemBuy, "ItemNameWidget", item.GetDisplayName());
		WidgetTrySetText(itemBuy, "ItemPriceWidget", pluginTrader.CalculateBuyPrice(m_traderInfo, classname, quantity).ToString());		
		WidgetTrySetText(itemBuy, "ItemQuantityWidget", FormatBuyQuantityStr(quantity) + "/" + pluginTrader.CalculateTraiderItemQuantityMax(m_traderInfo, classname));		
		
		m_buyWidgetsCache.Insert(itemBuy);
		return index;
	}
	
	string FormatBuyQuantityStr(float quantity)
	{
		int quantityInt = (int)(quantity * 10.0);
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
		ref array<ItemBase> result = new array<ItemBase>;
		GetSelectedSellItems(result);
		foreach (ItemBase item : result)
		{
			value = value + pluginTrader.CalculateSellPrice(m_traderInfo, m_traderData, item);
		}
		delete result;
		
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
			m_progressNegative.SetCurrent(Math.Min(100, value));
			m_barterBtn.Enable(false);
		}
		else
		{
			m_progressPositive.SetCurrent(0);
			m_progressNegative.SetCurrent(0);
			m_barterBtn.Enable(true);
		}
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
	
	override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/TraderMenu.layout" );
		
		m_sellItemsPanel = ScrollWidget.Cast( layoutRoot.FindAnyWidget( "SellItemsPanel" ) );
		m_buyItemsPanel = ScrollWidget.Cast( layoutRoot.FindAnyWidget( "BuyItemsPanel" ) );
		m_progressPositive = SimpleProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "ProgressPositive" ) );
		m_progressNegative = SimpleProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "ProgressNegative" ) );
		m_barterBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "TradeButton" ) );
		
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

		delete m_sellWidgetsCache;
		delete m_buyWidgetsCache;
				
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
				btn.SetUserID(1002);
			}
			else
			{
				back.SetColor(ARGB(200, 25, 25, 25));
				btn.SetUserID(1001);
			}
		}
		
		UpdateCurrentPriceProgress();
	}
	
	private void DoBarter()
	{
		PluginTrader pluginTrader = PluginTrader.Cast(GetPlugin(PluginTrader));
		if (!pluginTrader)
			return;
		
		ref array<ItemBase> sellItems = new array<ItemBase>;
		GetSelectedSellItems(sellItems);
		pluginTrader.DoBarter(m_traderId, sellItems);
		delete sellItems;
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
			else if ( item_base.IsInherited( Magazine ) )
			{
				Magazine magazine_item;
				Class.CastTo(magazine_item, item_base);
				
				WidgetTrySetText( root_widget, "ItemQuantityWidget",  magazine_item.GetAmmoCount().ToString() + "/" + magazine_item.GetAmmoMax().ToString() + " " + "#inv_inspect_pieces" );
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