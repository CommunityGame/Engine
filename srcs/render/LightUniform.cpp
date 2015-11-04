#include "LightUniform.hpp"
//#include "PointLightComponent.hpp"
//
//LightUniform::LightUniform( PointLightComponent * light, GLuint const program, std::string const & name ) :
//	_light( light ),
//	_position( program, Uniform::Type::VEC3, name + ".position" ),
//	_ambient( program, Uniform::Type::VEC3, name + ".ambient" ),
//	_diffuse( program, Uniform::Type::VEC3, name + ".diffuse" ),
//	_specular( program, Uniform::Type::VEC3, name + ".specular" ),
//	_shininess( program, Uniform::Type::FLOAT , name + ".shininess" ),
//	_radius( program, Uniform::Type::FLOAT , name + ".radius" ),
//	_cutoff( program, Uniform::Type::FLOAT , name + ".cutoff" )
//{
//	return ;
//}
//
//void LightUniform::update( void ) const
//{
//	this->_position.update( this->_light->getTransform().getPosition() );
//	this->_ambient.update( this->_light->getAmbient() );
//	this->_diffuse.update( this->_light->getDiffuse() );
//	this->_specular.update( this->_light->getSpecular() );
//	this->_shininess.update( this->_light->getShininess() );
//	this->_radius.update( this->_light->getRadius() );
//	this->_cutoff.update( this->_light->getCutoff() );
//}
