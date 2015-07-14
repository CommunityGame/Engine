#ifndef _UNIFORM_H_
# define _UNIFORM_H_

#include <string>
#include "Window.hpp"
#include "../math/Math.hpp"

class Uniform
{
public:
	enum Type
	{
		INT,
		FLOAT,
		DOUBLE,
		VEC2,
		VEC3,
		MAT4,
		_SIZE
	};

	static const char *	typeEnum[];

	Uniform( void );
	Uniform( GLuint const program, Type const & type, std::string const & name );

	// GETTER
	const std::string &	getName( void ) const;
	Type				getType( void ) const;
	GLint				getLocation( void ) const;

	void				update( int value );
	void				update( float value );
	void				update( double value );
	void				update( Vec2f value );
	void				update( Vec3f value );
	void				update( Colorf value );
	void				update( Mat<float, 4, 4> value );

	static Type			stringToTypeEnum( std::string const & s );
	static std::string	typeEnumToString( Type const & t );

private:
	mutable GLint		_location;
	GLuint				_program;
	Type				_type;
	std::string			_name;

	static const std::string	TAG;
};

#endif // ! _UNIFORM_H_
