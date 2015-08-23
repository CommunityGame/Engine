#ifndef _MAT_HPP_
# define _MAT_HPP_

#include <iostream>
#include <sstream>
# include "Vec.tpp"

template <typename T, u_int8_t X, u_int8_t Y>
class Mat : public Point<T, X * Y>
{
public:
	inline Mat( void )
	{
		*this = this->initIdentity();
		return ;
	}

	inline Mat &	initIdentity( void )
	{
		return ( this->initScale( T( 1 ) ) );
	}

	inline Mat &	initScale( T scale )
	{
		for ( u_int8_t i = 0; i < Y; ++i )
		{
			for ( u_int8_t j = 0; j < X; ++j )
				this->_values[j + i * X] = ( i == j ) ? scale : T( 0 );
		}
		return ( *this );
	}

	inline Mat &	initScale( const Vec<T, X - 1> & vec )
	{
		for ( u_int8_t i = 0; i < Y; ++i )
		{
			for ( u_int8_t j = 0; j < X; ++j )
				this->_values[j + i * X] = ( i == j ) ? T( vec[i] ) : T( 0 );
		}
		this->_values[15] = T(1);
		return ( *this );
	}

	inline Mat &	initTranslation( const Vec<T, Y - 1> & vec )
	{
		for ( u_int8_t i = 0; i < Y; ++i )
		{
			for ( u_int8_t j = 0; j < X; ++j )
				this->_values[j + i * X] = ( i == Y - 1 && j != Y - 1 ) ? vec[j] : T( i == j );
		}
		this->_values[15] = T(1);
		return ( *this );
	}

	inline Mat &	initRotationFromVectors( const Vec<T, X - 1>& n, const Vec<T, X - 1>& v, const Vec<T, X - 1>& u)
	{
		this->_values[0] = u[0];   this->_values[4] = v[0];   this->_values[8] = n[0];   this->_values[12] = T(0);
		this->_values[1] = u[1];   this->_values[5] = v[1];   this->_values[9] = n[1];   this->_values[13] = T(0);
		this->_values[2] = u[2];   this->_values[6] = v[2];   this->_values[10] = n[2];  this->_values[14] = T(0);
		this->_values[3] = T(0);   this->_values[7] = T(0);   this->_values[11] = T(0);  this->_values[15] = T(1);

		return ( *this );
	}

	inline Mat<T, Y, X>		transposed( void ) const
	{
		Mat<T, Y, X> result;

		for ( u_int8_t i = 0 ; i < Y ; ++i )
		{
			for ( u_int8_t j = 0 ; j < X; ++j )
				result[i + j * Y] = this->_values[j + i * X];
		}
		return ( result );
	}

	inline Mat		operator*( const Mat<T, Y, X> & m ) const
	{
		Mat result;

		for ( u_int8_t i = 0 ; i < Y ; ++i )
		{
			for ( u_int8_t j = 0 ; j < X; ++j )
			{
				result[j + i * X] = T( 0 );
				for( u_int8_t k = 0; k < X; ++k )
					result[j + i * X] += (*this)[j + k * X] * m[k + i * X];
			}
		}
		return ( result );
	}

	inline Mat &	operator*=( const Mat<T, Y, X> & m )
	{
		*this = ( * this ) * m;
		return ( *this );
	}

	inline Mat		operator*( const T & value ) const
	{
		Mat		result;

		for ( int i = 0; i < X * Y; ++i )
			result[i] = (*this)[i] * value;
		return ( result );
	}

	inline Mat &	operator*=( const T & value )
	{
		*this = *this * value;
		return ( *this );
	}

	inline Mat		operator+( Mat const & rhs ) const
	{
		Mat		result;

		for ( int i = 0; i < X * Y; ++i )
			result[i] = (*this)[i] + rhs[i];
		return ( result );
	}

	inline Mat &	operator+=( Mat const & rhs )
	{
		*this = *this + rhs;
		return ( *this );
	}

	inline Mat		operator-( Mat const & rhs ) const
	{
		Mat		result;

		for ( int i = 0; i < X * Y; ++i )
			result[i] = (*this)[i] - rhs[i];
		return ( result );
	}

	inline Mat &	operator-=( Mat const & rhs )
	{
		*this = *this - rhs;
		return ( *this );
	}
};

template <typename T>
class Mat4 : public Mat<T, 4, 4>
{
public:
	static const Mat4<T> ZERO;

	inline Mat4() {}

	inline Mat4( Mat<T, 4, 4> const & cpy )
	{
		*this = cpy;
		return ;
	}

	inline Mat4 &	operator=( Mat<T, 4, 4> const & rhs )
	{
		for ( int i = 0; i < 16; ++i )
			this->_values[i] = rhs[i];
		return ( *this );
	}

	inline Mat4 &	initPerspective( T fov, T aspectRatio, T zNear, T zFar )
	{
		const T zRange     = zNear - zFar;
		const T tanHalfFOV = tanf( fov / T(2) );

		this->_values[0] = T( 1 ) / ( tanHalfFOV * aspectRatio );
		this->_values[1] = T( 0 );
		this->_values[2] = T( 0 );
		this->_values[3] = T( 0 );

		this->_values[4] = T( 0 );
		this->_values[5] = T( 1 ) / tanHalfFOV;
		this->_values[6] = T( 0 );
		this->_values[7] = T( 0 );

		this->_values[8] = T( 0 );
		this->_values[9] = T( 0 );
		this->_values[10] = ( -zNear - zFar ) / zRange;
		this->_values[11] = T( 1 );

		this->_values[12] = T( 0 );
		this->_values[13] = T( 0 );
		this->_values[14] = T( 2 ) * zFar * zNear / zRange;
		this->_values[15] = T( 1 );
		return ( *this );
	}

	std::string		toString( void ) const
	{
		std::stringstream ss;
		ss << *this;
		return ( ss.str() );
	}
};

template <typename T>
Mat4<T> const Mat4<T>::ZERO = Mat4<T>();

template <typename T, u_int8_t X, u_int8_t Y>
std::ostream &		operator<<( std::ostream & o, Mat<T, X, Y> const & m )
{
	for ( int i = 0; i < Y; ++i )
	{
		for ( int j = 0; j < X; ++j )
		{
			o << "(" << j * X + i << "): " << m[j * X + i];
			if ( j == X - 1 )
				o << std::endl;
			else
				o << '\t';
		}
	}
	return ( o );
}

#endif // ! _MAT_HPP_
