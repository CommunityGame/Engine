#ifndef _PLAN_COLLIDER_H_
# define _PLAN_COLLIDER_H_

#include "Collider.hpp"

class PlanCollider : public Collider
{
public:
	PlanCollider( Vec3f const & normal );

	virtual IntersectData intersect( Collider & other, double delta );
	virtual IntersectData intersect( PlanCollider & other, double delta );
	virtual IntersectData intersect( SphereCollider & other, double delta );

	// SETTER
	void			setNormal( Vec3f const & normal );

	// GETTER
	Vec3f const &	getNormal( void ) const;

private:
	Vec3f			_normal;
};

#endif // ! _PLAN_COLLIDER_H_
