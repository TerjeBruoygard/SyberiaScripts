class PluginTrader extends PluginBase
{
	ref SybTraderMenu m_traderMenu;
	
	override void OnInit()
	{
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_OPEN_TRADE_MENU, this, "RpcRequstOpen"); 
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_ACTION_TRADER, this, "RpcResponseTraderAction"); 
	}

	void CloseTraderMenu()
	{
		if (m_traderMenu && m_traderMenu.m_active)
		{
			GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_CLOSE_TRADER_MENU, new Param1<int>(m_traderMenu.m_traderId));
			m_traderMenu.m_active = false;		
		}
	}
	
	void RpcRequstOpen(ref ParamsReadContext ctx, ref PlayerIdentity sender)
    {   		
		if (m_traderMenu && m_traderMenu.m_active)
		{
			m_traderMenu.m_active = false;
		}
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (GetGame().GetUIManager().GetMenu() != NULL || !player || !player.CanOpenSyberiaUI())
		{
			return;
		}
		
		Param3<int, ref PluginTrader_Trader, ref PluginTrader_Data> clientData;
       	if ( !ctx.Read( clientData ) ) return;
		
		m_traderMenu = new SybTraderMenu;
		m_traderMenu.InitMetadata(clientData.param1, clientData.param2, clientData.param3);
		GetGame().GetUIManager().ShowScriptedMenu( m_traderMenu, NULL );
	}
	
	void RpcResponseTraderAction(ref ParamsReadContext ctx, ref PlayerIdentity sender)
	{
		Param1<ref PluginTrader_Data> clientData;
       	if ( !ctx.Read( clientData ) ) return;
		
		if (m_traderMenu && m_traderMenu.m_active)
		{
			m_traderMenu.UpdateMetadata(clientData.param1);
		}
	}
	
	int CalculateSellPrice(ref PluginTrader_Trader trader, ref PluginTrader_Data data, ItemBase item)
	{
		if (!item)
		{
			return 0;
		}
		
		int healthlevel = item.GetHealthLevel();
		if (healthlevel > GameConstants.STATE_WORN)
		{
			return 0;
		}
		
		string classname = item.GetType();
		float traderTotalQuantity;
		if (!data.m_items.Find(classname, traderTotalQuantity))
		{
			traderTotalQuantity = 0;
		}
		
		float itemQuantity01 = CalculateItemQuantity01(item);
		float resultPrice = CalculateBuyPrice(trader, classname, traderTotalQuantity + itemQuantity01);	
		resultPrice = resultPrice - (trader.m_storageCommission * resultPrice);	
		resultPrice = resultPrice * CalculateItemQuantity01(item);
		
		if (healthlevel == GameConstants.STATE_WORN)
		{
			resultPrice = resultPrice * trader.m_dumpingByBadQuality;
		}
		
		return (int)Math.Max(0, Math.Floor(resultPrice));
	}
	
	int CalculateBuyPrice(ref PluginTrader_Trader trader, string classname, float quantity)
	{
		float itemMaxQuantity = CalculateTraiderItemQuantityMax(trader, classname);		
		quantity = Math.Min(quantity, itemMaxQuantity);
		float resultPrice = CalculateDumping(trader.m_dumpingByAmountAlgorithm, trader.m_dumpingByAmountModifier, (int)quantity, (int)itemMaxQuantity);
		resultPrice = 1000 * resultPrice;
		return (int)Math.Max(1, Math.Floor(resultPrice));
	}
	
	float CalculateTraiderItemQuantityMax(ref PluginTrader_Trader trader, string classname)
	{
		vector itemSize = "1 1 0";
		if (GetGame().ConfigIsExisting(CFG_VEHICLESPATH + " " + classname))
		{
			itemSize = GetGame().ConfigGetVector( CFG_VEHICLESPATH + " " + classname + " itemSize" );
		}
		else if (GetGame().ConfigIsExisting(CFG_MAGAZINESPATH + " " + classname))
		{
			itemSize = GetGame().ConfigGetVector( CFG_MAGAZINESPATH + " " + classname + " itemSize" );
		}
		else if (GetGame().ConfigIsExisting(CFG_WEAPONSPATH + " " + classname))
		{
			itemSize = GetGame().ConfigGetVector( CFG_WEAPONSPATH + " " + classname + " itemSize" );
		}
		
		int itemCapacity = (int)Math.Max(1, itemSize[0] * itemSize[1]);
		return Math.Round(((float)trader.m_storageMaxSize) / itemCapacity);
	}
	
	float CalculateItemQuantity01(ItemBase item)
	{
		float item_quantity = item.GetQuantity();
		int max_quantity = item.GetQuantityMax();
		if (max_quantity > 0)
		{
			if ( item.IsInherited( Ammunition_Base ))
			{
				Magazine magazine_item;
				Class.CastTo(magazine_item, item);
				return (float)magazine_item.GetAmmoCount() / (float)magazine_item.GetAmmoMax();
			}
			else if ( item.IsInherited( Magazine ) )
			{
				return 1;
			}
			else
			{
				return Math.Min(item_quantity, max_quantity) / (float)max_quantity;
			}
		}
		
		return 1;
	}
	
	float CalculateBuyMaxQuantity(ref PluginTrader_Trader traderInfo, string classname)
	{
		return Math.Max(1, CalculateTraiderItemQuantityMax(traderInfo, classname) * traderInfo.m_buyMaxQuantityPercent);
	}
	
	float CalculateItemSelectedQuantityStep(string classname)
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
			
			if ( stackedUnits == "pc." )
			{
				return 1 / maxStackSize;
			}
			else if ( GetGame().IsKindOf(classname, "Ammunition_Base") )
			{
				return 1 / maxStackSize;
			}
		}
		
		return 1;
	}
	
	float CalculateDumping(string algorithm, float modifier, float value, float max)
	{
		return Math.Lerp(1, modifier, (value / max));
	}
	
	void DoBarter(int traderId, ref array<ItemBase> sellItems)
	{
		GetSyberiaRPC().SendToServer(SyberiaRPC.SYBRPC_ACTION_TRADER, new Param2<int, ref array<ItemBase>>(traderId, sellItems));
	}
	
	override void OnDestroy()
	{
		
	}
};

class PluginTrader_Trader
{
	int m_traderId;
    ref array<string> m_purchaseFilter;
    ref array<string> m_saleFilter;
	int m_storageMaxSize;
    float m_storageCommission;
    string m_dumpingByAmountAlgorithm;
    float m_dumpingByAmountModifier;
    float m_dumpingByBadQuality;
	float m_saleMaxQuantityPercent;
	float m_buyMaxQuantityPercent;
	
	void ~PluginTrader_Trader()
	{
		if (m_purchaseFilter)
		{
			delete m_purchaseFilter;
		}
		
		if (m_saleFilter)
		{
			delete m_saleFilter;
		}
	}
};

class PluginTrader_Data
{
	ref map<string, float> m_items;
	
	void ~PluginTrader_Data()
	{
		if (m_items)
		{
			delete m_items;
		}
	}
};