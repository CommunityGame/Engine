#include "Test.hpp"
#include "../srcs/components/Mesh.hpp"
#include "../srcs/components/Camera.hpp"
#include "../srcs/components/CameraControl.hpp"

Test::Test( void ) : AGame()
{
	return ;
}

void Test::init( CoreEngine const & coreEngine )
{
//	Shader( "basic" );
//	std::cout << "ok" << std::endl;
	float aspectRatio = coreEngine.getWindow().getWidth() / coreEngine.getWindow().getHeight();
	GameObject *	cameraO = new GameObject();
	Camera *		camera = new Camera( Mat4f().initPerspective( 70.0f, aspectRatio, 0.1f, 1000.0f ) );
	CameraControl *	control = new CameraControl();
	control->setSpeed( 0.1f );
	cameraO->getTransform()->setPosition( Vec3f( 0, 0, 10 ) );
	cameraO->addComponent( camera )->addComponent( control );
	setCamera( camera );

	coreEngine.getRenderEngine().setCamera( camera );

	GameObject *	meshO = new GameObject();
	Mesh *			mesh = new Mesh();
	mesh->putVertex( Vec3f( -1, 0, 1 ) );
	mesh->putVertex( Vec3f( -1, 0, -1 ) );
	mesh->putVertex( Vec3f( 1, 0, 1 ) );
	mesh->putVertex( Vec3f( 1, 0, -1 ) );
	mesh->bufferData();
	meshO->addComponent( mesh );
	addObject( cameraO );
	addObject( meshO );
}
