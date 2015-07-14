#include "AGame.hpp"

AGame::~AGame( void )
{
	if ( this->_rootObject != nullptr )
		delete this->_rootObject;
	return ;
}

void	AGame::input( Input & input, double delta )
{
	if ( this->_rootObject != nullptr )
		this->_rootObject->inputAll( input, delta );
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

void	AGame::addObject( GameObject * object )
{
	object->setCoreEngine( this->_coreEngine );
	if ( this->_rootObject == nullptr )
		this->_rootObject = new GameObject();
	this->_rootObject->addChild( object );
	return ;
}

void	AGame::setCamera( Camera * camera )
{
	this->_camera = camera;
}

void AGame::setCoreEngine( CoreEngine * coreEngine )
{
	this->_coreEngine = coreEngine;
}

Camera *		AGame::getCamera( void ) const
{
	return ( this->_camera );
}

GameObject *	AGame::getRootObject( void ) const
{
	return ( this->_rootObject );
}