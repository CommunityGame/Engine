#include "PlanCollider.hpp"

PlanCollider::PlanCollider( Vec3f const & normal ) :
	_normal( normal.normalized() )
{
	return ;
}

IntersectData	PlanCollider::intersect( Collider & other, double delta )
{
	return ( other.intersect( (PlanCollider &) * this, delta ) );
}

IntersectData	PlanCollider::intersect( PlanCollider & other, double delta )
{
	return Collider::intersect( other, delta );
}

IntersectData	PlanCollider::intersect( SphereCollider & other, double delta )
{
	return ( Collider::intersectSpherePlan( other, *this, delta ) );
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
