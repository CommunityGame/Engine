#include <sstream>
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

	std::stringstream ss;
	ss << "Destroy window: " << this->_title << " [" << this->_width << " x " << this->_height << "]";
	Logger::i( ss.str() );
	return ;
}

Window::Window( int width, int height, std::string const & title ) :
	_width( width ),
	_height( height ),
	_title( title )
{
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

// FUNCTIONS
void				Window::refresh( void ) const
{
	glfwSwapBuffers( this->_GLFWwindow );
}

// STATIC FUNCTIONS
Window *			Window::create( int width, int height, std::string const & title )
{
	Window *		window = new Window( width, height, title );

	std::stringstream ss;
	ss << "Create window: " << title << " [" << width << " x " << height << "]";
	Logger::i( ss.str() );

	return ( window );
}

void				Window::initGLFW( void )
{
	if ( ! glfwInit() )
		throw ( EngineException( "Error: init GLFW" ) );

	int		major;
	int		minor;
	int		rev;

	glfwGetVersion( & major, & minor, & rev );

	std::stringstream ss;
	ss << "Init GLFW " << major << "." << minor << "." << rev;
	Logger::i( ss.str() );

	return ;
}

// GETTER
int					Window::getWidth( void ) const
{
	return ( this->_width );
}

int					Window::getHeight( void ) const
{
	return ( this->_height );
}

std::string			Window::getTitle( void ) const
{
	return ( this->_title );
}

GLFWwindow *		Window::getGLFWwindow( void ) const
{
	return ( this->_GLFWwindow );
}

// SETTER
void				Window::setTitle( std::string const & title )
{
	this->_title = title;
	glfwSetWindowTitle( this->_GLFWwindow, title.c_str() );
	return ;
}

void				Window::setSize( int width, int height )
{
	this->_width = width;
	this->_height = height;
	glfwSetWindowSize( this->_GLFWwindow, width, height );
}
