#ifndef _TRANSFORM_H_
# define _TRANSFORM_H_

# include "Vec.tpp"
# include "Quat.tpp"
# include <iostream>

template <typename T>
class Transform
{
public:
	inline Transform<T>( void ) :
			_position( Vec<T, 3>() ),
			_scale( Vec3<T>( 1, 1, 1 ) ),
			_rotation( Quat<T>() )
	{
		return ;
	}

	inline Transform<T>( Vec<T, 3> const & position, Vec<T, 3> const & scale, Quat<T> const & rotation ) :
			_position( position ),
			_scale( scale ),
			_rotation( rotation )
	{
		return ;
	}

	inline Transform<T> &	translate( Vec<T, 3> const & vec )
	{
		this->_position += vec;
		return ( *this );
	}

	inline Transform<T> &	translate( T x, T y, T z )
	{
		this->_position += Vec3<T>( x, y, z );
		return ( *this );
	}

	inline Transform<T> &	rotate( Quat<T> rot )
	{
		this->_rotation = ( rot * this->_rotation ).normalized();
		return ( *this );
	}

	inline Transform<T> &	rotate( Vec3<T> axis, T angle )
	{
		this->_rotation = ( Quat<T>( axis, angle ) * this->_rotation ).normalized();
		return ( *this );
	}

	//	GETTER
	inline Vec<T, 3> const &	getPosition( void ) const
	{
		return ( this->_position );
	}

	inline Vec<T, 3> const &	getScale( void ) const
	{
		return ( this->_scale );
	}

	inline Quat<T> const &		getRotation( void ) const
	{
		return ( this->_rotation );
	}

	inline Mat<T, 4, 4>	getTransformedMatrix( void ) const
	{
		Mat<T, 4, 4>	translationMatrix;
		Mat<T, 4, 4>	scaleMatrix;
		Mat<T, 4, 4>	rotationMatrix;

		translationMatrix.initTranslation( this->_position );
		scaleMatrix.initScale( this->_scale );
		rotationMatrix = this->_rotation.toMatrix();
		return ( translationMatrix * rotationMatrix * scaleMatrix );
	}

	//	SETTER
	inline void			setPosition( Vec<T, 3> const & position )
	{
		this->_position = position;
		return ;
	}

	inline void			setScale( Vec<T, 3> const & scale )
	{
		this->_scale = scale;
		return ;
	}

	inline void			setRotation( Quat<T> const & rotation )
	{
		this->_rotation = rotation;
		return ;
	}

private:
	Vec<T, 3>	_position;
	Vec<T, 3>	_scale;
	Quat<T>		_rotation;
};

#endif // ! _TRANSFORM_H_
