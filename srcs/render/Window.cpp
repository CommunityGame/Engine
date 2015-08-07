#include <sstream>
#include "Window.hpp"

const std::string	Window::TAG = "Window";
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
	Logger::i( TAG, ss.str() );
	return ;
}

Window::Window( int width, int height, std::string const & title ) :
	_width( width ),
	_height( height ),
	_title( title )
{
	if ( ! Window::_glfwIsInit )
		Window::initGLFW();

	GLFWmonitor *			monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *		mode = glfwGetVideoMode( monitor );

	glfwWindowHint( GLFW_RED_BITS, mode->redBits );
	glfwWindowHint( GLFW_GREEN_BITS, mode->greenBits );
	glfwWindowHint( GLFW_BLUE_BITS, mode->blueBits );
	glfwWindowHint( GLFW_REFRESH_RATE, mode->refreshRate );

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_SAMPLES, 4 );

	this->_GLFWwindow = glfwCreateWindow( this->_width, this->_height, this->_title.c_str(), nullptr, nullptr );
	if ( ! this->_GLFWwindow )
	{
		this->_GLFWwindow = nullptr;
		throw ( EngineException( "Error: create GLFW window" ) );
	}

	if ( Window::_nbWindow == 0 )
	{
		glfwMakeContextCurrent( this->_GLFWwindow );
//		gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );
	}

	glfwSetWindowPos( this->_GLFWwindow, mode->width / 2 - this->_width / 2, mode->height / 2 - this->_height / 2 );
	return ;
}

// FUNCTIONS
void				Window::refresh( void ) const
{
	glfwSwapBuffers( this->_GLFWwindow );
}

// STATIC FUNCTIONS
shared_ptr<Window>		Window::create( int width, int height, std::string const & title )
{
	shared_ptr<Window> window( new Window( width, height, title ) );
	const GLubyte*	renderer = glGetString( GL_RENDERER );
	const GLubyte*	version = glGetString( GL_VERSION );
	const GLubyte*	glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

	std::stringstream ss;
	ss << "Create window: " << title << " [" << width << " x " << height << "]";
	Logger::i( TAG, ss.str() );
	ss.str( "" );
	ss << "Renderer: " << renderer;
	Logger::i( TAG, ss.str() );
	ss.str( "" );
	ss << "OpenGL version supported " << version;
	Logger::i( TAG, ss.str() );
	ss.str( "" );
	ss << "OpenGL shader language version supported " << glslVersion;
	Logger::i( TAG, ss.str() );

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

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
	Logger::i( TAG, ss.str() );

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

void Window::setVsync( bool vSync )
{
	glfwSwapInterval( (bool)vSync );
}

void	Window::setWidth( int width )
{
	this->_width = width;
}

void	Window::setHeight( int height )
{
	this->_height = height;
}


void Window::setWindowPos( int x, int y )
{
	glfwSetWindowPos( this->_GLFWwindow, x, y );
}

void Window::destroyWindow( void )
{
	glfwDestroyWindow( this->_GLFWwindow );
	this->_GLFWwindow = nullptr;
}
