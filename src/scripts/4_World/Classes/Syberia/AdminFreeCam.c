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
	
	private static float m_moveSpeed = 1;
	private bool m_moveForward, m_moveBackward, m_moveLeft, m_moveRight, m_moveUp, m_moveDown, m_moveShift;

	void AdminFreeCam()
	{
		m_moveForward = false;
		m_moveBackward = false;
		m_moveLeft = false;
		m_moveRight = false;
		m_moveDown = false;
		m_moveUp = false;
		m_moveShift = false;
		SetEventMask( EntityEvent.FRAME );
	}
	
	void HandleKey(int key, bool state)
	{
		if (key == KeyCode.KC_W) m_moveForward = state;
		if (key == KeyCode.KC_S) m_moveBackward = state;
		if (key == KeyCode.KC_A) m_moveLeft = state;
		if (key == KeyCode.KC_D) m_moveRight = state;
		if (key == KeyCode.KC_Z) m_moveDown = state;
		if (key == KeyCode.KC_Q) m_moveUp = state;
		if (key == KeyCode.KC_LSHIFT) m_moveShift = state;
		
		if (!state)
		{
			if (key == KeyCode.KC_SUBTRACT) m_moveSpeed = Math.Clamp(m_moveSpeed / 2, 0.05, 10);
			if (key == KeyCode.KC_ADD) m_moveSpeed = Math.Clamp(m_moveSpeed * 2, 0.05, 10);
		}
	}
	
	override void EOnFrame( IEntity other, float timeSlice )
	{
		vector OldOrientation = GetOrientation();
		vector oldPos    = GetPosition();
		vector oldDir    = GetDirection();

		Input input = GetGame().GetInput();
		
		float forward = 0;
		if (m_moveForward) forward = forward + 1;
		if (m_moveBackward) forward = forward - 1;
		
		float strafe = 0;
		if (m_moveLeft) strafe = strafe - 1;
		if (m_moveRight) strafe = strafe + 1;
		
		float altitude = 0;
		if (m_moveUp) altitude = altitude + 1;
		if (m_moveDown) altitude = altitude - 1;
		
		float yawDiff = input.LocalValue( "UAAimLeft" ) - input.LocalValue( "UAAimRight" );
		float pitchDiff = input.LocalValue( "UAAimDown" ) - input.LocalValue( "UAAimUp" );

		float local_camspeed = CAM_SPEED * m_moveSpeed;
		if ( m_moveShift ) local_camspeed = local_camspeed * 3;
		
		vector up = vector.Up;
		vector direction = GetDirection();
		vector directionAside = vector.Up * direction;
		
		up = up * altitude * local_camspeed;
		direction = direction * forward * local_camspeed;
		directionAside = directionAside * strafe * local_camspeed;

		localVelocity = localVelocity * CAM_MOVE_DRAG;
		localVelocity = localVelocity + (direction + directionAside + up) * timeSlice;

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