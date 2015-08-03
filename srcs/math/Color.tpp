#ifndef _COLOR_HPP_
# define _COLOR_HPP_

#include <iostream>
#include "../debugs/Logger.hpp"

template <typename T = float>
class Color
{
public:
	Color()
	{
		this->_r = 0;
		this->_g = 0;
		this->_b = 0;
		this->_a = 1;
	}

	Color( const std::string & hex )
	{
		long			iVal;
		std::string		val( hex.substr( 1 ) );
		iVal = strtol( val.c_str(), 0, 16 );
		if ( val.length() == 6 )
		{
			this->_r = (T)( ( iVal & 0xFF0000 ) >> 16 ) / T( 255 );
			this->_g = (T)( ( iVal & 0x00FF00 ) >> 8 ) / T( 255 );
			this->_b = (T)( ( iVal & 0x0000FF ) >> 0 ) / T( 255 );
			this->_a = T( 1 );
		}
		else if ( val.length() == 8 )
		{
			this->_r = (T)( ( iVal & 0xFF000000 ) >> 24 ) / T( 255 );
			this->_g = (T)( ( iVal & 0x00FF0000 ) >> 16 ) / T( 255 );
			this->_b = (T)( ( iVal & 0x0000FF00 ) >> 8 ) / T( 255 );
			this->_a = (T)( ( iVal & 0x000000FF ) ) / T( 255 );
		}
		else
		{
			Logger::e( TAG, "Invalid format, expeted: #RRGGBB or #RRGGBBAA" );
			return ;
		}
	}

	Color( int32_t color )
	{
		this->_r = (T)( ( color & 0xFF000000 ) >> 24 ) / T( 255 );
		this->_g = (T)( ( color & 0x00FF0000 ) >> 16 ) / T( 255 );
		this->_b = (T)( ( color & 0x0000FF00 ) >> 8 ) / T( 255 );
		this->_a = (T)( ( color & 0x000000FF ) ) / T( 255 );
	}

	Color( T const & r, T const & g, T const & b, T const & a )
	{
		this->_r = r;
		this->_g = g;
		this->_b = b;
		this->_a = a;
	}

	inline Color( Color const & cpy )
	{
		*this = cpy;
		return ;
	}

	inline Color<T> &	operator=( Color<T> const & rhs )
	{
		this->_r = rhs.getR();
		this->_g = rhs.getG();
		this->_b = rhs.getB();
		this->_a = rhs.getA();
		return ( *this );
	}

	inline T	getR( void ) const
	{
		return ( this->_r );
	}

	inline T	getG( void ) const
	{
		return ( this->_g );
	}

	inline T	getB( void ) const
	{
		return ( this->_b );
	}

	inline T	getA( void ) const
	{
		return ( this->_a );
	}

private:
	T		_r;
	T		_g;
	T		_b;
	T		_a;

	static const std::string	TAG;
};

template <typename T>
const std::string	Color<T>::TAG = "Color";

template <typename T>
std::ostream &		operator<<( std::ostream & o, Color<T> const & c )
{
	return ( o << "r: " << c.getR() << ", g: " << c.getR() << ", b: " << c.getR() << ", a: " << c.getR() );
}

#endif // ! _COLOR_HPP_
