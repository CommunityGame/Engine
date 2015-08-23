#include <unistd.h>
#include "Debugger.hpp"

Debugger::Debugger( void )
{
	this->run();
}

Debugger::~Debugger( void )
{

}

void Debugger::run( void )
{
	this->_isRunning = true;
	this->_thread = new std::thread( & Debugger::loop, this );
}

void Debugger::loop( void )
{
	this->_window = GLWindow::create( 250, 150, "Debug" );
	this->_window->setWindowPos( 0, 0 );

	const useconds_t sleep = (const useconds_t) ((1.0 / 60.0) * SECOND);
	while ( this->_isRunning )
	{
		if ( glfwWindowShouldClose( this->_window->getGLFWwindow() ) == 1 )
		{
			this->stop();
			continue ;
		}

		this->_window->refresh();

		std::this_thread::sleep_for( std::chrono::microseconds( sleep ) );
	}
}

// SETTER
void Debugger::stop( void )
{
	this->_isRunning = false;
	this->_window->destroyWindow();
}
