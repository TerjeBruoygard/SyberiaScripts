class TurnSyringeFillLambda : TurnItemIntoItemLambda
{
    bool m_dirty;
    string m_medSolutionClassname;
    
    void TurnSyringeFillLambda (EntityAI old_item, string new_item_type, PlayerBase player, ItemBase medSolutionItem, bool dirty)
	{
        m_dirty = dirty;
        m_medSolutionClassname = medSolutionItem.GetType();
		SetTransferParams();
	}
};