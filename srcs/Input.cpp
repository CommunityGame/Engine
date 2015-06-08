#include "Input.hpp"

Input::Input( Window * window ) :
	_window( window )
{
	return ;
}

bool			Input::isKeyPressed( int key ) const
{
	return ( this->_keyPressed[key] );
}

bool			Input::isMouseButtonPressed( int button ) const
{
	return ( this->_mouseButtonPressed[button] );
}

Vec2d			Input::getMousePosition( void ) const
{
	double	x, y;

	glfwGetCursorPos( this->_window->getGLFWwindow(), &x, &y );
	return ( Vec2d( x, y ) );
}

bool			Input::isCloseRequested( void ) const
{
	return ( glfwWindowShouldClose( this->_window->getGLFWwindow() ) == 1 );
}

void			Input::pollEvents( void )
{
	glfwPollEvents();
	for ( int i = 0; i < GLFW_KEY_LAST; ++i )
		this->_keyPressed[i] = (bool) glfwGetKey( this->_window->getGLFWwindow(), i ) == GLFW_PRESS;
	for ( int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i )
		this->_mouseButtonPressed[i] = (bool) glfwGetMouseButton( this->_window->getGLFWwindow(), i ) == GLFW_PRESS;
}

void			Input::setCursor( bool visible )
{
	glfwSetInputMode( this->_window->getGLFWwindow(), GLFW_CURSOR, visible );
}

void Input::setMousePosition( Vec2d pos )
{
	glfwSetCursorPos( this->_window->getGLFWwindow(), pos.getX(), pos.getY() );
}
