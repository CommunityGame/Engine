#include "Window.hpp"

bool	Window::_glfwIsInit = false;
int		Window::_nbWindow = 0;

Window::Window( void )
{
	return ;
}

Window::~Window( void )
{
	glfwDestroyWindow( this->_GLFWwindow );
	this->_GLFWwindow = nullptr;
	Window::_nbWindow--;

	if ( Window::_nbWindow <= 0 )
	{
		glfwTerminate();
		Window::_glfwIsInit = false;
	}

	return ;
}

Window::Window( int width, int height, std::string const & title ) :
	_width( width ),
	_height( height ),
	_title( title )
{
	GLFWwindow *	window;

	if ( ! Window::_glfwIsInit )
		Window::initGLFW();

	this->_GLFWwindow = glfwCreateWindow( this->_width, this->_height, this->_title.c_str(), NULL, NULL );

	if ( ! this->_GLFWwindow )
	{
		this->_GLFWwindow = nullptr;
		throw ( EngineException( "Error: create GLFW window" ) );
	}
	Window::_nbWindow++;
	return ;
}

/*
* FUNCTIONS
*/
void				Window::refresh( void )
{
	glfwSwapBuffers( this->_GLFWwindow );
}

/*
* STATIC FUNCTIONS
*/
Window *			Window::create( int width, int height, std::string const & title )
{
	Window *		window = new Window( width, height, title );

	return ( window );
}

void				Window::initGLFW( void )
{
	if ( ! glfwInit() )
		throw ( EngineException( "Error: init GLFW" ) );

	//TODO: logger, glfwGetVersion( major, minor, rev );

	return ;
}

/*
* GETTER
*/
int 				Window::getWidth( void ) const
{
	return ( this->_width );
}

int 				Window::getHeight( void ) const
{
	return ( this->_height );
}

std::string			Window::getTitle( void ) const
{
	return ( this->_title );
}

GLFWwindow * 		Window::getGLFWWindow( void ) const
{
	return ( this->_GLFWwindow );
}

bool				Window::isCloseRequested( void ) const
{
	return ( glfwWindowShouldClose( this->_GLFWwindow ) == 1 );
}


/*
* SETTER
*/
