#include "PhysicsEngine.hpp"
#include "../GameObject.hpp"
# include "../components/basic/PhysicsComponent.hpp"

bool	PhysicsEngine::_needRefreshPhysicsObjectList = true;

void	PhysicsEngine::physics( GameObject & object, double delta ) const
{
	std::vector<GameObject *>::iterator	it;

	if ( PhysicsEngine::_needRefreshPhysicsObjectList )
	{
		this->_physicsObjects.clear();
		object.getPhysicsObjects( this->_physicsObjects );
	}
	PhysicsEngine::refreshPhysicsObjectList( false );

	for ( it = this->_physicsObjects.begin(); it != this->_physicsObjects.end(); it++ )
		(*it)->physics( delta );

	for ( int i = 0; i < this->_physicsObjects.size(); i++ )
	{
		for ( int j = i + 1; j < this->_physicsObjects.size(); j++ )
		{
			std::vector<Collider *>		collidersObject1;
			std::vector<Collider *>		collidersObject2;

			for ( int k = 0; k < this->_physicsObjects[i]->getPhysicsComponents().size(); k++ )
				collidersObject1.push_back( this->_physicsObjects[i]->getPhysicsComponents()[k]->getCollider() );
			for ( int k = 0; k < this->_physicsObjects[j]->getPhysicsComponents().size(); k++ )
				collidersObject2.push_back( this->_physicsObjects[j]->getPhysicsComponents()[k]->getCollider() );

			checkCollisions( collidersObject1, collidersObject2, delta );
		}
	}
}

