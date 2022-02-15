modded class PluginRecipesManagerBase
{
    override void RegisterRecipies()
    {
        super.RegisterRecipies();
        RegisterRecipe(new CraftSyringeFill);
        RegisterRecipe(new CraftCombineSyb);
        RegisterRecipe(new WashFruits);
    }
};

modded class PluginRecipesManager
{
	override protected void CreateAllRecipes()
	{
		super.CreateAllRecipes();
		PostProcessingRecipes();
	}
	
	protected void PostProcessingRecipes()
	{
		GetSyberiaRPC().RegisterHandler(SyberiaRPC.SYBRPC_SYNC_CRAFTS, this, "OnReceiveSettings");
	}
	
	protected void OnReceiveSettings(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param2<ref array<string>, ref array<ref PluginRecipesManager_CustomRecipeData>> clientData;
       	if ( !ctx.Read( clientData ) ) return;	
		
		ref array<string> recipesToUnreg = clientData.param1;
		foreach (string disabledRecipeClass : recipesToUnreg)
		{
			UnregisterRecipe(disabledRecipeClass);
		}
		
		ref array<ref PluginRecipesManager_CustomRecipeData> customRecipes = clientData.param2;
		foreach (ref PluginRecipesManager_CustomRecipeData customRecipe : customRecipes)
		{
			ref SybCustomRecipe recipeObj = new SybCustomRecipe();
			recipeObj.InitCustom(customRecipe);
			RegisterRecipe(recipeObj);
		}
		
		GenerateRecipeCache();
	}
};

class PluginRecipesManager_CustomRecipeData
{
	string m_Name;
	int m_IsInstaRecipe;
	float m_AnimationLength;

	ref array<ref array<string>> m_Ingredients;
	ref array<float> m_MinQuantityIngredient;
	ref array<float> m_MaxQuantityIngredient;
	ref array<int> m_MinDamageIngredient;
	ref array<int> m_MaxDamageIngredient;
	ref array<float> m_IngredientAddHealth;
	ref array<float> m_IngredientAddQuantity;
	ref array<float> m_IngredientSetHealth;
	ref array<int> m_IngredientDestroy;
		
	ref array<int> m_ResultSetFullQuantity;
	ref array<float> m_ResultSetQuantity;
	ref array<float> m_ResultSetHealth;
	ref array<int> m_ResultToInventory;
	ref array<int> m_ResultInheritsHealth;
	ref array<string> m_ItemsToCreate;
};