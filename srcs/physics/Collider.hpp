#ifndef _COLLIDER_H_
# define _COLLIDER_H_

#include "../math/Math.hpp"
#include "../math/geometry/Geometry.hpp"
#include "IntersectData.hpp"

class SphereCollider;
class PlanCollider;

class PhysicsComponent;

class Collider
{
public:

	Collider();

	virtual IntersectData intersect( Collider & other, double delta )
	{
		return ( IntersectData( false, Vec3f( 0, 0, 0 ) ) );
	}

	virtual IntersectData intersect( SphereCollider & other, double delta ) {};
	virtual IntersectData intersect( PlanCollider & other, double delta ) {};

	static IntersectData	intersectSpherePlan( SphereCollider & sphere, PlanCollider & plan, double delta );

	// GETTER
	PhysicsComponent *	getParentComponent( void ) const;

	// SETTER
	void				setParentComponent( PhysicsComponent * physicsComponent ) const;

protected:
	mutable PhysicsComponent *	_parentComponent;

private:
};

#endif // ! _COLLIDER_H_
