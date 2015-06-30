#include "CameraControl.hpp"

CameraControl::CameraControl( void ) :
	_motion( 0, 0, 0 ),
	_rotation(),
	_mouseLocked( false ),
	_speed( 1 ),
	_oldMousePos( 0, 0 )
{
	return ;
}

CameraControl::~CameraControl( void )
{
	return ;
}

void CameraControl::input( Input & input, double delta )
{
	_motion = Vec3f( 0, 0, 0 );
	if ( input.isKeyPressed( GLFW_KEY_W ) )
		_motion += getTransform().getRotation().getForward();
	if ( input.isKeyPressed( GLFW_KEY_S ) )
		_motion += getTransform().getRotation().getBack();
	if ( input.isKeyPressed( GLFW_KEY_A ) )
		_motion += getTransform().getRotation().getLeft();
	if ( input.isKeyPressed( GLFW_KEY_D ) )
		_motion += getTransform().getRotation().getRight();
	if ( input.isKeyPressed( GLFW_KEY_SPACE ) )
		_motion += getTransform().getRotation().getUp();
	if ( input.isKeyPressed( GLFW_KEY_LEFT_SHIFT ) )
		_motion += getTransform().getRotation().getDown();
	this->_motion.normalize();

	if ( input.isKeyPressed( GLFW_KEY_ESCAPE ) )
	{
		input.setCursor( true );
		this->_rotation = Quatf();
		this->_mouseLocked = false;
	}

	if ( this->_mouseLocked )
	{
		Vec2d deltaPos = input.getMousePosition() - this->_oldMousePos;
		this->_oldMousePos = input.getMousePosition();

		bool rotY = deltaPos.getX() != 0;
		bool rotX = deltaPos.getY() != 0;

		this->_rotation = Quatf();
		if ( rotY )
			this->_rotation *= Quatf( Vec3f( 0, 1, 0 ), TO_RADIANS( (float)deltaPos.getX() * this->_speed * delta ) );
		if ( rotX )
			this->_rotation *= Quatf( getTransform().getRotation().getRight(), TO_RADIANS( (float)deltaPos.getY() * this->_speed * delta ) );
		this->_rotation.normalize();
	}

	if ( input.isMouseButtonPressed( GLFW_MOUSE_BUTTON_LEFT ) )
	{
		this->_oldMousePos = input.getMousePosition();
		input.setCursor( false );
		this->_mouseLocked = true;
	}
	return ;
}

void CameraControl::update( double delta )
{
	Transformf	*transform;

	transform = &getTransform();
	if ( this->_motion != Vec3f( 0, 0, 0 ) )
		transform->translate( this->_motion * this->_speed * delta );
	if ( this->_rotation != Quatf() )
		transform->rotate( this->_rotation );
	return ;
}

void CameraControl::setSpeed( float speed )
{
	this->_speed = speed;
}
