modded class EmoteManager
{
	int GetCurrentEmoteID()
	{
		return m_CurrentGestureID;
	}
	
	bool IsPlayerSleeping()
	{
		return GetCurrentEmoteID() == EmoteConstants.ID_EMOTE_LYINGDOWN;
	}
};