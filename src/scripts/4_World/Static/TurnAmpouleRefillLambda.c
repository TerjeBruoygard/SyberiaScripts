class TurnAmpouleRefillLambda : TurnItemIntoItemLambda
{
    ItemBase m_ampouleSource;
	
	void InitValues(ItemBase ampouleSource)
	{
        m_ampouleSource = ampouleSource;
	}
};