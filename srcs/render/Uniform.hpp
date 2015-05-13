#ifndef _UNIFORM_H_
# define _UNIFORM_H_

#include <string>
#include "Window.hpp"

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

	Uniform( GLuint const program, Type const & type, std::string const & name );

	// GETTER
	std::string			getName( void ) const;

//	void				update( T );

	static Type			stringToTypeEnum( std::string const & s );
	static std::string	typeEnumToString( Type const & t );

private:
	GLint				_location;
//	GLuint				_program;
	Type				_type;
	std::string			_name;
};

#endif // ! _UNIFORM_H_
