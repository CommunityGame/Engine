#ifndef _VEC_HPP_
# define _VEC_HPP_

# include <ostream>
# include <tgmath.h>
# include "Point.tpp"

template <typename T, u_int8_t D>
class Vec : public Point<T, D>
{
public:
	inline Vec( void ) : Point<T, D>()
	{
		return ;
	}

	inline T		squaredNorm( void ) const
	{
		T	result( 0 );

		for ( int i = 0; i < D; ++i )
			result += this->_values[i] * this->_values[i];
		return ( result );
	}
	
	inline T		norm( void ) const
	{
		return ( sqrt( this->squaredNorm() ) );
	}

	inline Vec &	normalize( void )
	{
		T		length;

		length = this->norm();
		for ( int i = 0; i < D; ++i )
			(*this)[i] /= length;
		return ( *this );
	}

	inline Vec		normalized( void ) const
	{
		Vec		result;
		T		length;

		length = this->norm();
		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] / length;
		return ( result );
	}

	inline T		dot( const Vec & r ) const
	{
		T result = T(0);

		for ( int i = 0; i < D; ++i )
			result += (*this)[i] * r[i];
		return ( result );
	}

	inline Vec		operator*( Vec const & rhs )
	{
		Vec		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] * rhs[i];
		return ( result );
	}

	inline Vec		operator*( T const & value )
	{
		Vec		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] * value;
		return (  result );
	}

	inline Vec &	operator*=( Vec const & rhs )
	{
		*this = *this * rhs;
		return ( *this );
	}

	inline Vec &	operator*=( T const & value )
	{
		*this = *this * value;
		return ( *this );
	}

	inline Vec		operator/( Vec const & rhs )
	{
		Vec		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] / rhs[i];
		return ( result );
	}

	inline Vec		operator/( T const & value )
	{
		Vec		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] / value;
		return (  result );
	}

	inline Vec &	operator/=( Vec const & rhs )
	{
		*this = *this / rhs;
		return ( *this );
	}

	inline Vec &	operator/=( T const & value )
	{
		*this = *this / value;
		return ( *this );
	}
};

template <typename T>
class Vec2 : public Vec<T, 2>
{
public:
	Vec2( T x, T y )
	{
		(*this)[0] = x;
		(*this)[1] = y;
	}

	T				cross( const Vec2<T>& r ) const
	{
		return ( this->getX() * r.getX() - this->getY() * r.getY() );
	}

	/**
	 * GETTER
	 */
	inline T		getX( void ) const
	{
		return ( (*this)[0] );
	}
	inline T		getY( void ) const
	{
		return ( (*this)[1] );
	}

	/**
	 * SETTER
	 */
	inline void		setX( const T & x )
	{
		(*this)[0] = x;
	}
	inline void		setY( const T & y )
	{
		(*this)[1] = y;
	}

	inline void		set( const T & x, const T & y )
	{
		(*this)[0] = x;
		(*this)[1] = y;
	}
};

template <typename T>
class Vec3 : public Vec<T, 3>
{
public:
	Vec3( T x, T y, T z )
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}

	inline Vec3<T>	cross( const Vec3<T> & r ) const
	{
		T x = (*this)[1] * r[2] - (*this)[2] * r[1];
		T y = (*this)[2] * r[0] - (*this)[0] * r[2];
		T z = (*this)[0] * r[1] - (*this)[1] * r[0];

		return ( Vec3<T>( x, y, z ) );
	}

//	inline Vec3<T>	rotate( T angle, const Vec3<T> & axis ) const
//	{
//		const T sinAngle = sin( -angle );
//		const T cosAngle = cos( -angle );
//
//		return ( this->cross( axis * sinAngle ) + ( *this * cosAngle ) + ( axis * this->dot( axis * ( 1 - cosAngle ) ) ) );
//	}

	/**
	 * GETTER
	 */
	inline T		getX( void ) const
	{
		return ( (*this)[0] );
	}

	inline T		getY( void ) const
	{
		return ( (*this)[1] );
	}

	inline T		getZ( void ) const
	{
		return ( (*this)[2] );
	}

	/**
	 * SETTER
	 */
	inline void		setX( const T & x )
	{
		(*this)[0] = x;
	}

	inline void		setY( const T & y )
	{
		(*this)[1] = y;
	}

	inline void		setZ( const T & z )
	{
		(*this)[2] = z;
	}

	inline void		set( const T & x, const T & y, const T & z )
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}
};

#endif //_VEC_HPP_
