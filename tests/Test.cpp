#include "Test.hpp"
#include "../srcs/components/Mesh.hpp"
#include "../srcs/components/Camera.hpp"
#include "../srcs/components/CameraControl.hpp"
#include "../srcs/components/LightComponent.hpp"
#include "components/Cube.hpp"
#include "../srcs/modules/ModulesFactory.hpp"
#include "../srcs/components/MeshBuilder.hpp"
#include "../srcs/components/PhysicsComponent.hpp"
#include "../srcs/math/geometry/Sphere.hpp"
#include "../srcs/physics/SphereCollider.hpp"
#include "../srcs/physics/PlanCollider.hpp"

Test::Test( void ) : AGame()
{
	return ;
}


GameObject *		mesh1;
GameObject *		cube;

//TODO: use std::shared_ptr<>
void Test::init( void )
{
	float aspectRatio = (float)this->_coreEngine->getWindow().getWidth() / (float)this->_coreEngine->getWindow().getHeight();
	GameObject *	cameraO = new GameObject();
	Camera *		camera = new Camera( 70.0f, aspectRatio, 0.1f, 1000.0f );
	CameraControl *	control = new CameraControl();
	control->setSpeed( 10.0f );
	cameraO->addComponent( camera )->addComponent( control );
	cameraO->getTransform()->setPosition( Vec3f( 0, 0.001f, -10 ) );
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
	meshO->getTransform()->setPosition( Vec3f( 0, 0, 0 ) );

	PhysicsComponent * physicsComponent = new PhysicsComponent();
	physicsComponent->setCollider( new PlanCollider( Vec3f( 0, 1, 0 ) ) );
	physicsComponent->setMass( 10000000000000 );
	meshO->addComponent( physicsComponent );

	addObject( meshO );

//	GameObject * mesh1 = new GameObject();
//	mesh1->addComponent( MeshBuilder::loadFromObj( "./resources/modules/main_module/objs/Feisar_Ship.obj" ) );
//	mesh1->getTransform()->setScale( Vec3f( 0.02, 0.02, 0.02 ) );
//	addObject( mesh1 );

//	cube = new Cube( 2 );
//	cube->getTransform()->setScale( Vec3f( 0.5, 0.5, 0.5 ) );
//	physicsComponent = new PhysicsComponent();
//	physicsComponent->setCollider( SphereCollider( Sphere( Vec3f( 0, 0, 0 ), 2 ) ) );
//	cube->addComponent( physicsComponent );
//	addObject( cube );

	GameObject *		sphere = new GameObject();
	sphere->addComponent( MeshBuilder::loadFromObj( "./resources/objs/sphere.obj" ) );
	PhysicsComponent * physicsComponent1 = new PhysicsComponent();
	physicsComponent1->setCollider( new SphereCollider( Vec3f( 0, 0, 0 ), 1 ) );
	physicsComponent1->setVelocity( Vec3f( 0, -0.02f, 0 ) );
	physicsComponent1->setMass( 3000 );
	sphere->addComponent( physicsComponent1 );
	sphere->getTransform()->setPosition( Vec3f( 0, 2, 0 ) );
	addObject( sphere );

//	GameObject *		sphere2 = new GameObject();
//	sphere2->addComponent( MeshBuilder::loadFromObj( "./resources/objs/sphere.obj" ) );
//	PhysicsComponent * physicsComponent2 = new PhysicsComponent();
//	physicsComponent2->setCollider( new SphereCollider( Vec3f( 0, 0, 0 ), 1 ) );
//	physicsComponent2->setVelocity( Vec3f( -0.01f, 0, 0 ) );
//	physicsComponent2->setMass( 1000 );
//	sphere2->addComponent( physicsComponent2 );
//	sphere2->getTransform()->setPosition( Vec3f( 2, 1, 0 ) );
//	addObject( sphere2 );

	GameObject *		lightO = new GameObject();
	LightComponent *	light = new LightComponent();
	light->setAmbient( Colorf( 0.2f, 0.2f, 0.2f, 1 ) );
	light->setDiffuse( Colorf( 0.5f, 0.5f, 0.5f, 1 ) );
	light->setSpecular( Colorf( 0.9f, 0.9f, 0.9f, 1 ) );
	light->setShininess( 40 );
	lightO->addComponent( light );
	lightO->getTransform()->setPosition( Vec3f( 0, 10, 0 ) );
	addObject( lightO );
//	GameObject *		light1 = new GameObject();
//	light = new LightComponent();
//	light->setAmbient( Colorf( 0.0f, 0.2f, 0.2f, 1 ) );
//	light->setDiffuse( Colorf( 0.0f, 0.5f, 0.5f, 1 ) );
//	light->setSpecular( Colorf( 0.0f, 0.9f, 0.9f, 1 ) );
//	light->setShininess( 40 );
//	light1->addComponent( light );
//	light1->getTransform()->setPosition( Vec3f( 5, 10, 0 ) );
//	addObject( light1 );
}

void Test::update( double delta )
{
//	mesh1->getTransform()->rotate( Quatf( Vec3f( 0, 1, 0 ), TO_RADIANS( 0.3 ) ) );
	AGame::update( delta );
}
