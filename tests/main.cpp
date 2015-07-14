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


//#include <iostream>
//
//class SphereCollider;
//class AABBCollider;
//
//class Collider {
//public:
//	virtual bool collideWith(Collider& c ) {
//		std::cout << "Collider <> Collider" << std::endl;
//	};
//	virtual bool collideWith(SphereCollider& c ) {};
//	virtual bool collideWith(AABBCollider& c ) {};
//};
//
//class SphereCollider : public Collider {
//public:
//	virtual bool collideWith(Collider& c ) {
//		c.collideWith(*this);
//	}
//
//	virtual bool collideWith(SphereCollider& c ) {
//		std::cout << "SphereCollider <> SphereCollider" << std::endl;
//	}
//
//	virtual bool collideWith(AABBCollider& c ) {
//		std::cout << "AABBCollider <> SphereCollider" << std::endl;
//	}
//};
//
//class AABBCollider : public Collider {
//public:
//	virtual bool collideWith(Collider& c ) {
//		c.collideWith(*this);
//	}
//
//	virtual bool collideWith(AABBCollider& c ) {
//		std::cout << "AABBCollider <> AABBCollider" << std::endl;
//	}
//
//	virtual bool collideWith(SphereCollider& c ) {
//		std::cout << "SphereCollider <> AABBCollider" << std::endl;
//	}
//};
//
//int main( int argc, char **argv ) {
//
//	Collider& c1 = * new SphereCollider;
//	Collider& c2 = * new AABBCollider;
//
//	c1.collideWith( c1 );
//	c1.collideWith( c2 );
//	c2.collideWith( c2 );
//	c2.collideWith( c1 );
//
//	return 0;
//}