#include "Uniform.hpp"

const char *	Uniform::typeEnum[] =
{
		"int",
		"float",
		"double",
		"vec2",
		"vec3",
		"mat4"
};

Uniform::Uniform( GLuint const program, Type const & type, std::string const & name ) :
	_type( type ),
	_name( name ),
	_location( -1 ),
	_program( program )
{
	this->_location = -1;
	return ;
}

Uniform::Type		Uniform::stringToTypeEnum( std::string const & s )
{
	uint8_t		i = 0;

	while ( i < Uniform::Type::_SIZE )
	{
		if ( Uniform::typeEnum[i] == s )
			return ( (Uniform::Type)i );
		i++;
	}
	Logger::e( "Unable to find Type enum: " + s );
	return ( (Uniform::Type)-1 );
}

std::string			Uniform::typeEnumToString( Uniform::Type const & t )
{
	if ( t == (Uniform::Type)-1 )
	{
		Logger::e( "Invalid enum !" );
		return "";
	}
	return ( Uniform::typeEnum[t] );
}

//void				Uniform::update( void )
//{
//	switch ( this->_type )
//	{
//		case Type::INT:
//			glUniform1i( this->_location,  );
//	}
//}

std::string Uniform::getName( void ) const
{
	return ( this->_name );
}

GLint Uniform::getLocation( void ) const
{
	if ( this->_location == -1 )
	{
		this->_location = glGetUniformLocation( this->_program, this->_name.c_str() );
//		if ( this->_location == -1 )
//			Logger::e( "Can't find uniform" );
	}
	return ( this->_location );
}
