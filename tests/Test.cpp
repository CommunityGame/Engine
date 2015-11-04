#include "Test.hpp"
#include "../srcs/components/Camera.hpp"
#include "../srcs/components/CameraControl.hpp"
#include "../srcs/physics/SphereCollider.hpp"
#include "../srcs/physics/PlanCollider.hpp"
#include "../srcs/ui/UiComponent.hpp"
#include "../srcs/ui/tag/Layout.hpp"
#include "../srcs/ui/svg/ScalableVectorGraphics.hpp"
#include "../srcs/components/MeshComponent.hpp"
#include "../srcs/factories/MeshFactory.hpp"
#include "../srcs/factories/SoundFactory.hpp"
#include "../srcs/utils/OldFactory.hpp"
#include "../srcs/assets/AssetsManager.hpp"
#include "../srcs/components/SoundComponent.hpp"
#include "../srcs/factories/ShaderFactory.hpp"
#include "../srcs/components/basic/PhysicsComponent.hpp"
#include "../srcs/components/PointLightComponent.hpp"

Test::Test( void ) : AGame()
{
	return ;
}

shared_ptr<SoundComponent> soundSource;
shared_ptr<GameObject> parent( new GameObject() );
shared_ptr<GameObject> mesh1( new GameObject() );

void soundCallback( enum SoundComponent::Event e, SoundComponent const & source )
{
}

