class SleepingBag_BaseColor : ItemBase
{
	override void OnPlacementComplete( Man player, vector position = "0 0 0", vector orientation = "0 0 0" )
    {        
        super.OnPlacementComplete( player, position, orientation );
        
        if ( GetGame().IsServer() )
        {
			PlayerBase pb = PlayerBase.Cast( player );
			string placedClassname = GetGame().ConfigGetTextOut("CfgVehicles " + GetType() + " placedName");
            Object sleepingBagPlacedObject = GetGame().CreateObject(placedClassname, pb.GetLocalProjectionPosition(), false );
            sleepingBagPlacedObject.SetPosition( position );
            sleepingBagPlacedObject.SetOrientation( orientation );

			string placedSound;
			if ( GetGame().ConfigGetText("CfgVehicles " + placedClassname + " placedSound", placedSound) )
			{
				SyberiaSoundEmitter.Spawn(placedSound, position);
			}          
        }    
    }
    
    override string GetLoopDeploySoundset()
    {
        return "";
    }
	
	override bool IsBasebuildingKit()
	{
		return true;
	}
    
    override void SetActions()
    {
        super.SetActions();
        
        AddAction(ActionTogglePlaceObject);
        AddAction(ActionPlaceObject);
    }
};

class SleepingBagPlacing : BaseBuildingBase
{
	
};

class SleepingBagPlaced_BaseColor : BaseBuildingBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionSleep);
		AddAction(ActionFoldBaseBuildingObject);
	}
	
	protected override string GetConstructionKitType()
	{
		return GetGame().ConfigGetTextOut("CfgVehicles " + GetType() + " packedName");
	}
	
	override void SetPartsAfterStoreLoad()
	{

	}
	
	override ItemBase CreateConstructionKit()
	{
		ItemBase result = super.CreateConstructionKit();
		if (result)
		{
			float health = GetHealth01("", "");
			result.SetHealth01("", "", health);
		}
		return result;
	}
};