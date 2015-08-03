#include "AObjectComponent.hpp"
#include "../../GameObject.hpp"

GameObject const &	AObjectComponent::getParent( void ) const
{
	return ( * this->_parent );
}

void				AObjectComponent::setParent( GameObject * parent )
{
	this->_parent = parent;
	return ;
}

Transformf &		AObjectComponent::getTransform( void ) const
{
	return ( * this->_parent->getTransform() );
}
