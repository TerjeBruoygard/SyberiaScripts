class SyberiaSoundEmitter extends House
{
	SoundOnVehicle m_soundEffect;
	
	void SyberiaSoundEmitter()
	{		
		if ( GetGame().IsServer() )
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater(Delete, GetLifeTime(), false);
		}
		
		if ( GetGame().IsClient() )
		{
			PlaySoundInternal();
		}
	}
	
	void ~SyberiaSoundEmitter() 
	{
		if ( GetGame().IsClient() )
		{			
			if ( m_soundEffect )
			{
				GetGame().ObjectDelete( m_soundEffect );
				m_soundEffect = null;
			}
		}
	}
	
	private void Delete()
	{
		if ( GetGame().IsServer() )
		{
			GetGame().ObjectDelete( this );
		}
	}
	
	private void PlaySoundInternal()
	{
		if ( GetGame().IsClient() )
		{
			m_soundEffect = PlaySound(GetSound(), GetRange(), true);	
		};		
	}
	
	protected int GetLifeTime()
	{
		float sec = GetGame().ConfigGetFloat("CfgVehicles " + GetType() + " emitterLifetime");
		return (int)(sec * 1000);
	}
	
	protected float GetRange()
	{
		return GetGame().ConfigGetFloat("CfgVehicles " + GetType() + " emitterRange");
	}
	
	protected string GetSound()
	{
		return GetGame().ConfigGetTextOut("CfgVehicles " + GetType() + " emitterSound");
	}
	
	static void Spawn(string type, vector pos)
	{
		GetGame().CreateObject(type, pos);
	}
};