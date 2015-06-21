#ifndef _VERTEX_HPP_
# define _VERTEX_HPP_

# include "Color.tpp"
# include "Math.hpp"

template <typename T>
class Vertex
{
public:
	Vertex( const Vec3<T> & position, const Vec3<T> & normal, const Color<T> & color ) :
			_position( position ),
			_normal( normal ),
			_color( color )
	{

	}

	Vertex( const Vec3<T> & position, const Color<T> & color ) :
			_position( position ),
			_normal( 0, 0, 0 ),
			_color( color )
	{

	}

	Vertex( const Vec3<T> & position ) :
			_position( position ),
			_normal( 0, 0, 0 ),
			_color( 1, 1, 1, 1 )
	{

	}

	inline Vertex( Vertex const & cpy ) :
			_position( cpy.getPosition() ),
			_normal( cpy.getNormal() ),
			_color( cpy.getColor() )
	{
		*this = cpy;
		return ;
	}

	inline Vertex<T> &	operator=( Vertex<T> const & rhs )
	{
		this->_position = rhs.getPosition();
		this->_normal = rhs.getNormal();
		this->_color = rhs.getColor();
		return ( *this );
	}

	// GETTER
	const Vec3< T > &	getPosition( void ) const
	{
		return ( this->_position );
	}

	const Vec3< T > &	getNormal( void ) const
	{
		return ( this->_normal );
	}

	const Color< T > &	getColor( void ) const
	{
		return ( this->_color );
	}

	// SETTER
	void setPosition( const Vec3< T > & position )
	{
		this->_position = position;
	}

	void setNormal( const Vec3< T > & normal )
	{
		this->_normal = normal;
	}

	void setColor( const Color< T > & color )
	{
		this->_color = color;
	}

private:
	Vec3<T>		_position;
	Vec3<T>		_normal;
	Color<T>	_color;
};

#endif // ! _VERTEX_HPP_