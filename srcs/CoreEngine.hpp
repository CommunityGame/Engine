#ifndef _CORE_ENGINE_H_
# define _CORE_ENGINE_H_

#include <sys/types.h>
#include "render/Window.hpp"
#include "Input.hpp"
#include "render/RenderEngine.hpp"
#include "debugs/Debugger.hpp"

class AGame;

class CoreEngine
{
public:
	CoreEngine( AGame & game, int fpsExpected );
	~CoreEngine( void );

	// FUNCTIONS
	bool					start( void );
	bool					stop( void );
	void					createWindow( int width, int height, std::string const & title );
	void					startDebugWindow( void );

	// GETTER
	Window const &			getWindow( void ) const;
	RenderEngine const &	getRenderEngine( void ) const;
	Input const &			getInput( void ) const;

	// SETTER
	void					setDebugMode( bool mode );

private:
	void					run( void );

	AGame &					_game;
	Window *				_window;
	Input *					_input;
	RenderEngine *			_renderEngine;
	Debugger *				_debugger;
	bool					_isRunning;
	double					_fpsExpected;
	bool					_debugMode;
};

#endif // ! _CORE_ENGINE_H_
