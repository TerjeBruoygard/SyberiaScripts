modded class ActionSewTarget
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return false;
	}
};

modded class ActionSewSelf
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return false;
	}
};