#include <sstream>
#include "CoreEngine.hpp"
#include "AGame.hpp"
#include "modules/ModulesFactory.hpp"
#include "components/Camera.hpp"

const std::string	CoreEngine::TAG = "CoreEngine";

CoreEngine::CoreEngine( AGame & game, int fpsExpected ) :
	_game( game ),
	_window( nullptr ),
	_isRunning( false ),
	_fpsExpected( fpsExpected ),
	_debugMode( false )
{
	return ;
}

CoreEngine::~CoreEngine( void )
{
	delete this->_renderEngine;
	return ;
}

bool			CoreEngine::start( void )
{
	if ( this->_isRunning )
	{
		Logger::e( TAG, "Can't start, The CoreEngine alrady running" );
		return ( false );
	}
	if ( this->_window == nullptr )
	{
		Logger::e( TAG, "Unable to start CoreEngine: no window set" );
		return ( false );
	}
	this->run();
	return ( true );
}

bool			CoreEngine::stop( void )
{
	if ( ! this->_isRunning )
	{
		Logger::e( TAG, "Can't stop, The CoreEngine is not running" );
		return ( false );
	}
	this->_isRunning = false;
	return ( true );
}

void			CoreEngine::createWindow( int width, int height, std::string const & title )
{
	this->_window = GLWindow::create( width, height, title );
	this->_renderEngine = new RenderEngine( * this->_window );
	this->_physicsEngine = new PhysicsEngine(  );
	this->_soundEngine = shared_ptr<SoundEngine>( new SoundEngine() );
	return ;
}

void			CoreEngine::run( void )
{
	double	begin_ticks;
	double	end_ticks;
//	double	begin_debug;
//	double	end_debug;
	double	dt;

	dt = 0;
	this->_isRunning = true;

	begin_ticks = glfwGetTime();

	this->_game.setCoreEngine( this );
	this->_game.init();
	Input::init( this->_window );

	ModulesFactory	modulesFactory;
	modulesFactory.loadModules( "./assets/modules" );

	modulesFactory.initModules( this->_game.getRootObject() );
//	this->_game.addObject( new LuaGameObject( "./assets/modules/main_module/GameObject.lua", modulesFactory.getLuaState() ) );

	this->_game.getRootObject()->initAll( * this );

	while ( this->_isRunning )
	{
		int width, height;
		glfwGetFramebufferSize( this->_window->getGLFWwindow(), &width, &height );
		if ( this->_window->getWidth() != width || this->_window->getHeight() != height )
		{
			this->_window->setWidth( width );
			this->_window->setHeight( height );
			if ( this->_game.getCamera() != nullptr )
				this->_game.getCamera()->setAspect( (float)width / (float)height );
			glViewport( 0, 0, width, height );
		}

		// INPUT
//		begin_debug = glfwGetTime();
		Input::pollEvents( this->_window );

		if ( Input::isCloseRequested() )
			this->stop();

		// PHYSICS
//		begin_debug = end_debug;
		this->_game.physics( * this->_physicsEngine, dt );

//		end_debug = glfwGetTime();
//		std::cout << "Physics: " << end_debug - begin_debug << std::endl;

		// UPDATE
//		begin_debug = end_debug;
		modulesFactory.updateModules( dt );
		this->_game.update( dt );

		if ( this->_game.getCamera() != this->_renderEngine->getCamera() )
			this->_renderEngine->setCamera( this->_game.getCamera() );

//		end_debug = glfwGetTime();
//		std::cout << "Update: " << end_debug - begin_debug << std::endl;

		this->_soundEngine->update( dt, this->_game.getCamera()->getParent() );

		// RENDER
//		begin_debug = end_debug;
		this->_game.render( * this->_renderEngine );

//		end_debug = glfwGetTime();
//		std::cout << "Render: " << end_debug - begin_debug << std::endl;

		// REFRESH
//		begin_debug = end_debug;
		this->_window->refresh();

//		end_debug = glfwGetTime();
//		std::cout << "Refresh: " << end_debug - begin_debug << std::endl;

		end_ticks = glfwGetTime();
		dt = ( end_ticks - begin_ticks );
		begin_ticks = end_ticks;

//		if ( 1 )
//		{
//			std::stringstream	title;
//			double fps = 1.0 / dt;
//			std::cout << "dt: " << dt << std::endl;
//			std::cout << fps << std::endl;
//			if ( fps > this->_fpsExpected )
//				title << this->_window->getTitle() << ", real FPS: " << this->_fpsExpected;
//			else
//				title << this->_window->getTitle() << ", real FPS: " << fps;
//			title << ", FPS could be done: " << fps;
//			glfwSetWindowTitle( this->_window->getGLFWwindow(), title.str().c_str() );
//
//			if ( fps < this->_fpsExpected )
//			{
//				std::stringstream	log;
//				log << "Frames dropped: " << (this->_fpsExpected - fps);
//				Logger::w( log.str() );
//			}
//			else
//				std::this_thread::sleep_for( std::chrono::microseconds( ( ( ( 1.0 / this->_fpsExpected ) - dt ) * SECOND ) ) );
//		}
	}

	modulesFactory.unloadModules();
}

GLWindow &		CoreEngine::getWindow( void ) const
{
	return ( * this->_window );
}

RenderEngine &	CoreEngine::getRenderEngine( void ) const
{
	return ( * this->_renderEngine );
}

PhysicsEngine &	CoreEngine::getPhysicsEngine( void ) const
{
	return ( * this->_physicsEngine );
}

shared_ptr<SoundEngine> const &	CoreEngine::getSoundEngine( void ) const
{
	return ( this->_soundEngine );
}

void			CoreEngine::startDebugWindow( void )
{
	this->_debugger = new Debugger();
}

void			CoreEngine::setDebugMode( bool mode )
{
	this->_debugMode = mode;
}

AGame &			CoreEngine::getGame( void ) const
{
	return ( this->_game );
}
