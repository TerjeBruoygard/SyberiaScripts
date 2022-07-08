class SybTraderMenu extends UIScriptedMenu
{
	const float SELL_ITEM_DEPTH_OFFSET = 30;
	const float SELL_ITEM_HEIGHT_OFFSET = 2;
	
	bool m_active = false;
	bool m_dirty = false;
	
	int m_traderId;
	ref PluginTrader_Traider m_traderData;
	ref PluginTrader_Storage m_storageData;
	
	ref ScrollWidget m_sellItemsPanel;
	ref SimpleProgressBarWidget m_progressPositive;
	ref SimpleProgressBarWidget m_progressNegative;
	
	void InitMetadata(int traderId, ref PluginTrader_Traider traderData, ref PluginTrader_Storage storageData)
	{
		m_traderId = traderId;
		m_traderData = traderData;
		m_storageData = storageData;
	}
	
	void InitInventorySell()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (!player || !player.IsAlive())
			return;
		
		int nextItemIndex = -1;
		ItemBase item = ItemBase.Cast( player.GetItemInHands() );
		if (item)
		{
			nextItemIndex = InitItemSell(nextItemIndex + 1, 0, item);
		}
		
		for ( int i = 0; i < player.GetInventory().GetAttachmentSlotsCount(); ++i )
		{
			item = ItemBase.Cast( player.GetInventory().FindAttachment(player.GetInventory().GetAttachmentSlotId(i)) );
			if ( item )
			{
				nextItemIndex = InitItemSell(nextItemIndex + 1, 0, item);
			}
		}
	}
	
	int InitItemSell(int index, int depth, ItemBase item)
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
		
		ref ItemPreviewWidget previewWidget = ItemPreviewWidget.Cast( itemSell.FindAnyWidget( "ItemPreviewWidget" ) );		
		previewWidget.SetItem(item);
		previewWidget.SetView(item.GetViewIndex());
		previewWidget.SetModelPosition(Vector(0,0,1));
		
		WidgetSetWidth(itemSell, "ItemNameWidget", contentWidth - 220);
		WidgetTrySetText(itemSell, "ItemNameWidget", item.GetDisplayName());
		WidgetTrySetText(itemSell, "ItemPriceWidget", item.GetDisplayPrice());		
		UpdateItemInfoDamage(itemSell, item);
		UpdateItemInfoQuantity(itemSell, item);
		
		if (item.GetInventory() && depth < 8)
		{
			int i;
			for ( i = 0; i < item.GetInventory().GetAttachmentSlotsCount(); ++i )
			{
				ItemBase attachment = ItemBase.Cast( item.GetInventory().FindAttachment(item.GetInventory().GetAttachmentSlotId(i)) );
				if ( attachment )
				{
					index = InitItemSell(index + 1, depth + 1, attachment);
				}
			}
			
			if (item.GetInventory().GetCargo())
			{
				for ( i = 0; i < item.GetInventory().GetCargo().GetItemCount(); ++i )
				{
					ItemBase cargo = ItemBase.Cast( item.GetInventory().GetCargo().GetItem(i) );
					if ( cargo )
					{
						index = InitItemSell(index + 1, depth + 1, cargo);
					}
				}
			}
		}
		
		return index;
	}
	
	void SetCurrentPriceProgress(float value)
	{
		if (value > 0)
		{
			m_progressPositive.SetCurrent(Math.Min(100, value));
			m_progressNegative.SetCurrent(0);
		}
		else if (value < 0)
		{
			m_progressPositive.SetCurrent(0);
			m_progressNegative.SetCurrent(Math.Min(100, value));
		}
		else
		{
			m_progressPositive.SetCurrent(0);
			m_progressNegative.SetCurrent(0);
		}
	}
	
	override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/TraderMenu.layout" );
		
		m_sellItemsPanel = ScrollWidget.Cast( layoutRoot.FindAnyWidget( "SellItemsPanel" ) );
		m_progressPositive = SimpleProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "ProgressPositive" ) );
		m_progressNegative = SimpleProgressBarWidget.Cast( layoutRoot.FindAnyWidget( "ProgressNegative" ) );
		
		SetCurrentPriceProgress(0);
		InitInventorySell();
		
		m_active = true;
		m_dirty = true;
        return layoutRoot;
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_dirty)
		{
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
		
		Close();
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		super.OnClick(w, x, y, button);	

		if (button == MouseState.LEFT)
		{			
			ref Widget parent;
			if (w.GetUserID() == 1001) // sell item select
			{
				parent = w.GetParent();
				if (parent)
				{
					parent.SetColor(ARGB(200, 16, 87, 20));
					w.SetUserID(1002);
				}
			}
			else if (w.GetUserID() == 1002) // sell item unselect
			{
				parent = w.GetParent();
				if (parent)
				{
					parent.SetColor(ARGB(200, 25, 25, 25));
					w.SetUserID(1001);
				}
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
				if( item_quantity == 1 )
				{
					WidgetTrySetText( root_widget, "ItemQuantityWidget", item_quantity.ToString() + " " + "#inv_inspect_piece" );
				}
				else
				{
					WidgetTrySetText( root_widget, "ItemQuantityWidget", item_quantity.ToString() + " " + "#inv_inspect_pieces" );
				}		
			}
			else if( item_base.ConfigGetString("stackedUnit") == "percentage" )
			{
				quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );
				
				quantity_str = "#inv_inspect_remaining " + quantity_ratio.ToString() + "#inv_inspect_percent";
				WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_str );			
			}
			else if( item_base.ConfigGetString("stackedUnit") == "g" )
			{
				quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );
				
				quantity_str = "#inv_inspect_remaining " + quantity_ratio.ToString() + "#inv_inspect_percent";
				WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_str );			
			}
			else if( item_base.ConfigGetString("stackedUnit") == "ml" )
			{
				quantity_ratio = Math.Round( ( item_quantity / max_quantity ) * 100 );
				
				quantity_str = "#inv_inspect_remaining " + quantity_ratio.ToString() + "#inv_inspect_percent";
				WidgetTrySetText( root_widget, "ItemQuantityWidget", quantity_str );
			}
			else if ( item_base.IsInherited( Magazine ) )
			{
				Magazine magazine_item;
				Class.CastTo(magazine_item, item_base);
				
				if( magazine_item.GetAmmoCount() == 1 )
				{
					WidgetTrySetText( root_widget, "ItemQuantityWidget",  magazine_item.GetAmmoCount().ToString() + " " + "#inv_inspect_piece" );
				}
				else
				{
					WidgetTrySetText( root_widget, "ItemQuantityWidget",  magazine_item.GetAmmoCount().ToString() + " " + "#inv_inspect_pieces" );
				}
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