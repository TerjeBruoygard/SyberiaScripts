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