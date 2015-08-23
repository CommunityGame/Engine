#ifndef _CORE_ENGINE_H_
# define _CORE_ENGINE_H_

#include <sys/types.h>
#include "render/GLWindow.hpp"
#include "Input.hpp"
#include "render/RenderEngine.hpp"
#include "debugs/Debugger.hpp"
#include "physics/PhysicsEngine.hpp"

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
	GLWindow &				getWindow( void ) const;
	RenderEngine &			getRenderEngine( void ) const;
	PhysicsEngine &			getPhysicsEngine( void ) const;
	AGame &					getGame( void ) const;

	// SETTER
	void					setDebugMode( bool mode );

private:
	void					run( void );

	AGame &					_game;
	shared_ptr<GLWindow>	_window;
	RenderEngine *			_renderEngine;
	PhysicsEngine *			_physicsEngine;
	Debugger *				_debugger;
	bool					_isRunning;
	double					_fpsExpected;
	bool					_debugMode;

	static const std::string	TAG;
};

#endif // ! _CORE_ENGINE_H_
