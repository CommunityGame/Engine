#include "PlanCollider.hpp"

PlanCollider::PlanCollider( Vec3f const & normal ) :
	_normal( normal.normalized() )
{
	return ;
}

IntersectData	PlanCollider::intersect( Collider & other )
{
	return ( other.intersect( (PlanCollider &) * this ) );
}

IntersectData	PlanCollider::intersect( PlanCollider & other )
{
	return Collider::intersect( other );
}

IntersectData	PlanCollider::intersect( SphereCollider & other )
{
	return ( Collider::intersectSpherePlan( other, *this ) );
}

// SETTER
void			PlanCollider::setNormal( Vec3f const & normal )
{
	this->_normal = normal.normalized();
}

// GETTER
Vec3f const &	PlanCollider::getNormal( void ) const
{
	return ( this->_normal );
}
