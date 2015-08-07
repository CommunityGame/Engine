#ifndef _QUAT_HPP_
#define _QUAT_HPP_

#include "Point.tpp"
#include "Mat.tpp"
#include "Math.hpp"

template <typename T>
class Quat : public Point<T, 4>
{
public:
	inline Quat( void )
	{
		this->_values[0] = 1;
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

	inline Quat( const Vec3<T> & axis, T angle )
	{
		T sinHalfAngle = sinf( angle / T( 2 ) );
		T cosHalfAngle = cosf( angle / T( 2 ) );

		(*this)[0] = cosHalfAngle;
		(*this)[1] = axis.getX() * sinHalfAngle;
		(*this)[2] = axis.getY() * sinHalfAngle;
		(*this)[3] = axis.getZ() * sinHalfAngle;
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

	inline Mat<T, 4, 4>	toMatrix( void ) const
	{
		Mat<T, 4, 4>	result;
		result[0] = T(1) - T(2) * getJ() * getJ() - T(2) * getK() * getK();
		result[1] = T(2) * getI() * getJ() - T(2) * getK() * getR();
		result[2] = T(2) * getI() * getK() + T(2) * getJ() * getR();
		result[3] = T(0);
		result[4] = T(2) * getI() * getJ() + T(2) * getK() * getR();
		result[5] = T(1) - T(2) * getI() * getI() - T(2) * getK() * getK();
		result[6] = T(2) * getJ() * getK() - T(2) * getI() * getR();
		result[7] = T(0);
		result[8] = T(2) * getI() * getK() - T(2) * getJ() * getR();
		result[9] = T(2) * getJ() * getK() + T(2) * getI() * getR();
		result[10] = T(1) - T(2) * getI() * getI() - T(2) * getJ() * getJ();
		result[11] = T(0);
		result[12] = T(0);
		result[13] = T(0);
		result[14] = T(0);
		result[15] = T(1);
		return ( result );
	}

//	inline Mat<T, 4, 4> toMatrix( void ) const
//	{
//		Vec3<T> forward( 2.0f * (getI() * getK() - getR() * getJ()), 2.0f * (getJ() * getK() + getR() * getI()), 1.0f - 2.0f * (getI() * getI() + getJ() * getJ()));
//		Vec3<T> up( 2.0f * (getI()*getJ() + getR()*getK()), 1.0f - 2.0f * (getI()*getI() + getK()*getK()), 2.0f * (getJ()*getK() - getR()*getI()));
//		Vec3<T> right( 1.0f - 2.0f * (getJ()*getJ() + getK()*getK()), 2.0f * (getI()*getJ() - getR()*getK()), 2.0f * (getI()*getK() + getR()*getJ()));
//
//		return Mat4<T>().initRotationFromVectors( forward, up, right );
//	}

	inline Quat		operator*( Quat const & rhs ) const
	{
		Quat		result;

		result[0] = rhs.getR() * this->getR() - rhs.getI() * this->getI() - rhs.getJ() * this->getJ() - rhs.getK() * this->getK();
		result[1] = rhs.getR() * this->getI() + rhs.getI() * this->getR() - rhs.getJ() * this->getK() + rhs.getK() * this->getJ();
		result[2] = rhs.getR() * this->getJ() + rhs.getI() * this->getK() + rhs.getJ() * this->getR() - rhs.getK() * this->getI();
		result[3] = rhs.getR() * this->getK() - rhs.getI() * this->getJ() + rhs.getJ() * this->getI() + rhs.getK() * this->getR();
		return ( result );
	}

	inline Quat &	operator*=( Quat const & rhs )
	{
		*this = *this * rhs;
		return ( *this );
	}

	inline Quat		operator*( Vec3<T> const & rhs ) const
	{
		Quat		result;
		result[0] = - ( this->getI() * rhs.getX() ) - ( this->getJ() * rhs.getY() ) - ( this->getK() * rhs.getZ() );
		result[1] =   ( this->getR() * rhs.getX() ) + ( this->getJ() * rhs.getZ() ) - ( this->getK() * rhs.getY() );
		result[2] =   ( this->getR() * rhs.getY() ) + ( this->getK() * rhs.getX() ) - ( this->getI() * rhs.getZ() );
		result[3] =   ( this->getR() * rhs.getZ() ) + ( this->getI() * rhs.getY() ) - ( this->getJ() * rhs.getX() );
		return ( result );
	}

	inline Quat		operator/( Quat const & rhs ) const
	{
		Quat result;
		T div = T( rhs.getR() * rhs.getR() );
		div += T( rhs.getI() * rhs.getI() );
		div += T( rhs.getJ() * rhs.getJ() );
		div += T( rhs.getK() * rhs.getK() );

		result[0] = ( rhs.getR() * this->getR() + rhs.getI() * this->getI() + rhs.getJ() * this->getJ() + rhs.getK() * this->getK() ) / div;
		result[1] = ( rhs.getR() * this->getI() - rhs.getI() * this->getR() - rhs.getJ() * this->getK() + rhs.getK() * this->getJ() ) / div;
		result[2] = ( rhs.getR() * this->getJ() + rhs.getI() * this->getK() - rhs.getJ() * this->getR() - rhs.getK() * this->getI() ) / div;
		result[3] = ( rhs.getR() * this->getK() - rhs.getI() * this->getJ() + rhs.getJ() * this->getI() - rhs.getK() * this->getR() ) / div;
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

	inline Vec3<T>	getForward( void ) const
	{
		return ( Vec3<T>( 0, 0, 1 ).rotate( * this ) );
	}

	inline Vec3<T>	getBack( void ) const
	{
		return ( Vec3<T>( 0, 0, -1 ).rotate( * this ) );
	}

	inline Vec3<T>	getRight( void ) const
	{
		return ( Vec3<T>( 1, 0, 0 ).rotate( * this ) );
	}

	inline Vec3<T>	getLeft( void ) const
	{
		return ( Vec3<T>( -1, 0, 0 ).rotate( * this ) );
	}

	inline Vec3<T>	getUp( void ) const
	{
		return ( Vec3<T>( 0, 1, 0 ).rotate( * this ) );
	}

	inline Vec3<T>	getDown( void ) const
	{
		return ( Vec3<T>( 0, -1, 0 ).rotate( * this ) );
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

	std::string		toString( void ) const
	{
		std::stringstream ss;
		ss << "Quat( ";
		ss << (*this)[0] << ", ";
		ss << (*this)[1] << ", ";
		ss << (*this)[2] << ", ";
		ss << (*this)[3] << " )";
		return ( ss.str() );
	}
};

#endif //_QUAT_HPP_
