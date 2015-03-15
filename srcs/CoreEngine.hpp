#ifndef _CORE_ENGINE_H_
# define _CORE_ENGINE_H_

#include "render/Window.hpp"
#include "Input.hpp"
#include "render/RenderEngine.hpp"

class CoreEngine
{
public:
	CoreEngine( int fpsExpected );
	~CoreEngine( void );

	// FUNCTIONS
	bool				start( void );
	bool				stop( void );
	void				createWindow( int width, int height, std::string const & title );
	// GETTER

	// SETTER

private:
	void				run( void );

	Window *			_window;
	Input *				_input;
	RenderEngine *		_renderEngine;
	//Debuger *
	bool				_isRunning;
	double				_fpsExpected;
};

#endif // ! _CORE_ENGINE_H_