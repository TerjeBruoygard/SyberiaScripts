class WashFruits extends RecipeBase
{
	override void Init()
	{
		m_Name = "#syb_action_wash";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 0.5;//animation length in relative time units
		m_Specialty = -0.02;// value > 0 for roughness, value < 0 for precision
		
		
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"Inventory_Base");
		
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;// 0 = do nothing
		m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"Inventory_Base");
		
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
	}

	private bool CanDoInternal(ItemBase item1, ItemBase item2)
	{
        if (!item1)
		{
			return false;
		}
        
        if (!item1.IsFruit() && !item1.IsMushroom())
		{
			return false;
		}
		
		if (!item2 || item2.GetLiquidType() != LIQUID_WATER || item2.GetQuantity() < item2.GetDisinfectQuantity())
		{
			return false;
		}
		
		return true;
	}
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)//final check for recipe's validity
	{
		return CanDoInternal(ingredients[0], ingredients[1]) || CanDoInternal(ingredients[1], ingredients[0]);
	}

	private void DoInternal(ItemBase fruit, ItemBase waterContainer)
	{
		fruit.RemoveAgent(eAgents.FOOD_POISON);
		waterContainer.AddQuantity( -waterContainer.GetDisinfectQuantity(), false );
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		if (ingredients[0].IsFruit())
		{
			DoInternal(ingredients[0], ingredients[1]);
		}
		else if (ingredients[1].IsFruit())
		{
			DoInternal(ingredients[1], ingredients[0]);
		}
	}
};
