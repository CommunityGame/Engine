#include "PhysicsComponent.hpp"
#include "../GameObject.hpp"

PhysicsComponent::PhysicsComponent( void ) :
	_velocity( 0, 0, 0 )
{
	return ;
}

void	PhysicsComponent::physics( double delta )
{
//	this->_velocity = Vec3f( 0, -0.005f, 0 );
}

void	PhysicsComponent::update( double delta )
{
	this->_parent->getTransform()->translate( this->_velocity );
}

// SETTER
void		PhysicsComponent::setVelocity( Vec3f const & velocity )
{
	this->_velocity = velocity;
}

void		PhysicsComponent::setMass( float mass )
{
	this->_mass = mass;
}

void		PhysicsComponent::setCollider( Collider * collider )
{
	collider->setParentComponent( this );
	this->_collider = collider;
}

// GETTER
Vec3f		PhysicsComponent::getVelocity( void ) const
{
	return ( this->_velocity );
}

float		PhysicsComponent::getMass( void ) const
{
	return ( this->_mass );
}

Collider *	PhysicsComponent::getCollider( void )
{
	return ( this->_collider );
}

