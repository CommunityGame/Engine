#ifndef _UNIFORM_H_
# define _UNIFORM_H_

#include <string>
#include "GLWindow.hpp"
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
		LIGHT,
		_SIZE
	};

	static const char *	typeEnum[];

	Uniform( void );
	Uniform( GLuint const program, Type const & type, std::string const & name );

	// GETTER
	const std::string &	getName( void ) const;
	Type				getType( void ) const;
	GLint				getLocation( void ) const;

	void				update( int value ) const;
	void				update( float value ) const;
	void				update( double value ) const;
	void				update( Vec2f value ) const;
	void				update( Vec3f value ) const;
	void				update( Colorf value ) const;
	void				update( Mat<float, 4, 4> value ) const;

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
