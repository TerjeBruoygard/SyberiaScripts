class AdminFreeCam extends Camera
{
	protected float CAM_SPEED = 5.0;
	protected float CAM_MOVE_DRAG = 0.7;
	protected float CAM_MOUSE_SENSE = 0.8;
	protected float CAM_SMOOTHNESS = 0.8;
	protected float CAM_FOV = 1.0;	
	protected vector localVelocity;
	protected float  localyawVelocity;
	protected float  localpitchVelocity;
	
	private float m_SendUpdateAcc = 0.0;

	void AdminFreeCam()
	{
		SetEventMask( EntityEvent.FRAME );
	}
	
	override void EOnFrame( IEntity other, float timeSlice )
	{
		vector OldOrientation = GetOrientation();
		vector oldPos    = GetPosition();
		vector oldDir    = GetDirection();

		Input input = GetGame().GetInput();
		
		float forward  = input.LocalValue( "UAMoveForward" ) - input.LocalValue( "UAMoveBack" );
		float strafe   = input.LocalValue( "UAMoveRight" ) - input.LocalValue( "UAMoveLeft" );
		float yawDiff = input.LocalValue( "UAAimLeft" ) - input.LocalValue( "UAAimRight" );
		float pitchDiff = input.LocalValue( "UAAimDown" ) - input.LocalValue( "UAAimUp" );

		float local_camspeed = 5.0;
		if( input.LocalValue("UATurbo") )
			local_camspeed = local_camspeed * 3;
		
		vector direction = GetDirection();
		vector directionAside = vector.Up * direction;
		
		direction = direction * forward * local_camspeed;
		directionAside = directionAside * strafe * local_camspeed;

		localVelocity = localVelocity * CAM_MOVE_DRAG;
		localVelocity = localVelocity + (direction + directionAside) * timeSlice;

		vector newPos = oldPos + localVelocity;

		float surfaceY = GetGame().SurfaceY( newPos[0], newPos[2] ) + 0.15; //0.25
		if ( newPos[1] < surfaceY )
			newPos[1] = surfaceY;

		//Mouse Control
		localyawVelocity =  (localyawVelocity + yawDiff * CAM_MOUSE_SENSE);
		localpitchVelocity = (localpitchVelocity + pitchDiff * CAM_MOUSE_SENSE);

		vector OrientNew = OldOrientation;
		OrientNew[0] = OldOrientation[0] - Math.RAD2DEG * localyawVelocity * timeSlice;
		OrientNew[1] = OldOrientation[1] - Math.RAD2DEG * localpitchVelocity * timeSlice;

		localyawVelocity   *= CAM_SMOOTHNESS;
		localpitchVelocity *= CAM_SMOOTHNESS;

		if( OrientNew[1] < -89 )
			OrientNew[1] = -89;
			
		if( OrientNew[1] > 89 )
			OrientNew[1] = 89;
			
		//Update Position & rotation
		SetPosition(newPos);
		SetOrientation(OrientNew);
		
		if( m_SendUpdateAcc > 1 )
		{
			GetSyberiaRPC().SendToServer( SyberiaRPC.SYBRPC_ADMINTOOL_TELEPORT, new Param2< vector, int >( GetPosition(), 1 ) );
			m_SendUpdateAcc = 0;
		}
		
		m_SendUpdateAcc = m_SendUpdateAcc + timeSlice;
	}
};