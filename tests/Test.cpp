#include "Test.hpp"
#include "../srcs/components/Mesh.hpp"
#include "../srcs/components/Camera.hpp"
#include "../srcs/components/CameraControl.hpp"
#include "../srcs/components/LightComponent.hpp"
#include "../srcs/components/MeshBuilder.hpp"
#include "../srcs/physics/SphereCollider.hpp"
#include "../srcs/physics/PlanCollider.hpp"
#include "../srcs/ui/UiComponent.hpp"
#include "../srcs/utils/Factory.hpp"
#include "../srcs/ui/tag/Layout.hpp"

Test::Test( void ) : AGame()
{
	return ;
}

shared_ptr<GameObject> parent( new GameObject() );
shared_ptr<GameObject> mesh1( new GameObject() );

void Test::init( void )
{
	// TODO main factory
	Factory::registerClass( "layout", &Layout::instantiate );

	float aspectRatio = (float)this->_coreEngine->getWindow().getWidth() / (float)this->_coreEngine->getWindow().getHeight();
	shared_ptr<GameObject>	cameraO( new GameObject() );
	shared_ptr<Camera>		camera( new Camera( 70.0f, aspectRatio, 0.1f, 1000.0f ) );
	shared_ptr<CameraControl>	control( new CameraControl() );
	control->setSpeed( 10.0f );
	cameraO->addComponent( camera );
	cameraO->addComponent( control );
	cameraO->getTransform().setPosition( Vec3f( 0, 0.001f, -10 ) );
	setCamera( camera );
	addObject( cameraO );

	shared_ptr<GameObject>	meshO( new GameObject() );
	shared_ptr<Mesh>		mesh( new Mesh() );
	mesh->putVertex( Vertexf( Vec3f( -1, 0, -1 ) ) );
	mesh->putVertex( Vertexf( Vec3f( -1, 0, 1 ) ) );
	mesh->putVertex( Vertexf( Vec3f( 1, 0, -1 ) ) );
	mesh->putVertex( Vertexf( Vec3f( 1, 0, 1 ) ) );
	mesh->calcNormal();
	mesh->bufferData();
	meshO->addComponent( mesh );
	meshO->getTransform().setScale( Vec3f( 10, 10, 10 ) );
	meshO->getTransform().setPosition( Vec3f( 0, 0, 0 ) );

	shared_ptr<PhysicsComponent> physicsComponent( new PhysicsComponent() );
	physicsComponent->setCollider( new PlanCollider( Vec3f( 0, 1, 0 ) ) );
	physicsComponent->setMass( 10000000000000 );
	meshO->addComponent( physicsComponent );
	addObject( meshO );

//	mesh1->addComponent( MeshBuilder::loadFromObj( "./resources/modules/main_module/objs/Feisar_Ship.obj" ) );
//	mesh1->getTransform()->setScale( Vec3f( 0.02, 0.02, 0.02 ) );
//	mesh1->getTransform()->setPosition( Vec3f( 2, 0, 0 ) );
//	parent->addChild( mesh1 );
//	addObject( parent );

//	cube = new Cube( 2 );
//	cube->getTransform()->setScale( Vec3f( 0.5, 0.5, 0.5 ) );
//	physicsComponent = new PhysicsComponent();
//	physicsComponent->setCollider( SphereCollider( Sphere( Vec3f( 0, 0, 0 ), 2 ) ) );
//	cube->addComponent( physicsComponent );
//	addObject( cube );

//	shared_ptr<GameObject>		sphere( new GameObject() );
//	sphere->addComponent( MeshBuilder::loadFromObj( "./resources/objs/sphere.obj" ) );
//	PhysicsComponent * physicsComponent1 = new PhysicsComponent();
//	physicsComponent1->setCollider( new SphereCollider( Vec3f( 0, 0, 0 ), 1 ) );
//	physicsComponent1->setVelocity( Vec3f( 0, -1, 0 ) );
//	physicsComponent1->setMass( 1000 );
//	sphere->addComponent( physicsComponent1 );
//	sphere->getTransform()->setPosition( Vec3f( 0, 2, 0 ) );
//	addObject( sphere );

//	shared_ptr<GameObject>		sphere2( new GameObject() );
//	sphere2->addComponent( MeshBuilder::loadFromObj( "./resources/objs/sphere.obj" ) );
//	PhysicsComponent * physicsComponent2 = new PhysicsComponent();
//	physicsComponent2->setCollider( new SphereCollider( Vec3f( 0, 0, 0 ), 1 ) );
//	physicsComponent2->setVelocity( Vec3f( -0.5f, -0.5f, 0 ) );
//	physicsComponent2->setMass( 1000 );
//	sphere2->addComponent( physicsComponent2 );
//	sphere2->getTransform()->setPosition( Vec3f( 3, 1, 0 ) );
//	addObject( sphere2 );

	shared_ptr<GameObject>		lightO( new GameObject() );
	shared_ptr<LightComponent>	light( new LightComponent() );
	light->setAmbient( Colorf( 0.2f, 0.2f, 0.2f, 1 ) );
	light->setDiffuse( Colorf( 0.5f, 0.5f, 0.5f, 1 ) );
	light->setSpecular( Colorf( 0.9f, 0.9f, 0.9f, 1 ) );
	light->setShininess( 40 );
	lightO->addComponent( light );
	lightO->getTransform().setPosition( Vec3f( 0, 10, 0 ) );
	addObject( lightO );


	// TODO: GUI
//	shared_ptr<GameObject>		guiObject = new GameObject();
//	guiObject->addComponent( new UiComponent( "./resources/ui/test_ui.xml" ) );
//	guiObject->getTransform()->setScale( Vec3f( 0.5f, 0.5f, 0.5f ) );
//	addObject( guiObject );

//	shared_ptr<GameObject>		light1 = new GameObject();
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
//	parent->getTransform()->rotate( Quatf( Vec3f( 0, 1, 0 ), TO_RADIANS( 0.3 ) ) );
	AGame::update( delta );
}
