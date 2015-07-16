#ifndef _SPHERE_COLLIDER_H_
# define _SPHERE_COLLIDER_H_

#include "Collider.hpp"
#include "../math/geometry/Sphere.hpp"

class SphereCollider : public Collider
{
public:
	SphereCollider( Vec3f const & center, float radius );

	virtual IntersectData intersect( Collider & other, double delta );
	virtual IntersectData intersect( SphereCollider & other, double delta );
	virtual IntersectData intersect( PlanCollider & other, double delta );

	Vec3f const					getCenter( void ) const;
	float						getRadius( void ) const;

private:
	Vec3f						_center;
	float						_radius;
};

#endif // ! _SPHERE_COLLIDER_H_
