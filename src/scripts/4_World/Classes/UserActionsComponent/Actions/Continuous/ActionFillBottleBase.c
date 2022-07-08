modded class ActionFillBottleBase
{
	override int GetLiquidType( PlayerBase player, ActionTarget target, ItemBase item )
	{
		vector pos = target.GetCursorHitPos();
		string surface_type = "";
		GetGame().SurfaceGetType(pos[0], pos[2], surface_type);
		if (surface_type == "nam_snow" || surface_type == "nam_lakeice_ext" || surface_type == "nam_lakewater_ext")
		{
			return LIQUID_WATER;
		}
		
		return super.GetLiquidType(player, target, item);
	}
};