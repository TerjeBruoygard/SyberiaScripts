int GetSyberiaTemperatureColor( int temperature, int alpha )
{
    float mod;
    if ( temperature < -10 )
	{
        return ARGB( alpha, 180, 180, 180 );
    }
	
    if ( temperature < 10 )
	{
        mod = temperature + 10;
        mod = (100 / 20) * mod;
		return ARGB( alpha, 180 - (int)mod, 180, 180 );
	}
    
    if ( temperature < 30 )
	{
        mod = temperature - 20;
        mod = (128 / 20) * mod;
		return ARGB( alpha, 127 + (int)mod, 155, 159 );
	}
    
    mod = Math.Clamp(temperature, 30, 330) - 30;
    mod = (128 / 300) * mod;
	return ARGB( alpha, 255, 129 - (int)mod, 129 - (int)mod);
}