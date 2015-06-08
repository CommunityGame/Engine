#include "../srcs/CoreEngine.hpp"
#include "../tests/Test.hpp"

int		main( void )
{
	CoreEngine *	coreEngine;
	coreEngine = new CoreEngine( * new Test(), 60 );

	Logger::setVerbosity( VERBOSE );
	Logger::setPrintLogs( true );

	coreEngine->createWindow( 850, 550, "Test" );
//	coreEngine->startDebugWindow();
	coreEngine->start();

	delete coreEngine;
	return ( 0 );
}