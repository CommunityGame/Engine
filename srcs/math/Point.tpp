#ifndef _POINT_HPP_
# define _POINT_HPP_

#include <typeinfo>
#include <ostream>
#include <tgmath.h>

template <typename T, u_int8_t D>
class Point
{
public:
	inline Point( void )
	{
		for ( int i = 0; i < D; ++i )
			this->_values[i] = 0;
		return ;
	}

	inline Point( Point const & cpy )
	{
		*this = cpy;
		return ;
	}

	inline ~Point( void )
	{
		return ;
	}

	inline Point &	operator=( Point const & rhs )
	{
		for ( int i = 0; i < D; ++i )
			this->_values[i] = rhs[i];
		return ( *this );
	}

	inline bool		operator==( Point const & rhs ) const
	{
		for ( int i = 0; i < D; ++i )
		{
			if ( this->_values[i] != rhs[i] )
				return ( false );
		}
		return ( true );
	}

	inline bool		operator!=( Point const & rhs ) const
	{
		for ( int i = 0; i < D; ++i )
		{
			if ( this->_values[i] != rhs[i] )
				return ( true );
		}
		return ( false );
	}

	inline Point	operator+( Point const & rhs ) const
	{
		Point		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] + rhs[i];
		return ( result );
	}

	inline Point &	operator+=( Point const & rhs )
	{
		for ( int i = 0; i < D; ++i )
			this->_values[i] += rhs[i];
		return ( *this );
	}

	inline Point	operator-( Point const & rhs ) const
	{
		Point		result;

		for ( int i = 0; i < D; ++i )
			result[i] = (*this)[i] - rhs[i];
		return ( result );
	}

	inline Point &	operator-=( Point const & rhs )
	{
		for ( int i = 0; i < D; ++i )
			this->_values[i] -= rhs[i];
		return ( *this );
	}

	inline T &		operator[]( u_int8_t i )
	{
		return ( this->_values[i] );
	}

	inline T		operator[]( u_int8_t i ) const
	{
		return ( this->_values[i] );
	}

	inline T const *		getValues( void ) const
	{
		return ( this->_values );
	}

protected:
	T				_values[D];
};

template <typename T, u_int8_t D>
std::ostream &		operator<<( std::ostream & o, Point<T, D> const & p )
{
	o << "(";
	for ( int i = 0; i < D; ++i )
	{
		o << "[" << i << "]: " << p[i];
		if ( i + 1 != D )
			o << ", ";
	}
	o << ")";
	return ( o );
}

#endif // ! _POINT_HPP_
