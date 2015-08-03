#ifndef _PHYSICS_COMPONENT_H_
# define _PHYSICS_COMPONENT_H_

#include "../../physics/Collider.hpp"
#include "AObjectComponent.hpp"

class PhysicsComponent : public AObjectComponent
{
public:
	PhysicsComponent( void );

	/*!
	 * @function physics
	 * @param delta: time passed to run the previous loop
	 * physics this AObjectComponent
	 *
	 * @return void
	 */
	virtual void		physics( double delta );
	virtual void		update( double delta );
	virtual void		init( CoreEngine & coreEngine ) {};

	// SETTER
	void				setVelocity( Vec3f const & velocity );
	void				setMass( float mass );
	void				setCollider( Collider * collider );

	// GETTER
	Vec3f				getVelocity( void ) const;
	float				getMass( void ) const;
	Collider *			getCollider( void );

private:
	Vec3f				_velocity;
	float				_mass;
	Collider *			_collider;
};

#endif // ! _PHYSICS_COMPONENT_H_
