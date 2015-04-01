#ifndef _QUAT_HPP_
#define _QUAT_HPP_

#include "Point.tpp"
#include "Mat.tpp"

template <typename T>
class Quat : public Point<T, 4>
{
public:
	inline Quat( void )
	{
		this->_values[0] = 0;
		this->_values[1] = 0;
		this->_values[2] = 0;
		this->_values[3] = 0;
		return ;
	}

	inline Quat( T r, T i, T j, T k )
	{
		this->_values[0] = r;
		this->_values[1] = i;
		this->_values[2] = j;
		this->_values[3] = k;
		return ;
	}

	inline Quat		conjugated( void ) const
	{
		return ( Quat( this->getR(), -this->getI(), -this->getJ(), -this->getK() ) );
	}

	inline Quat &	conjugate( void )
	{
		*this = this->conjugated();
		return ( *this );
	}

	inline Quat		inversed( void ) const
	{
		Quat		result( this->conjugated() );
		T			squaredNorm( this->squaredNorm() );

		result[0] /= squaredNorm;
		result[1] /= squaredNorm;
		result[2] /= squaredNorm;
		result[3] /= squaredNorm;
		return ( result );
	}

	inline Quat &	inverse( void )
	{
		*this = this->inversed();
		return ( *this );
	}

	inline T		squaredNorm( void ) const
	{
		return ( this->getR() * this->getR() + this->getI() * this->getI() + this->getJ() * this->getJ() + this->getK() * this->getK() );
	}

	inline T		norm( void ) const
	{
		return ( sqrt( this->squaredNorm() ) );
	}

	inline Quat		normalized( void ) const
	{
		Quat	result( *this );
		T		norm( this->norm() );

		result[0] /= norm;
		result[1] /= norm;
		result[2] /= norm;
		result[3] /= norm;
		return ( result );
	}

	inline Quat &	normalize( void )
	{
		T		norm( this->norm() );

		(*this)[0] /= norm;
		(*this)[1] /= norm;
		(*this)[2] /= norm;
		(*this)[3] /= norm;
		return ( *this );
	}

	inline Mat<T, 4, 4>	toMatrix( void )
	{
		Mat<T, 4, 4>	result;

		result[0] = this->getR();	result[1] = this->getI();	result[2] = this->getJ();	result[3] = this->getK();
		result[4] = -this->getI();	result[5] = this->getR();	result[6] = -this->getK();	result[7] = this->getJ();
		result[8] = -this->getJ();	result[9] = this->getK();	result[10] = this->getR();	result[11] = -this->getI();
		result[12] = -this->getK();	result[13] = -this->getJ();	result[14] = this->getI();	result[15] = this->getR();
		return ( result );
	}

	inline Quat		operator*( Quat const & rhs ) const
	{
		Quat		result;

		result[0] = ( rhs.getR() * this->getR() - rhs.getI() * this->getI() - rhs.getJ() * this->getJ() - rhs.getK() * this->getK() );
		result[1] = ( rhs.getR() * this->getI() + rhs.getI() * this->getR() - rhs.getJ() * this->getK() + rhs.getK() * this->getJ() );
		result[2] = ( rhs.getR() * this->getJ() + rhs.getI() * this->getK() + rhs.getJ() * this->getR() - rhs.getK() * this->getI() );
		result[3] = ( rhs.getR() * this->getK() - rhs.getI() * this->getJ() + rhs.getJ() * this->getI() + rhs.getK() * this->getR() );
		return ( result );
	}

	inline Quat &	operator*=( Quat const & rhs )
	{
		*this = *this * rhs;
		return ( *this );
	}

	inline Quat		operator/( Quat const & rhs ) const
	{
		Quat result;
		T div = T( rhs.getR() * rhs.getR());
		div += T( rhs.getI() * rhs.getI());
		div += T( rhs.getJ() * rhs.getJ());
		div += T( rhs.getK() * rhs.getK());

		result[0] = (rhs.getR() * this->getR() + rhs.getI() * this->getI() + rhs.getJ() * this->getJ() + rhs.getK() * this->getK()) / div;
		result[1] = (rhs.getR() * this->getI() - rhs.getI() * this->getR() - rhs.getJ() * this->getK() + rhs.getK() * this->getJ()) / div;
		result[2] = (rhs.getR() * this->getJ() + rhs.getI() * this->getK() - rhs.getJ() * this->getR() - rhs.getK() * this->getI()) / div;
		result[3] = (rhs.getR() * this->getK() - rhs.getI() * this->getJ() + rhs.getJ() * this->getI() - rhs.getK() * this->getR()) / div;
		return (result);
	}

	inline Quat &	operator/=( Quat const & rhs )
	{
		*this = *this / rhs;
		return ( *this );
	}

	/**
	 * GETTER
	 */
	inline T		getR( void ) const
	{
		return ( (*this)[0] );
	}

	inline T		getI( void ) const
	{
		return ( (*this)[1] );
	}

	inline T		getJ( void ) const
	{
		return ( (*this)[2] );
	}

	inline T		getK( void ) const
	{
		return ( (*this)[3] );
	}

	/**
	 * SETTER
	 */
	inline void		setR( const T & r )
	{
		(*this)[0] = r;
	}

	inline void		setI( const T & i )
	{
		(*this)[1] = i;
	}

	inline void		setJ( const T & j )
	{
		(*this)[2] = j;
	}

	inline void		setK( const T & k )
	{
		(*this)[3] = k;
	}

	inline void		set( const T & r, const T & i, const T & j, const T & k )
	{
		(*this)[0] = r;
		(*this)[1] = i;
		(*this)[2] = j;
		(*this)[3] = k;
	}
};

#endif //_QUAT_HPP_