void	PhysicsEngine::checkCollisions( std::vector<Collider *> collidersObject1, std::vector<Collider *> collidersObject2, double delta ) const
{
	for ( int i = 0; i < collidersObject1.size(); i++ )
	{
		for ( int j = 0; j < collidersObject2.size(); j++ )
		{
			Collider &	c1 = * collidersObject1[i];
			Collider &	c2 = * collidersObject2[j];
			IntersectData intersectData = c1.intersect( c2, delta );
			if ( intersectData.haveIntersect() )
			{
//				std::cout << intersectData.getDistToCollision1() << std::endl;
//				std::cout << intersectData.getDistToCollision2() << std::endl;
				c1.getParentComponent()->getTransform().translate( intersectData.getDistToCollision1() );
				c2.getParentComponent()->getTransform().translate( intersectData.getDistToCollision2() );
				Vec3f n = intersectData.getCommonNormal();
//				std::cout << n << std::endl;
//				std::cout << c2.getParentComponent()->getVelocity() << std::endl;
//				std::cout << c2.getParentComponent()->getVelocity().reflect( n ) << std::endl;
//				c1.getParentComponent()->setVelocity( c2.getParentComponent()->getVelocity().reflect( n ) * -1 );
//				c2.getParentComponent()->setVelocity( c1.getParentComponent()->getVelocity().reflect( n ) );
//				c2.getParentComponent()->setVelocity( Vec3f( 0, 0, 0 ) );
//				std::cout << c1.getParentComponent()->getVelocity().normalized() << std::endl;
//				Vec3f otherDirection = direction.reflect( c1.getParentComponent()->getVelocity().normalized() );
//				c1.getParentComponent()->setVelocity( direction );
//				c2.getParentComponent()->setVelocity( c1.getParentComponent()->getVelocity().reflect( otherDirection ) );

				std::cout << c1.getParentComponent()->getVelocity() << " " << c1.getParentComponent()->getVelocity().norm() << std::endl;
				std::cout << c2.getParentComponent()->getVelocity() << " " << c2.getParentComponent()->getVelocity().norm() << std::endl;
				std::cout << "-- POK --" << std::endl;
//				std::cout << n << " " << n.norm() << std::endl;
//				std::cout << c2.getParentComponent()->getVelocity().normalized() << " " << c2.getParentComponent()->getVelocity().normalized().norm() << std::endl;

				float angle = n.dot( c2.getParentComponent()->getVelocity().normalized() );
				float length = angle * c2.getParentComponent()->getVelocity().norm();
				Vec3f vel2 = n * length;
//				std::cout << c2.getParentComponent()->getVelocity() << std::endl;
				std::cout << TO_DEGREES( acosf( angle ) ) << std::endl;
//				std::cout << vel1 << std::endl;

				n = n * -1;
				length = angle * c1.getParentComponent()->getVelocity().norm();
				Vec3f vel1 = n * length;
//				std::cout << c1.getParentComponent()->getVelocity() << std::endl;
//				std::cout << n << std::endl;
//				std::cout << TO_DEGREES( acosf( angle ) ) << std::endl;
//				std::cout << vel2 << std::endl;
//				Vec3f vel2 = ;
//				std::cout << vel1 << " " << vel1.norm() << std::endl;
//				std::cout << vel2 << " " << vel2.norm() << std::endl;
//				std::cout << "-- POKA --" <<std::endl;

				Vec3f v1 = ( vel1 * ( c1.getParentComponent()->getMass() - c2.getParentComponent()->getMass() ) + ( vel2 * ( 2 * c2.getParentComponent()->getMass() ) ) ) /
						   ( c1.getParentComponent()->getMass() + c2.getParentComponent()->getMass() );

				Vec3f v2 = ( vel2 * ( c2.getParentComponent()->getMass() - c1.getParentComponent()->getMass() ) + ( vel1 * ( 2 * c1.getParentComponent()->getMass() ) ) ) /
						   ( c1.getParentComponent()->getMass() + c2.getParentComponent()->getMass() );
//				std::cout << v1 << " " << v1.norm() << std::endl;
//				std::cout << v2 << " " << v2.norm() << std::endl;
//				std::cout << "-- POKY --" <<std::endl;

				Vec3f vv1 = ( v1 * ( c1.getParentComponent()->getMass() - c2.getParentComponent()->getMass() ) + ( v2 * ( 2 * c2.getParentComponent()->getMass() ) ) ) /
						   ( c1.getParentComponent()->getMass() + c2.getParentComponent()->getMass() );

				Vec3f vv2 = ( v2 * ( c2.getParentComponent()->getMass() - c1.getParentComponent()->getMass() ) + ( v1 * ( 2 * c1.getParentComponent()->getMass() ) ) ) /
						   ( c1.getParentComponent()->getMass() + c2.getParentComponent()->getMass() );
//				std::cout << vv1 << " " << vv1.norm() << std::endl;
//				std::cout << vv2 << " " << vv2.norm() << std::endl;
//				std::cout << "-- POKY --" <<std::endl;

				c1.getParentComponent()->setVelocity( c1.getParentComponent()->getVelocity() - vv1 + v1 );
				c2.getParentComponent()->setVelocity( c2.getParentComponent()->getVelocity() - vv2 + v2 );

				std::cout << c1.getParentComponent()->getVelocity() << " " << c1.getParentComponent()->getVelocity().norm() << std::endl;
				std::cout << c2.getParentComponent()->getVelocity() << " " << c2.getParentComponent()->getVelocity().norm() << std::endl;

//				Vec3f collision = intersectData.getDistance();
//				float aci = c1.getParentComponent()->getVelocity().dot( collision );
//				float bci = c2.getParentComponent()->getVelocity().dot( collision );
//
//				// Solve for the new velocities using the 1-dimensional elastic collision equations.
//				// Turns out it's really simple when the masses are the same.
//				float acf = bci;
//				float bcf = aci;
//
//				// Replace the collision velocity components with the new ones
//				c1.getParentComponent()->setVelocity( Vec3f( 0, 0, 0 ) );
//				c2.getParentComponent()->setVelocity( Vec3f( 0, 0, 0 ) );
			}
		}
	}
}

void	PhysicsEngine::refreshPhysicsObjectList( bool needed )
{
	PhysicsEngine::_needRefreshPhysicsObjectList = needed;
}
