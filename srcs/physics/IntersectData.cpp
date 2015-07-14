#include "IntersectData.hpp"

IntersectData::IntersectData( bool intersect, Vec3f direction ) :
		_haveIntersect( intersect ),
		_direction( direction )
{
	return ;
}

IntersectData::IntersectData( IntersectData const & cpy )
{
	* this = cpy;
	return ;
}

IntersectData &	IntersectData::operator=( IntersectData const & rhs )
{
	if ( & rhs != this )
	{
		this->_direction = rhs.getDistance();
		this->_haveIntersect = rhs.haveIntersect();
		this->_distToCollision1 = rhs.getDistToCollision1();
		this->_distToCollision2 = rhs.getDistToCollision2();
		this->_commonNormal = rhs.getCommonNormal();
	}
	return ( *this );
}

// SETTER
void		IntersectData::setDistToCollision1( Vec3f const & vec )
{
	this->_distToCollision1 = vec;
}

void		IntersectData::setDistToCollision2( Vec3f const & vec )
{
	this->_distToCollision2 = vec;
}

void IntersectData::setCommonNormal( Vec3f const & vec )
{
	this->_commonNormal = vec;
}

// GETTER
Vec3f		IntersectData::getDistToCollision1( void ) const
{
	return ( this->_distToCollision1 );
}

Vec3f		IntersectData::getDistToCollision2( void ) const
{
	return ( this->_distToCollision2 );
}

bool		IntersectData::haveIntersect( void ) const
{
	return ( this->_haveIntersect );
}

Vec3f		IntersectData::getDistance( void ) const
{
	return ( this->_direction );
}

Vec3f		IntersectData::getCommonNormal( void ) const
{
	return ( this->_commonNormal );
}
