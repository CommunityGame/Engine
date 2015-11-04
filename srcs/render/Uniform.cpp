#include "Uniform.hpp"

const std::string	Uniform::TAG = "Uniform";

const char *	Uniform::typeEnum[] =
{
		"int",
		"float",
		"double",
		"vec2",
		"vec3",
		"mat4"
};

Uniform::Uniform( void )
{

}

Uniform::Uniform( GLuint const program, Type const & type, std::string const & name ) :
	_type( type ),
	_name( name ),
	_location( -1 ),
	_program( program )
{
//	Logger::d( TAG, "Added uniform: " + this->_name );
	return ;
}

Uniform &			Uniform::operator=( Uniform const & rhs )
{
	if ( this != & rhs )
	{
		this->_program = rhs.getProgram();
		this->_name = rhs.getName();
		this->_location = rhs.getLocation();
		this->_type = rhs.getType();
	}
	return ( * this );
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
	Logger::e( TAG, "Unable to find Type enum: " + s );
	return ( (Uniform::Type)-1 );
}

std::string			Uniform::typeEnumToString( Uniform::Type const & t )
{
	if ( t == (Uniform::Type)-1 )
	{
		Logger::e( TAG, "Invalid enum !" );
		return "";
	}
	return ( Uniform::typeEnum[t] );
}

const std::string &	Uniform::getName( void ) const
{
	return ( this->_name );
}

Uniform::Type	Uniform::getType( void ) const
{
	return ( this->_type );
}

GLint			Uniform::getLocation( void ) const
{
	if ( this->_location == -1 )
		this->_location = glGetUniformLocation( this->_program, this->_name.c_str() );
	return ( this->_location );
}

GLuint			Uniform::getProgram( void ) const
{
	return ( this->_program );
}

void			Uniform::update( int value ) const
{
	glUniform1i( this->getLocation(), value );
}

void			Uniform::update( float value ) const
{
	glUniform1f( this->getLocation(), value );
}

void			Uniform::update( double value ) const
{
	glUniform1f( this->getLocation(), (float)value );
}

void			Uniform::update( Vec2f value ) const
{
	glUniform2f( this->getLocation(), value[0], value[1] );
}

void			Uniform::update( Vec3f value ) const
{
	glUniform3f( this->getLocation(), value[0], value[1], value[2] );
}

void			Uniform::update( Colorf value ) const
{
//	std::cout << this->getLocation() << std::endl;
	glUniform3f( this->getLocation(), value.getR(), value.getG(), value.getB() );
}

void			Uniform::update( Mat<float, 4, 4> value ) const
{
	glUniformMatrix4fv( this->getLocation(), 1, GL_FALSE, value.getValues() );
}

