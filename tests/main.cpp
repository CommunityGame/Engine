#include "../srcs/CoreEngine.hpp"
#include "../tests/Test.hpp"

int		main( int argc, const char *argv[] )
{
	CoreEngine *	coreEngine;
	coreEngine = new CoreEngine( * new Test(), 60 );

	Logger::setPrintLogs( true );

	Logger::i( "\t-- Start session --" );
	if ( argc == 2 && std::string(argv[1]) == "--dev" )
	{
		coreEngine->setDebugMode( true );
	// coreEngine->startDebugWindow();
		Logger::setVerbosity( VERBOSE );
		Logger::i( "DEV MODE" );
	}
	else
	{
		coreEngine->setDebugMode( false );
		Logger::setVerbosity( INFO );
		Logger::i( "NORMAL MODE" );
	}

	coreEngine->createWindow( 850, 550, "Test" );
	coreEngine->start();

	delete coreEngine;
	Logger::i( "\t-- End session --\n" );
	return ( 0 );
}
