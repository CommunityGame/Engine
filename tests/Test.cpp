#include "Test.hpp"
#include "../srcs/components/Mesh.hpp"
#include "../srcs/components/Camera.hpp"

Test::Test( void ) : AGame()
{
	return ;
}

void Test::init( CoreEngine const & coreEngine )
{
//	Shader( "basic" );
//	std::cout << "ok" << std::endl;
	GameObject *	cameraO = new GameObject();
	Camera *		camera = new Camera( Mat4f().initPerspective( 0, 0, 0, 0 ) );
	cameraO->addComponent( camera );

	coreEngine.getRenderEngine().setCamera( camera );

	GameObject *	meshO = new GameObject();
	Mesh *			mesh = new Mesh();
	mesh->putVertex( Vec3f( 0, 0, 0 ) );
	mesh->putVertex( Vec3f( 0, 1, 0 ) );
	mesh->putVertex( Vec3f( 1, 1, 0 ) );
	mesh->bufferData();
	meshO->addComponent( mesh );
	addObject( cameraO );
	addObject( meshO );

}