void Test::init( void )
{
	AssetsManager::loadAsset<Sound>( "11k16bitpcm.wav", "sound1" );
	AssetsManager::loadAsset<Mesh>( "Feisar_Ship.obj", "ship" );
	AssetsManager::loadAsset<Mesh>( "cube.obj", "cube" );
	AssetsManager::loadAsset<Mesh>( "plan.obj", "plan" );
	AssetsManager::loadAsset<Mesh>( "sphere.obj", "sphere" );

	// TODO main factory
	OldFactory::registerClass( "layout", (OldFactory::instantiateFunction) &Layout::instantiate );

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

	shared_ptr<GameObject>		meshO( new GameObject() );

	Asset<Mesh>	plan = AssetsManager::getAssetByUidName<Mesh>( "plan" );
	meshO->addComponent( shared_ptr<MeshComponent>( new MeshComponent( plan ) ) );
	meshO->getTransform().setScale( Vec3f( 50, 50, 50 ) );
	meshO->getTransform().setPosition( Vec3f( 0, 0, 0 ) );

	shared_ptr<PhysicsComponent> physicsComponent( new PhysicsComponent() );
	physicsComponent->setCollider( new PlanCollider( Vec3f( 0, 1, 0 ) ) );
	physicsComponent->setMass( 10000000000000 );
	meshO->addComponent( physicsComponent );
	addObject( meshO );

	//TODO: Attache to SoundEngine to update() it

	Asset<Sound>	sound = AssetsManager::getAssetByUidName<Sound>( "sound1" );
	soundSource = shared_ptr<SoundComponent>( new SoundComponent( sound ) );
//	soundSource->setSound( sound );
	soundSource->setPosition( Vec3f( 0, 0, 0 ) );
	soundSource->setEventCallback( soundCallback );
//	soundSource->play();

	Asset<Mesh>	ship = AssetsManager::getAssetByUidName<Mesh>( "ship" );
	mesh1->addComponent( shared_ptr<MeshComponent>( new MeshComponent( ship ) ) );
	mesh1->getTransform().setScale( Vec3f( 0.02, 0.02, 0.02 ) );
	mesh1->getTransform().setPosition( Vec3f( 0, 0, 0 ) );
	parent->addChild( mesh1 );
	addObject( parent );

//	shared_ptr<GameObject>		sphereO( new GameObject() );
//	Asset<Mesh>	sphere = AssetsManager::getAssetByUidName<Mesh>( "sphere" );
//	sphereO->addComponent( shared_ptr<MeshComponent>( new MeshComponent( sphere ) ) );
//	shared_ptr<PhysicsComponent> physicsComponent1 = shared_ptr<PhysicsComponent>( new PhysicsComponent() );
//	physicsComponent1->setCollider( new SphereCollider( Vec3f( 0, 0, 0 ), 1 ) );
//	physicsComponent1->setVelocity( Vec3f( 0, -1, 0 ) );
//	physicsComponent1->setMass( 1000 );
//	sphereO->addComponent( physicsComponent1 );
//	sphereO->getTransform().setPosition( Vec3f( 0, 2, 0 ) );
//	addObject( sphereO );

//	shared_ptr<GameObject>		sphere2( new GameObject() );
//	sphere2->addComponent( MeshFactory::loadObj( "./assets/meshs/sphere.obj" ) );
//	PhysicsComponent * physicsComponent2 = new PhysicsComponent();
//	physicsComponent2->setCollider( new SphereCollider( Vec3f( 0, 0, 0 ), 1 ) );
//	physicsComponent2->setVelocity( Vec3f( -0.5f, -0.5f, 0 ) );
//	physicsComponent2->setMass( 1000 );
//	sphere2->addComponent( physicsComponent2 );
//	sphere2->getTransform()->setPosition( Vec3f( 3, 1, 0 ) );
//	addObject( sphere2 );

	shared_ptr<GameObject>		lightO;
	lightO = shared_ptr<GameObject>( new GameObject() );
	shared_ptr<PointLightComponent>	light( new PointLightComponent() );
	light->setAmbient( Colorf( 0.2f, 0.2f, 0.2f, 1 ) );
	light->setDiffuse( Colorf( 0.5f, 0.5f, 0.5f, 1 ) );
	light->setSpecular( Colorf( 0.5f, 0.5f, 0.5f, 1 ) );
	light->setShininess( 0.015 );
	light->setRadius( 5 );
	light->setCutoff( 0.005 );
	lightO->addComponent( light );
	lightO->getTransform().setPosition( Vec3f( 0, 4, 0 ) );
	addObject( lightO );

//	shared_ptr<GameObject>		lightO1;
//	lightO1 = shared_ptr<GameObject>( new GameObject() );
//	shared_ptr<PointLightComponent>	light1( new PointLightComponent( AssetsManager::loadAsset<Shader>( "point_phong", "point_phong" ) ) );
//	light1->setAmbient( Colorf( 0.2f, 0.2f, 0.2f, 1 ) );
//	light1->setDiffuse( Colorf( 0.5f, 0.5f, 0.5f, 1 ) );
//	light1->setSpecular( Colorf( 0.7f, 0.7f, 0.7f, 1 ) );
//	light1->setShininess( 0.15 );
//	light1->setRadius( 7 );
//	light1->setCutoff( 0.005 );
//	lightO1->addComponent( light1 );
//	lightO1->getTransform().setPosition( Vec3f( 0, 10, 0 ) );
//	addObject( lightO1 );
//
//	shared_ptr<GameObject>		lightO2;
//	lightO2 = shared_ptr<GameObject>( new GameObject() );
//	shared_ptr<PointLightComponent>	light2( new PointLightComponent( AssetsManager::loadAsset<Shader>( "point_phong", "point_phong" ) ) );
//	light2->setAmbient( Colorf( 0.2f, 0.2f, 0.0f, 1 ) );
//	light2->setDiffuse( Colorf( 0.5f, 0.5f, 0.0f, 1 ) );
//	light2->setSpecular( Colorf( 0.7f, 0.7f, 0.0f, 1 ) );
//	light2->setShininess( 1.75 );
//	light2->setRadius( 7 );
//	light2->setCutoff( 0.005 );
//	lightO2->addComponent( light2 );
//	lightO2->getTransform().setPosition( Vec3f( 15, 10, 0 ) );
//	addObject( lightO2 );

//	shared_ptr<GameObject>		svgObject( new GameObject() );
//	svgObject->addComponent( shared_ptr<ScalableVectorGraphics>( new ScalableVectorGraphics( "./assets/svg/test.svg" ) ) );
//	svgObject->addComponent( shared_ptr<ScalableVectorGraphics>( new ScalableVectorGraphics( "./assets/svg/test2.svg" ) ) );
//	svgObject->addComponent( shared_ptr<ScalableVectorGraphics>( new ScalableVectorGraphics( "./assets/svg/tiger.svg" ) ) );
//	svgObject->addComponent( shared_ptr<ScalableVectorGraphics>( new ScalableVectorGraphics( "./assets/svg/gs_snowflak.svg" ) ) );
//	addObject( svgObject );


	// TODO: GUI
//	shared_ptr<GameObject>		guiObject( new GameObject() );
//	guiObject->addComponent( shared_ptr<UiComponent>( new UiComponent( "./assets/ui/test_ui.xml" ) ) );
//	guiObject->getTransform().setScale( Vec3f( 0.5f, 0.5f, 0.5f ) );
//	addObject( guiObject );

//	shared_ptr<GameObject>		light1 = new GameObject();
//	light = new PointLightComponent();
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
//	soundSource->setPitch( soundSource->getPitch() - 0.001f );
//	std::cout << soundSource->getState() << std::endl;
//	parent->getTransform()->rotate( Quatf( Vec3f( 0, 1, 0 ), TO_RADIANS( 0.3 ) ) );
	AGame::update( delta );
}
