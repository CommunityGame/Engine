#include "../srcs/CoreEngine.hpp"
#include "../srcs/debugs/Timer.hpp"

int		main( void )
{
	CoreEngine *	coreEngine;
	coreEngine = new CoreEngine( 60 );

	Logger::setVerbosity( VERBOSE );
	Logger::setPrintLogs( true );

	printf( "Pok: %lf\n", Timer::getNanotime() );

	coreEngine->createWindow( 850, 550, "Test" );
	coreEngine->start();
	printf( "Pok: %lf\n", Timer::getNanotime() );

	delete coreEngine;
	return ( 0 );
}