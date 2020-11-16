class SyberiaMedicineBase extends Edible_Base
{

};

class TabletsBase extends SyberiaMedicineBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionForceConsumeSingle);
		AddAction(ActionConsumeSingle);
	}
};