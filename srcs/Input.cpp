#include "Input.hpp"

Input::Input( Window * window ) :
	_window( window )
{
	return ;
}

bool			Input::isKeyDown( int key ) const
{
	return ( glfwGetKey( this->_window->getGLFWwindow(), key ) == GLFW_PRESS );
}

bool			Input::isKeyUp( int key ) const
{
	return ( glfwGetKey( this->_window->getGLFWwindow(), key ) == GLFW_RELEASE );
}

bool			Input::isCloseRequested( void ) const
{
	return ( glfwWindowShouldClose( this->_window->getGLFWwindow() ) == 1 );
}

void			Input::pollEvents( void ) const
{
	glfwPollEvents();
}
