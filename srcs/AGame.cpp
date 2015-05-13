#include "AGame.hpp"

AGame::~AGame( void )
{
	if ( this->_rootObject != nullptr )
		delete this->_rootObject;
	return ;
}

void	AGame::input( Input const & input )
{
	if ( this->_rootObject != nullptr )
		this->_rootObject->inputAll( input );
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

void	AGame::addObject( GameObject * object )
{
	if ( this->_rootObject == nullptr )
		this->_rootObject = new GameObject();
	this->_rootObject->addChild( object );
	return ;
}
