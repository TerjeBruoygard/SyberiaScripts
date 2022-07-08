modded class WoodBase
{
    void GetMaterialAndQuantityMap(ItemBase item, out map<string,int> output_map)
	{
		if ( IsTree() && item && item.KindOf("Knife") && m_BarkType != "" )
		{
			output_map.Insert(m_BarkType,1);
		}
		else
		{
			if (m_BarkType != "") output_map.Insert(m_BarkType,2);
			if (m_PrimaryOutput != "") output_map.Insert(m_PrimaryOutput,1);
		}
	}
};