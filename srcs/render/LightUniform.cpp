#include "LightUniform.hpp"
#include "../components/LightComponent.hpp"

LightUniform::LightUniform( GLuint const program, std::string const & name ) :
	_position( program, Uniform::Type::VEC3, name + ".position" ),
	_ambient( program, Uniform::Type::VEC3, name + ".ambient" ),
	_diffuse( program, Uniform::Type::VEC3, name + ".diffuse" ),
	_specular( program, Uniform::Type::VEC3, name + ".specular" ),
	_shininess( program, Uniform::Type::FLOAT , name + ".shininess" )
{
	return ;
}

void LightUniform::update( LightComponent & light )
{
	this->_position.update( light.getTransform().getPosition() );
	this->_ambient.update( light.getAmbient() );
	this->_diffuse.update( light.getDiffuse() );
	this->_specular.update( light.getSpecular() );
	this->_shininess.update( light.getShininess() );
}
