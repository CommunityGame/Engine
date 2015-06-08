#include "GameObject.hpp"

GameObject::GameObject( void ) :
	_transform( Transformf() )
{
	return ;
}

void	GameObject::input( Input const & input )
{
	std::vector< AObjectComponent *>::iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->input( input );
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

void	GameObject::inputAll( Input const & input )
{
	std::vector<GameObject *>::iterator it;

	this->input( input );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->inputAll( input );
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

void	GameObject::addChild( GameObject * object )
{
	object->setParent( this );
	this->_childrens.push_back( object );
}

void	GameObject::addComponent( AObjectComponent * component )
{
	component->setParent( this );
	this->_components.push_back( component );
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
