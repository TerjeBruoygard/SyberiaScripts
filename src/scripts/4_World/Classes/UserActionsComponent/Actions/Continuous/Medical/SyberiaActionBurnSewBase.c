modded class ActionBurnSewTarget
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return false;
	}
};

modded class ActionBurnSewSelf
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return false;
	}
};