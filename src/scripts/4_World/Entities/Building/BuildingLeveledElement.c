class BuildingLeveledElement extends BuildingElement
{
    string GetNextLevel()
    {
        return ConfigGetString("nextLevel");
    }
    
    string GetPrevLevel()
    {
        return ConfigGetString("prevLevel");
    }
};