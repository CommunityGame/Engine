#include "../srcs/CoreEngine.hpp"
#include "../tests/Test.hpp"

int		main( int argc, const char *argv[] )
{
	static const std::string	TAG = "MAIN";
	CoreEngine *	coreEngine;
	coreEngine = new CoreEngine( * new Test(), 60 );

	Logger::setPrintLogs( true );

	Logger::i( TAG, "\t-- Start session --" );
	if ( argc == 2 && std::string(argv[1]) == "--dev" )
	{
		coreEngine->setDebugMode( true );
	// coreEngine->startDebugWindow();
		Logger::setVerbosity( VERBOSE );
		Logger::i( TAG, "DEV MODE" );
	}
	else
	{
		coreEngine->setDebugMode( false );
		Logger::setVerbosity( INFO );
		Logger::i( TAG, "NORMAL MODE" );
	}

	coreEngine->createWindow( 850, 550, "Test" );
	coreEngine->getWindow().setVsync( true );
	coreEngine->start();

	delete coreEngine;
	Logger::i( TAG, "\t-- End session --\n" );
	return ( 0 );
}
