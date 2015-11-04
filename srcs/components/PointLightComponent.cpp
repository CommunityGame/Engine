#include "PointLightComponent.hpp"

PointLightComponent::PointLightComponent() :
	_ambient( 0, 0, 0, 1 ),
	_diffuse( 0, 0, 0, 1 ),
	_specular( 0, 0, 0, 1 ),
	_shininess( 0 ),
	_radius( 1 ),
	_cutoff( 0 )
{
	return ;
}

void		PointLightComponent::update( double delta )
{
}

void		PointLightComponent::updateUniforms( Asset<Shader> const & shader, std::string const & name ) const
{
//	shader->bind();
	shader->getConstUniform( name + ".position" )->update( getTransform().getPosition() );
	shader->getConstUniform( name + ".ambient" )->update( _ambient );
	shader->getConstUniform( name + ".diffuse" )->update( _diffuse );
	shader->getConstUniform( name + ".specular" )->update( _specular );
	shader->getConstUniform( name + ".shininess" )->update( _shininess );
	shader->getConstUniform( name + ".radius" )->update( _radius );
	shader->getConstUniform( name + ".cutoff" )->update( _cutoff );
//	shader->unbind();
}

// SETTER
void		PointLightComponent::setAmbient( Colorf const & ambient )
{
	this->_ambient = ambient;
}

void		PointLightComponent::setDiffuse( Colorf const & diffuse )
{
	this->_diffuse = diffuse;
}

void		PointLightComponent::setSpecular( Colorf const & specular )
{
	this->_specular = specular;
}

void		PointLightComponent::setShininess( float shininess )
{
	this->_shininess = shininess;
}

void		PointLightComponent::setRadius( float radius )
{
	this->_radius = radius;
}

void		PointLightComponent::setCutoff( float cutoff )
{
	this->_cutoff = cutoff;
}


// GETTER
Colorf const & PointLightComponent::getAmbient( void ) const
{
	return ( this->_ambient );
}

Colorf const & PointLightComponent::getDiffuse( void ) const
{
	return ( this->_diffuse );
}

Colorf const & PointLightComponent::getSpecular( void ) const
{
	return ( this->_specular );
}

float			PointLightComponent::getShininess( void ) const
{
	return ( this->_shininess );
}

float			PointLightComponent::getRadius( void ) const
{
	return ( this->_radius );
}

float			PointLightComponent::getCutoff( void ) const
{
	return ( this->_cutoff );
}
