#ifndef _TRANSFORM_H_
# define _TRANSFORM_H_
# include "Vec.tpp"
# include "Quat.tpp"

template <typename T>
class Transform
{
public:
	inline Transform<T>( void ) :
			_position( Vec<T, 3>() ),
			_scale( Vec<T, 3>() ),
			_rotation( Quat<T>() )
	{
		return ;
	}

	inline Transform<T>( Vec<T, 3> position, Vec<T, 3> scale, Quat<T> rotation ) :
			_position( position ),
			_scale( scale ),
			_rotation( rotation )
	{
		return ;
	}

	//	GETTER
	inline Vec<T, 3>	getPosition( void ) const
	{
		return ( this->_position );
	}

	inline Vec<T, 3>	getScale( void ) const
	{
		return ( this->_scale );
	}

	inline Quat<T>		getRotation( void ) const
	{
		return ( this->_rotation );
	}

	//	SETTER
	inline void			setPosition( Vec<T, 3> position )
	{
		this->_position = position;
		return ;
	}

	inline void			setScale( Vec<T, 3> scale )
	{
		this->_scale = scale;
		return ;
	}

	inline void			setRotation( Quat<T> rotation )
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