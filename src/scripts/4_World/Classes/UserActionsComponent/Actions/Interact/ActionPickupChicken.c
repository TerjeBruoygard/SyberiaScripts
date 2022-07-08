modded class ActionPickupChicken
{
    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
    {
        EntityAI entity = EntityAI.Cast(target.GetObject());
        return super.ActionCondition(player, target, item) && entity && !entity.IsSkinned();
    }
};