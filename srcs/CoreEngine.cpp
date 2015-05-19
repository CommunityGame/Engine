#include <unistd.h>
#include <sstream>
#include "CoreEngine.hpp"
#include "debugs/Timer.hpp"
#include "AGame.hpp"

CoreEngine::CoreEngine( AGame & game, int fpsExpected ) :
	_game( game ),
	_window( nullptr ),
	_input( nullptr ),
	_isRunning( false ),
	_fpsExpected( fpsExpected )
{
	return ;
}

CoreEngine::~CoreEngine( void )
{
	delete this->_window;
	delete this->_input;
	delete this->_renderEngine;
	return ;
}

bool			CoreEngine::start( void )
{
	if ( this->_isRunning )
	{
		Logger::e( "Can't start, The CoreEngine alrady running" );
		return ( false );
	}
	if ( this->_window == nullptr )
	{
		Logger::e( "Unable to start CoreEngine: no window set" );
		return ( false );
	}
	this->run();
	return ( true );
}

bool			CoreEngine::stop( void )
{
	if ( ! this->_isRunning )
	{
		Logger::e( "Can't stop, The CoreEngine is not running" );
		return ( false );
	}
	this->_isRunning = false;
	return ( true );
}

void			CoreEngine::createWindow( int width, int height, std::string const & title )
{
	this->_window = Window::create( width, height, title );
	this->_input = new Input( this->_window );
	this->_renderEngine = new RenderEngine( * this->_window );
	return ;
}

void			CoreEngine::run( void )
{
	double	begin_ticks;
	double	end_ticks;
	double	dt;

	this->_isRunning = true;

	begin_ticks = Timer::getNanotime();

	this->_game.init( *this );

	while ( this->_isRunning )
	{
		// INPUT
		this->_input->pollEvents();

		if ( this->_input->isCloseRequested() )
			this->stop();

		// INPUT
		this->_game.input( * this->_input );

		// UPDATE
		this->_game.update( dt );

		// RENDER
		this->_game.render( * this->_renderEngine );

		// REFRESH
		this->_window->refresh();

		end_ticks = Timer::getNanotime();
		dt = ( end_ticks - begin_ticks );
		begin_ticks = end_ticks;

		std::stringstream	title;
		title << this->_window->getTitle() << ", FPS: " << 1 / dt;
		glfwSetWindowTitle( this->_window->getGLFWwindow(), title.str().c_str() );

		usleep( (useconds_t) ( ( SECOND / this->_fpsExpected ) - dt ) );
	}
}

Window const & CoreEngine::getWindow( void ) const
{
	return ( * this->_window );
}

RenderEngine const & CoreEngine::getRenderEngine( void ) const
{
	return ( * this->_renderEngine );
}

Input const & CoreEngine::getInput( void ) const
{
	return ( * this->_input );
}
