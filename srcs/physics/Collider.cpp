#include "Collider.hpp"
#include "../components/PhysicsComponent.hpp"

#include "PlanCollider.hpp"
#include "SphereCollider.hpp"

Collider::Collider()
{
	return ;
}

PhysicsComponent * Collider::getParentComponent( void ) const
{
	return ( this->_parentComponent );
}

void Collider::setParentComponent( PhysicsComponent * physicsComponent ) const
{
	this->_parentComponent = physicsComponent;
}

IntersectData Collider::intersectSpherePlan( SphereCollider & sphere, PlanCollider & plan )
{
	float distanceFromSphereCenter = (float)fabs( plan.getNormal().dot( sphere.getCenter() - plan.getParentComponent()->getTransform().getPosition() ) );
	float distanceFromSphere = distanceFromSphereCenter - sphere.getRadius();

//	Vec3f v = plan.getParentComponent()->getVelocity() + sphere.getParentComponent()->getVelocity();

//	float distanceFromSphereNextFrame = distanceFromSphere + v.norm();
//
//	std::cout << "pok1: " << distanceFromSphere << std::endl;
//	std::cout << "pok2: " << distanceFromSphereNextFrame << std::endl;

//	if ( distanceFromSphere >= 0 )
//		return ( IntersectData( false, Vec3f( 0, 0, 0 ) ) );

	Vec3f dv = sphere.getParentComponent()->getVelocity() - plan.getParentComponent()->getVelocity();
	Vec3f dp = plan.getNormal() * distanceFromSphereCenter;

	float pp = dp.norm() - sphere.getRadius();

//	std::cout << distanceFromSphere << std::endl;
//	std::cout << pp << std::endl;
	if ( pp < 0 )
		return ( IntersectData( false, Vec3f( 0, 0, 0 ) ) );

	float vv = dv.squaredNorm();
	float pv = dp.dot( dv );

	if ( pv >= 0 )
		return ( IntersectData( false, Vec3f( 0, 0, 0 ) ) );
	if ( (pv + vv) <= 0 && (vv + 2 * pv + pp) >= 0 )
		return ( IntersectData( false, Vec3f( 0, 0, 0 ) ) );

	float coeff = pp / ( pp - (vv + 2 * pv + pp) );

//	std::cout << coeff << std::endl;
	float tmin = -pv / vv;

	Vec3f v1 = sphere.getParentComponent()->getVelocity() * coeff;
	Vec3f v2 = plan.getParentComponent()->getVelocity() * coeff;
	IntersectData data = IntersectData( pp + pv * tmin < 0, plan.getNormal() * dp.normalized() );
	data.setDistToCollision1( v2 );
	data.setDistToCollision2( v1 );
//	std::cout << "pok" << std::endl;
	return ( data );
}
