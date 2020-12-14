modded class PluginRecipesManagerBase
{
    override void RegisterRecipies()
    {
        super.RegisterRecipies();
        RegisterRecipe(new CraftSyringeClear);
        RegisterRecipe(new CraftSyringeFill);
        RegisterRecipe(new CraftAmpouleRefill);
    }
};