#include "AObjectComponent.hpp"
#include "GameObject.hpp"

GameObject::GameObject( void ) :
	_transform( Transformf() ),
	_coreEngine( nullptr )
{
	return ;
}

void	GameObject::input( Input & input, double delta )
{
	std::vector< AObjectComponent *>::iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->input( input, delta );
	return ;
}

void	GameObject::update( double delta )
{
	std::vector< AObjectComponent *>::iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->update( delta );
	return ;
}

void	GameObject::render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{
	std::vector< AObjectComponent *>::const_iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->render( renderEngine, shader, camera );
	return ;
}

void	GameObject::init( CoreEngine & coreEngine )
{
	std::vector< AObjectComponent *>::const_iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->init( coreEngine );
	return ;
}

void	GameObject::inputAll( Input & input, double delta )
{
	std::vector<GameObject *>::iterator it;

	this->input( input, delta );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->inputAll( input, delta );
}

void	GameObject::updateAll( double delta )
{
	std::vector<GameObject *>::iterator it;

	this->update( delta );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->updateAll( delta );
}

void	GameObject::renderAll( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{
	std::vector<GameObject *>::const_iterator it;

	this->render( renderEngine, shader, camera );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->renderAll( renderEngine, shader, camera );
}

void	GameObject::initAll( CoreEngine & coreEngine )
{
	std::vector<GameObject *>::const_iterator it;

	this->init( coreEngine );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->initAll( coreEngine );
}

void	GameObject::addChild( GameObject * object )
{
	object->setParent( this );
	this->_childrens.push_back( object );
}

GameObject	*GameObject::addComponent( AObjectComponent * component )
{
	component->setParent( this );
	this->_components.push_back( component );
	return ( this );
}

//	GETTER
Transformf *		GameObject::getTransform( void )
{
	return ( & this->_transform );
}

Transformf const &	GameObject::getTransform( void ) const
{
	return ( this->_transform );
}

GameObject *		GameObject::getParent( void ) const
{
	return ( this->_parent );
}

CoreEngine *		GameObject::getCoreEngine( void ) const
{
	return ( this->_coreEngine );
}

//	SETTER
void					GameObject::setTransform( Transformf const & transform )
{
	this->_transform = transform;
	return ;
}

void					GameObject::setParent( GameObject * parent )
{
	this->_parent = parent;
	return ;
}

void					GameObject::setCoreEngine( CoreEngine * coreEngine )
{
	std::vector<GameObject *>::const_iterator it;

	this->_coreEngine = coreEngine;
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->setCoreEngine( coreEngine );
}
