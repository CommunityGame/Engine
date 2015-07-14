#ifndef _INTERSECT_DATA_H_
# define _INTERSECT_DATA_H_

#include "../math/Math.hpp"

class IntersectData
{
public:
	IntersectData( bool intersect, Vec3f direction );
	IntersectData( IntersectData const & cpy );

	IntersectData & operator=( IntersectData const & rhs );

	// SETTER
	void		setDistToCollision1( Vec3f const & vec );
	void		setDistToCollision2( Vec3f const & vec );
	void		setCommonNormal( Vec3f const & vec );

	// GETTER
	bool		haveIntersect( void ) const;
	Vec3f		getDistance( void ) const;
	Vec3f		getCommonNormal( void ) const;
	Vec3f		getDistToCollision1( void ) const;
	Vec3f		getDistToCollision2( void ) const;

private:
	bool		_haveIntersect;
	Vec3f		_direction;
	Vec3f		_commonNormal;
	Vec3f		_distToCollision1;
	Vec3f		_distToCollision2;
};

#endif // ! _INTERSECT_DATA_H_
