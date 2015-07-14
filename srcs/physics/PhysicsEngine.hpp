#ifndef _PHYSICS_ENGINE_H_
# define _PHYSICS_ENGINE_H_

#include <vector>
#include "Collider.hpp"

class GameObject;

class PhysicsEngine
{
public:
	void				physics( GameObject & object, double delta ) const;
	void				checkCollisions( std::vector<Collider *> collidersObject1, std::vector<Collider *> collidersObject2 ) const ;

	static void			refreshPhysicsObjectList( bool needed );

private:
	mutable std::vector<GameObject *>	_physicsObjects;
	static bool							_needRefreshPhysicsObjectList;
};

#endif // ! _PHYSICS_ENGINE_H_
