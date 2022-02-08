class SybCustomRecipe extends RecipeBase
{
	void InitCustom(ref PluginRecipesManager_CustomRecipeData data)
	{
		m_Name = data.m_Name;
		m_IsInstaRecipe = (data.m_IsInstaRecipe == 1);
		m_AnimationLength = data.m_AnimationLength;
		m_Specialty = 0;

		for (int i = 0; i < MAX_NUMBER_OF_INGREDIENTS; i++)
		{
			m_MinQuantityIngredient[i] = data.m_MinQuantityIngredient[i];
			m_MaxQuantityIngredient[i] = data.m_MaxQuantityIngredient[i];
			m_MinDamageIngredient[i] = data.m_MinDamageIngredient[i];
			m_MaxDamageIngredient[i] = data.m_MaxDamageIngredient[i];
			m_IngredientAddHealth[i] = data.m_IngredientAddHealth[i];
			m_IngredientSetHealth[i] = data.m_IngredientSetHealth[i];
			m_IngredientAddQuantity[i] = data.m_IngredientAddQuantity[i];
			m_IngredientDestroy[i] = data.m_IngredientDestroy[i];
			m_IngredientUseSoftSkills[i] = false;
			
			ref array<string> tempArray = data.m_Ingredients[i];
			for (int q = 0; q < tempArray.Count(); q++)
			{
				InsertIngredient(i, tempArray.Get(q));
			}
		}
		
		for (int r = 0; r < data.m_ItemsToCreate.Count() && r < MAXIMUM_RESULTS; r++)
		{
			AddResult(data.m_ItemsToCreate[r]);
			m_ResultSetFullQuantity[r] = data.m_ResultSetFullQuantity[r];
			m_ResultSetQuantity[r] = data.m_ResultSetQuantity[r];
			m_ResultSetHealth[r] = data.m_ResultSetHealth[r];
			m_ResultInheritsHealth[r] = data.m_ResultInheritsHealth[r];
			m_ResultToInventory[r] = data.m_ResultToInventory[r];
			m_ResultInheritsColor[r] = -1;
			m_ResultReplacesIngredient[r] = -1;
			m_ResultUseSoftSkills[r] = false;
		}
		
		SybLog("CUSTOM RECIPE INITIALIZED: " + m_Name);
	}
};
