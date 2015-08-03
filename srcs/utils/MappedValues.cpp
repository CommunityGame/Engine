#include <iostream>
#include "MappedValues.hpp"
#include "../render/LightUniform.hpp"

void		MappedValues::addValue( std::string const & name, int value )
{
	this->_intValues[name] = value;
}

void		MappedValues::addValue( std::string const & name, float value )
{
	this->_floatValues[name] = value;
}

void		MappedValues::addValue( std::string const & name, double value )
{
	this->_doubleValues[name] = value;
}

void		MappedValues::addValue( std::string const & name, Vec2f const & value )
{
	this->_vec2fValues[name] = value;
}

void		MappedValues::addValue( std::string const & name, Vec3f const & value )
{
	this->_vec3fValues[name] = value;
}

void		MappedValues::addValue( std::string const & name, Mat4f const & value )
{
	this->_mat4fValues[name] = value;
}

void		MappedValues::addValue( std::string const & name, LightUniform const * value )
{
	this->_lightValues[name] = value;
}


int			MappedValues::getInt( std::string const & name ) const
{
	std::map<std::string, int>::const_iterator it = this->_intValues.find( name );

	if( it != this->_intValues.end() )
		return ( it->second );
	return ( 0 );
}

float		MappedValues::getFloat( std::string const & name ) const
{
	std::map<std::string, float>::const_iterator it = this->_floatValues.find( name );

	if( it != this->_floatValues.end() )
		return ( it->second );
	return ( 0 );
}

double		MappedValues::getDouble( std::string const & name ) const
{
	std::map<std::string, double>::const_iterator it = this->_doubleValues.find( name );

	if( it != this->_doubleValues.end() )
		return ( it->second );
	return ( 0 );
}

Vec2f const &	MappedValues::getVec2f( std::string const & name ) const
{
	std::map<std::string, Vec2f>::const_iterator it = this->_vec2fValues.find( name );

	if( it != this->_vec2fValues.end() )
		return ( it->second );
	return ( Vec2f::ZERO );
}

Vec3f const &	MappedValues::getVec3f( std::string const & name ) const
{
	std::map<std::string, Vec3f>::const_iterator it = this->_vec3fValues.find( name );

	if( it != this->_vec3fValues.end() )
		return (it->second);
	return ( Vec3f::ZERO );
}

Mat4f const &	MappedValues::getMat4f( std::string const & name ) const
{
	std::map<std::string, Mat4f>::const_iterator it = this->_mat4fValues.find( name );

	if( it != this->_mat4fValues.end() )
		return ( it->second );
	return ( Mat4f::ZERO );
}

LightUniform const *	MappedValues::getLight( std::string const & name ) const
{
	std::map<std::string, LightUniform const *>::const_iterator it = this->_lightValues.find( name );

	if( it != this->_lightValues.end() )
		return ( it->second );
	return ( nullptr );
}