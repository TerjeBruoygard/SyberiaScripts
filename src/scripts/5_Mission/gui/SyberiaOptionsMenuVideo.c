modded class OptionsMenuVideo
{
    override void OnPPQualityChanged( int value )
	{
        if (value == 0)
        {
            value = 1;
        }
        
		super.OnPPQualityChanged(value);
	}
};