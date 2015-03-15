#include <unistd.h>
#include "CoreEngine.hpp"
#include "debugs/Timer.hpp"

CoreEngine::CoreEngine( int fpsExpected ) :
	_window( nullptr ),
	_input( nullptr ),
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
	if ( this->_isRunning || this->_window == nullptr )
		return ( false );
	this->run();
	return ( true );
}

bool			CoreEngine::stop( void )
{
	if ( ! this->_isRunning )
		return ( false );
	this->_isRunning = false;
	return ( true );
}

void			CoreEngine::createWindow( int width, int height, std::string const & title )
{
	this->_window = Window::create( width, height, title );
	this->_input = new Input( this->_window );
	this->_renderEngine = new RenderEngine( this->_window );
	return ;
}

void			CoreEngine::run( void )
{
	double	begin_ticks;
	double	end_ticks;
	double	dt;

	this->_isRunning = true;

	begin_ticks = Timer::getNanotime();

	while ( this->_isRunning )
	{
		// INPUT
		this->_input->pollEvents();

		if ( this->_input->isCloseRequested() )
			this->stop();

		// RENDER
//		std::cerr << "pok" << std::endl;

		// REFRESH
		this->_window->refresh();

		end_ticks = Timer::getNanotime();
		dt = ( end_ticks - begin_ticks );
		begin_ticks = end_ticks;

		std::cout << 1 / dt << "fps" << std::endl;

		usleep( (__useconds_t) ( ( SECOND / this->_fpsExpected ) - dt ) );
	}
}
