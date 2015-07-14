#ifndef _SPHERE_H_
# define _SPHERE_H_

#include "Geometry.hpp"
#include "../Math.hpp"

//TODO: template
class Sphere : public Geometry
{
public:
	inline Sphere( Vec3f const & center, float radius ) :
		_center( center ),
		_radius( radius )
	{
		return ;
	}

	inline float	getRadius( void ) const
	{
		return ( this->_radius );
	}

	inline Vec3f	getCenter( void ) const
	{
		return ( this->_center );
	}

private:
	float			_radius;
	Vec3f			_center;
};

#endif // ! _SPHERE_H_
