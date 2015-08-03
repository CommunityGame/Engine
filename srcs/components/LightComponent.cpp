#include "LightComponent.hpp"

LightComponent::LightComponent( void ) :
	_ambient( 0, 0, 0, 1 ),
	_diffuse( 0, 0, 0, 1 ),
	_specular( 0, 0, 0, 1 ),
	_shininess( 0 ),
	_uniform(  )
{

}

void		LightComponent::update( double delta )
{

}

void		LightComponent::render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{

}

void		LightComponent::init( CoreEngine & coreEngine )
{
	coreEngine.getRenderEngine().addLight( this );
}

// SETTER
void		LightComponent::setAmbient( Colorf const & ambient )
{
	this->_ambient = ambient;
}

void		LightComponent::setDiffuse( Colorf const & diffuse )
{
	this->_diffuse = diffuse;
}

void		LightComponent::setSpecular( Colorf const & specular )
{
	this->_specular = specular;
}

void		LightComponent::setShininess( float shininess )
{
	this->_shininess = shininess;
}

void		LightComponent::setUniform( LightUniform * uniform )
{
	this->_uniform = uniform;
}


// GETTER
Colorf const &	LightComponent::getAmbient( void ) const
{
	return ( this->_ambient );
}

Colorf const &	LightComponent::getDiffuse( void ) const
{
	return ( this->_diffuse );
}

Colorf const &	LightComponent::getSpecular( void ) const
{
	return ( this->_specular );
}

float		LightComponent::getShininess( void ) const
{
	return ( this->_shininess );
}

LightUniform const *	LightComponent::getUniform( void ) const
{
	return ( this->_uniform );
}
