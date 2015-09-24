#include <sstream>
#include <vg/vgu.h>
#include "GLWindow.hpp"

const std::string	GLWindow::TAG = "GLWindow";
bool	GLWindow::_glfwIsInit = false;
int		GLWindow::_nbWindow = 0;

GLWindow::GLWindow( void )
{
	return ;
}

GLWindow::~GLWindow( void )
{
	glfwDestroyWindow( this->_GLFWwindow );
	this->_GLFWwindow = nullptr;
	GLWindow::_nbWindow--;

	if ( GLWindow::_nbWindow <= 0 )
	{
		glfwTerminate();
		GLWindow::_glfwIsInit = false;
	}

	std::stringstream ss;
	ss << "Destroy window: " << this->_title << " [" << this->_width << " x " << this->_height << "]";
	Logger::i( TAG, ss.str() );
	return ;
}

GLWindow::GLWindow( int width, int height, std::string const & title ) :
	_width( width ),
	_height( height ),
	_title( title )
{
	if ( ! GLWindow::_glfwIsInit )
		GLWindow::initGLFW();

	GLFWmonitor *			monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *		mode = glfwGetVideoMode( monitor );

	glfwWindowHint( GLFW_RED_BITS, mode->redBits );
	glfwWindowHint( GLFW_GREEN_BITS, mode->greenBits );
	glfwWindowHint( GLFW_BLUE_BITS, mode->blueBits );
	glfwWindowHint( GLFW_REFRESH_RATE, mode->refreshRate );

//	glfwWindowHint( GLFW_VERSION_MAJOR, 3 );
//	glfwWindowHint( GLFW_VERSION_MINOR, 3 );
//	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
//	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
//	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
//	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_SAMPLES, 4 );

	this->_GLFWwindow = glfwCreateWindow( this->_width, this->_height, this->_title.c_str(), nullptr, nullptr );
	if ( ! this->_GLFWwindow )
	{
		this->_GLFWwindow = nullptr;
		throw ( EngineException( "Error: create GLFW window" ) );
	}

	if ( GLWindow::_nbWindow == 0 )
	{
		glfwMakeContextCurrent( this->_GLFWwindow );
//		gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );
	}

	vgCreateContextSH( width, height );

	glfwSetWindowPos( this->_GLFWwindow, mode->width / 2 - this->_width / 2, mode->height / 2 - this->_height / 2 );
	return ;
}

// FUNCTIONS
void				GLWindow::refresh( void ) const
{
	glfwSwapBuffers( this->_GLFWwindow );
}

// STATIC FUNCTIONS
shared_ptr<GLWindow>		GLWindow::create( int width, int height, std::string const & title )
{
	shared_ptr<GLWindow> window( new GLWindow( width, height, title ) );
	const GLubyte*	renderer = glGetString( GL_RENDERER );
	const GLubyte*	version = glGetString( GL_VERSION );
	const GLubyte*	glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

	int max = 1000;
//	glGetIntegerv(GL_EXTENSIONS, &max);

//	for(int i = 0; glGetStringi(GL_EXTENSIONS, i); i++)
//		std::cout << "POK:    " << glGetStringi(GL_EXTENSIONS, i) << std::endl;


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

	return ( window );
}

void				GLWindow::initGLFW( void )
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
int					GLWindow::getWidth( void ) const
{
	return ( this->_width );
}

int					GLWindow::getHeight( void ) const
{
	return ( this->_height );
}

std::string			GLWindow::getTitle( void ) const
{
	return ( this->_title );
}

GLFWwindow * GLWindow::getGLFWwindow( void ) const
{
	return ( this->_GLFWwindow );
}

// SETTER
void				GLWindow::setTitle( std::string const & title )
{
	this->_title = title;
	glfwSetWindowTitle( this->_GLFWwindow, title.c_str() );
	return ;
}

void				GLWindow::setSize( int width, int height )
{
	this->_width = width;
	this->_height = height;
	glfwSetWindowSize( this->_GLFWwindow, width, height );
}

void GLWindow::setVsync( bool vSync )
{
	glfwSwapInterval( (bool)vSync );
}

void	GLWindow::setWidth( int width )
{
	this->_width = width;
}

void	GLWindow::setHeight( int height )
{
	this->_height = height;
}


void GLWindow::setWindowPos( int x, int y )
{
	glfwSetWindowPos( this->_GLFWwindow, x, y );
}

void GLWindow::destroyWindow( void )
{
	glfwDestroyWindow( this->_GLFWwindow );
	this->_GLFWwindow = nullptr;
}
