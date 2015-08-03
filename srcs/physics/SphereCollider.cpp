#include "SphereCollider.hpp"
#include "../components/basic/PhysicsComponent.hpp"

SphereCollider::SphereCollider( Vec3f const & center, float radius  ) :
	_center( center ),
	_radius( radius )
{
	return ;
}

IntersectData SphereCollider::intersect( Collider & other, double delta )
{
	return ( other.intersect( (SphereCollider &) * this, delta ) );
}

IntersectData SphereCollider::intersect( SphereCollider & other, double delta )
{
	// TODO: transform center pos
	// Relative velocity
	Vec3f	dv	= ( other.getParentComponent()->getVelocity() - this->_parentComponent->getVelocity() ) * delta;
	// Relative position
	Vec3f	dp	= other.getCenter() - this->getCenter();
	//Minimal distance squared
	float r = this->getRadius() + other.getRadius();
	//dP^2-r^2
	float pp = dp.squaredNorm() - r * r;
	//(1)Check if the spheres are already intersecting
	if ( pp < 0 )
		return ( IntersectData( true, dp.normalized() * pp ) );

	//dP*dV
	float pv	= dp.dot( dv );
	//(2)Check if the spheres are moving away from each other
	if ( pv >= 0 )
		return ( IntersectData( false, Vec3f( 0, 0, 0 ) ) );

	//dV^2
	float vv = dv.squaredNorm();
	//(3)Check if the spheres can intersect within 1 frame
	if ( (pv + vv) <= 0 && (vv + 2 * pv + pp) >= 0 )
		return ( IntersectData( false, Vec3f( 0, 0, 0 ) ) );

//	std::cout << "pok: " << pp << std::endl;
//	std::cout << "pok1: " << (vv + 2 * pv + pp) << std::endl;
	float coeff = ( pp / ( pp - (vv + 2 * pv + pp) ) ) * (float)delta;
//	std::cout << "coeff: " << coeff << std::endl;

//	std::cout << "v1: " << this->_parentComponent->getVelocity() * coeff << std::endl;
//	std::cout << "v2: " << other.getParentComponent()->getVelocity() * coeff << std::endl;

	Vec3f v1 = this->_parentComponent->getVelocity() * coeff;// + this->_parentComponent->getTransform().getPosition();
	Vec3f v2 = other.getParentComponent()->getVelocity() * coeff;// + other.getParentComponent()->getTransform().getPosition();

//	std::cout << (v2 - v1).norm() << std::endl;

	//tmin = -dP*dV/dV*2
	//the time when the distance between the spheres is minimal
	float tmin = -pv / vv;

	//Discriminant/(4*dV^2) = -(dp^2-r^2+dP*dV*tmin)
	IntersectData data = IntersectData( pp + pv * tmin < 0, dp.normalized() * pp );
	data.setDistToCollision1( v2 );
	data.setDistToCollision2( v1 );
	data.setCommonNormal( dp.normalized() );
//	std::cout << v1 << std::endl;
//	std::cout << v2 << std::endl;
	return ( data );
}

IntersectData	SphereCollider::intersect( PlanCollider & other, double delta )
{
	return ( Collider::intersectSpherePlan( *this, other, delta ) );
}


Vec3f const		SphereCollider::getCenter( void ) const
{
	return ( this->_center + this->_parentComponent->getTransform().getPosition() );
}

float			SphereCollider::getRadius( void ) const
{
	return ( this->_radius );
}
