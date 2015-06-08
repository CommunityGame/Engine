#include "CameraControl.hpp"

CameraControl::CameraControl( void ) :
	_motion( 0, 0, 0 ),
	_rotation(),
	_mouseLocked( false ),
	_speed( 1 ),
	_windowCenter( 0, 0 )
{
	return ;
}

CameraControl::~CameraControl( void )
{
	return ;
}

void CameraControl::input( Input & input )
{
	_motion = Vec3f( 0, 0, 0 );
	if ( input.isKeyPressed( GLFW_KEY_W ) )
		_motion += Vec3f( 0, 0, -1 );
	if ( input.isKeyPressed( GLFW_KEY_S ) )
		_motion += Vec3f( 0, 0, 1 );
	if ( input.isKeyPressed( GLFW_KEY_A ) )
		_motion += Vec3f( -1, 0, 0 );
	if ( input.isKeyPressed( GLFW_KEY_D ) )
		_motion += Vec3f( 1, 0, 0 );
	if ( input.isKeyPressed( GLFW_KEY_SPACE ) )
		_motion += Vec3f( 0, 1, 0 );
	if ( input.isKeyPressed( GLFW_KEY_LEFT_SHIFT ) )
		_motion += Vec3f( 0, -1, 0 );
	if( input.isKeyPressed( GLFW_KEY_ESCAPE ) )
	{
		input.setCursor( true );
		this->_mouseLocked = false;
	}

	if ( this->_mouseLocked )
	{
		Vec2d deltaPos = input.getMousePosition() - this->_windowCenter;

		bool rotY = deltaPos.getX() != 0;
		bool rotX = deltaPos.getY() != 0;

		this->_rotation = Quatf();
		if ( rotY )
			getTransform().rotate( Vec3f( 0, 1, 0 ), TO_RADIANS( (float)deltaPos.getX() * this->_speed ) );
		if ( rotX )
			getTransform().rotate( getTransform().getRotation().getRight(), TO_RADIANS( (float)deltaPos.getY() * this->_speed ) );
		if ( rotY || rotX )
			input.setMousePosition( this->_windowCenter );
	}

	if ( input.isMouseButtonPressed( GLFW_MOUSE_BUTTON_LEFT ) )
	{
		input.setCursor( false );
		input.setMousePosition( this->_windowCenter );
		this->_mouseLocked = true;
	}
	return ;
}

void CameraControl::update( double delta )
{
	Transformf	*transform;

	transform = &getTransform();
	if ( this->_motion != Vec3f( 0, 0, 0 ) )
		transform->translate( this->_motion.rotate( transform->getRotation() ) * this->_speed );
//	if ( this->_rotation != Quatf() )
//		transform->rotate( this->_rotation );
	return ;
}

void CameraControl::setSpeed( float speed )
{
	this->_speed = speed;
}
