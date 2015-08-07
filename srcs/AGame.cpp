#include "AGame.hpp"

AGame::~AGame( void )
{
	return ;
}

void	AGame::update( double delta )
{
	if ( this->_rootObject != nullptr )
		this->_rootObject->updateAll( delta );
	return ;
}

void	AGame::render( RenderEngine const & renderEngine ) const
{
	if ( this->_rootObject != nullptr )
		renderEngine.render( * this->_rootObject );
	return ;
}

void	AGame::physics( PhysicsEngine const & physicsEngine, double delta ) const
{
	if ( this->_rootObject != nullptr )
		physicsEngine.physics( * this->_rootObject, delta );
	return ;
}

void	AGame::addObject( shared_ptr<GameObject> object )
{
	object->setCoreEngine( this->_coreEngine );
	if ( this->_rootObject == nullptr )
		this->_rootObject = shared_ptr<GameObject>( new GameObject() );
	this->_rootObject->addChild( object );
	return ;
}

void	AGame::setCamera( shared_ptr<Camera> camera )
{
	this->_camera = camera;
}

void AGame::setCoreEngine( CoreEngine * coreEngine )
{
	this->_coreEngine = coreEngine;
}

shared_ptr<Camera>		AGame::getCamera( void ) const
{
	return ( this->_camera );
}

shared_ptr<GameObject>	AGame::getRootObject( void ) const
{
	return ( this->_rootObject );
}