#include "Input.hpp"

shared_ptr<GLWindow>	Input::_window( nullptr );
bool		Input::_keyPressed[GLFW_KEY_LAST];
bool		Input::_mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST];
Vec2f		Input::_scrollOffset;

const std::string	Input::TAG = "Input";

void			scrollCallback( GLFWwindow * win, double xOffset, double yOffset )
{
	Input::setScrollOffset( Vec2f( (float)xOffset, (float)yOffset ) );
}

void			Input::init( shared_ptr<GLWindow> const & window )
{
	glfwSetScrollCallback( window->getGLFWwindow(), scrollCallback );
}

void			Input::pollEvents( shared_ptr<GLWindow> const & window )
{
	Input::_window = window;
	glfwPollEvents();
	for ( int i = 0; i < GLFW_KEY_LAST; ++i )
		Input::_keyPressed[i] = (bool) glfwGetKey( window->getGLFWwindow(), i ) == GLFW_PRESS;
	for ( int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i )
		Input::_mouseButtonPressed[i] = (bool) glfwGetMouseButton( window->getGLFWwindow(), i ) == GLFW_PRESS;
}

// SETTER
void			Input::setCursor( bool visible )
{
	if ( Input::_window == nullptr )
	{
		Logger::e( TAG, "No window detected, wait a poolEvents" );
		return ;
	}
	glfwSetInputMode( Input::_window->getGLFWwindow(), GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED );
}

void			Input::setMousePosition( Vec2f pos )
{
	if ( Input::_window == nullptr )
	{
		Logger::e( TAG, "No window detected, wait a poolEvents" );
		return ;
	}
	glfwSetCursorPos( Input::_window->getGLFWwindow(), pos.getX(), pos.getY() );
}

void			Input::setScrollOffset( Vec2f offset )
{
	Input::_scrollOffset = offset;
}

// GETTER
bool			Input::isKeyPressed( int key )
{
	return ( Input::_keyPressed[key] );
}

bool			Input::isMouseButtonPressed( int button )
{
	return ( Input::_mouseButtonPressed[button] );
}

Vec2f			Input::getMousePosition( void )
{
	double	x, y;
	if ( Input::_window == nullptr )
	{
		Logger::e( TAG, "No window detected, wait a poolEvents" );
		return ( Vec2f( 0, 0 ) );
	}
	glfwGetCursorPos( Input::_window->getGLFWwindow(), &x, &y );
	return ( Vec2f( (float)x, (float)y ) );
}

Vec2f			Input::getWindowCenter( void )
{
	if ( Input::_window == nullptr )
	{
		Logger::e( TAG, "No window detected, wait a poolEvents" );
		return ( Vec2f( 0, 0 ) );
	}
	return ( Vec2f( Input::_window->getWidth() / 2.0f, Input::_window->getHeight() / 2.0f ) );
}

Vec2f			Input::getScrollOffset( void )
{
	return ( Input::_scrollOffset );
}

bool			Input::isCloseRequested( void )
{
	if ( Input::_window == nullptr )
	{
		Logger::e( TAG, "No window detected, wait a poolEvents" );
		return ( false );
	}
	return ( glfwWindowShouldClose( Input::_window->getGLFWwindow() ) == 1 );
}

bool			Input::isJoystickPresent( int joystick )
{
	return ( glfwJoystickPresent( joystick ) == 1 );
}

std::string		Input::getJoystickName( int joystick )
{
	return ( std::string( glfwGetJoystickName( joystick ) ) );
}

bool			Input::isJoystickButtonPressed( int joystick, int button )
{
	int count;
	const unsigned char *	buttons;

	buttons = glfwGetJoystickButtons( joystick, &count );
	if ( count < button || button < 0 )
		return ( false );
	return ( buttons[button] );
}

float			Input::getJoystickPressure( int joystick, int button, int direction )
{
	int count;
	const float *	buttons;

	buttons = glfwGetJoystickAxes( joystick, &count );
	if ( count < button || button < 0 )
		return ( 0 );

	int index1 = ( button == LEFT_STICKER ) ? 0 : ( button == RIGHT_STICKER ) ? 3 : ( direction == LEFT ) ? 2 : 5;
	int index2 = ( button == LEFT_STICKER ) ? 1 : 4;
	if ( direction == LEFT )
		return ( ( button == TRIGGER ) ? buttons[index1] : -buttons[index1] );
	else if ( direction == RIGHT )
		return ( buttons[index1] );
	else if ( direction == UP )
		return ( -buttons[index2] );
	else if ( direction == DOWN )
		return ( buttons[index2] );
	return ( 0 );
}

Vec2f		Input::getJoystickDirection( int joystick, int button )
{
	int count;
	const float *	buttons;

	if ( ! ( button == LEFT_STICKER || button == RIGHT_STICKER ) )
		return ( Vec2f( 0, 0 ) );
	buttons = glfwGetJoystickAxes( joystick, &count );

	for ( int i = 0; i < count; ++i )
		std::cout << buttons[i] << ", ";
	std::cout << std::endl;
	int index = ( button == LEFT_STICKER ) ? 0 : 3;
	return ( Vec2f( buttons[index], -buttons[index + 1] ) );
}
