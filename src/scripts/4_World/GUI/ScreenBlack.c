class ScreenBlack extends ScreenBase
{
	void ScreenBlack()
	{

	}
	
	void ~ScreenBlack()
	{

	}
	
    override Widget Init()
    {
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "SyberiaScripts/layout/ScreenBlack.layout" );	
        return layoutRoot;
    }
}