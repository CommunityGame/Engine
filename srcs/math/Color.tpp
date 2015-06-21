#ifndef _COLOR_HPP_
# define _COLOR_HPP_

#include <iostream>

template <typename T>
class Color
{
public:
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
};

template <typename T>
std::ostream &		operator<<( std::ostream & o, Color<T> const & c )
{
	return ( o << "r: " << c.getR() << ", g: " << c.getR() << ", b: " << c.getR() << ", a: " << c.getR() );
}

#endif // ! _COLOR_HPP_
