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
	float aspectRatio = coreEngine.getWindow().getWidth() / coreEngine.getWindow().getHeight();
	GameObject *	cameraO = new GameObject();
	Camera *		camera = new Camera( Mat4f().initPerspective( 70.0f, aspectRatio, 0.1f, 1000.0f ) );
	cameraO->getTransform()->setPosition( Vec3f(0, 0, 10) );
	cameraO->addComponent( camera );
	setCamera( camera );

	coreEngine.getRenderEngine().setCamera( camera );

	GameObject *	meshO = new GameObject();
	Mesh *			mesh = new Mesh();
	mesh->putVertex( Vec3f( 0, 0, 0 ) );
	mesh->putVertex( Vec3f( 0, 1, 0 ) );
	mesh->putVertex( Vec3f( 1, 1, 0 ) );
	mesh->bufferData();
	meshO->addComponent( mesh );
//	addObject( cameraO );
	addObject( meshO );

//	Mat<float, 4, 4> matTest;
//	Quatf quatf( Vec3f( 0, 0, 1 ), TO_RADIANS( 90.0f ) );
//	matTest = quatf.toMatrix();

//	matTest.initTranslation( Vec3f( 1, 2, 3 ) );

//	std::cout << matTest << std::endl;

}
