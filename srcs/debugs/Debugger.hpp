#ifndef _DEBUGGER_H_
# define _DEBUGGER_H_

#include <thread>
#include <tinycthread.h>
#include "../render/Window.hpp"

class Debugger
{
public:
	Debugger( void );
	~Debugger( void );

	void			run( void );

	// SETTER
	void			stop( void );


private:
	void			loop( void );

	std::thread *	_thread;
	Window *		_window;
	bool			_isRunning;
};

#endif // ! _DEBUGGER_H_
