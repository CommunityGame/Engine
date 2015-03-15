#include "GameObject.hpp"

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

void	GameObject::render( RenderEngine const & renderEngine ) const
{
	std::vector< AObjectComponent *>::const_iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->render( renderEngine );
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

void	GameObject::renderAll( RenderEngine const & renderEngine ) const
{
	std::vector<GameObject *>::const_iterator it;

	this->render( renderEngine );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->renderAll( renderEngine );
}

void	GameObject::addChild( GameObject * object )
{
	this->_childrens.push_back( object );
}

void	GameObject::addComponent( AObjectComponent * component )
{
	this->_components.push_back( component );
}
