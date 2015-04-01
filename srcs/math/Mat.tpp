#ifndef _MAT_HPP_
# define _MAT_HPP_
# include "Math.hpp"

template <typename T, u_int8_t X, u_int8_t Y>
class Mat : public Point<T, X * Y>
{
public:
	inline Mat( void )
	{
		for ( int i = 0; i < X * Y; ++i )
			this->_values[i] = T( 0 );
		return ;
	}

	inline Mat &	initIdentity( void )
	{
		return ( this->initScale( 1 ) );
	}

	inline Mat &	initScale( T scale )
	{
		for ( u_int8_t i = 0; i < Y; ++i )
		{
			for ( u_int8_t j = 0; j < X; ++j )
				this->_values[j + i * X] = T( i == j );
		}
		return ( *this );
	}

	inline Mat &	initScale( const Vec<T, X - 1> vec )
	{
		for ( u_int8_t i = 0; i < Y; ++i )
		{
			for ( u_int8_t j = 0; j < X; ++j )
				this->_values[j + i * X] = ( i == j && i != X - 1 ) ? T( vec[i] ) : T( 0 );
		}
		return ( *this );
	}

	inline Mat &	initTranslation( const Vec<T, Y - 1> vec )
	{
		for ( u_int8_t i = 0; i < Y; ++i )
		{
			for ( u_int8_t j = 0; j < X; ++j )
				this->_values[j + i * X] = ( j == Y - 1 && i != X - 1 ) ? T( vec[i] ) : T( i == j );
		}
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
		*this = *this * m;
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

template <typename T, u_int8_t X, u_int8_t Y>
std::ostream &		operator<<( std::ostream & o, Mat<T, X, Y> const & m )
{
	for ( int i = 0; i < Y; ++i )
	{
		for ( int j = 0; j < X; ++j )
		{
			o << m[j + i * X];
			if ( j == X - 1 )
				o << std::endl;
			else
				o << '\t';
		}
	}
	return ( o );
}

#endif // ! _MAT_HPP_
