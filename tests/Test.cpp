#include "Test.hpp"
#include "../srcs/components/Mesh.hpp"
#include "../srcs/components/Camera.hpp"
#include "../srcs/components/CameraControl.hpp"
#include "../srcs/components/LightComponent.hpp"
#include "components/Cube.hpp"

Test::Test( void ) : AGame()
{
	return ;
}

void Test::init( void )
{
	float aspectRatio = this->_coreEngine->getWindow().getWidth() / this->_coreEngine->getWindow().getHeight();
	GameObject *	cameraO = new GameObject();
	Camera *		camera = new Camera( 70.0f, aspectRatio, 0.1f, 1000.0f );
	CameraControl *	control = new CameraControl();
	control->setSpeed( 10.0f );
	cameraO->addComponent( camera )->addComponent( control );
	cameraO->getTransform()->setPosition( Vec3f( 0, 1, -10 ) );
	setCamera( camera );
	addObject( cameraO );

	GameObject *	meshO = new GameObject();
	Mesh *			mesh = new Mesh();
	mesh->putVertex( Vertexf( Vec3f( -1, 0, -1 ) ) );
	mesh->putVertex( Vertexf( Vec3f( -1, 0, 1 ) ) );
	mesh->putVertex( Vertexf( Vec3f( 1, 0, -1 ) ) );
	mesh->putVertex( Vertexf( Vec3f( 1, 0, 1 ) ) );
	mesh->calcNormal();
	mesh->bufferData();
	meshO->addComponent( mesh );
	meshO->getTransform()->setScale( Vec3f( 10, 10, 10 ) );
	meshO->getTransform()->setPosition( Vec3f( 0, -1, 0 ) );
	addObject( meshO );

	addObject( new Cube( 2 ) );

	GameObject *		lightO = new GameObject();
	LightComponent *	light = new LightComponent();
	light->setAmbient( Colorf( 0.2f, 0.2f, 0.2f, 1 ) );
	light->setDiffuse( Colorf( 0.5f, 0.5f, 0.5f, 1 ) );
	light->setSpecular( Colorf( 0.9f, 0.9f, 0.9f, 1 ) );
	light->setShininess( 20 );
	lightO->addComponent( light );
	lightO->getTransform()->setPosition( Vec3f( -10, 15, 0 ) );
	addObject( lightO );
	GameObject *		light1 = new GameObject();
	light = new LightComponent();
	light->setAmbient( Colorf( 0.0f, 0.2f, 0.2f, 1 ) );
	light->setDiffuse( Colorf( 0.0f, 0.5f, 0.5f, 1 ) );
	light->setSpecular( Colorf( 0.0f, 0.9f, 0.9f, 1 ) );
	light->setShininess( 20 );
	light1->addComponent( light );
	light1->getTransform()->setPosition( Vec3f( 15, 20, 0 ) );
	addObject( light1 );
}
