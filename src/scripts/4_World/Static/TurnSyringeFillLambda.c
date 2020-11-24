class TurnSyringeFillLambda : TurnItemIntoItemLambda
{
    bool m_dirty;
    ItemBase m_medSolutionItem;
	
	void InitValues(ItemBase medSolutionItem, bool dirty)
	{
		m_dirty = dirty;
        m_medSolutionItem = medSolutionItem;
	}
};