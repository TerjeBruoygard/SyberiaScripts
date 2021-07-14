class TurnSyringeFillLambda : TurnItemIntoItemLambda
{
    ItemBase m_medSolutionItem;
	
	void InitValues(ItemBase medSolutionItem)
	{
        m_medSolutionItem = medSolutionItem;
	}
};