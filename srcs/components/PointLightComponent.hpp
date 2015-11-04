#ifndef _LIGHT_COMPONENT_H_
# define _LIGHT_COMPONENT_H_

#include "basic/LightComponent.hpp"

class PointLightComponent : public LightComponent
{
public:
	PointLightComponent();
//	PointLightComponent( Colorf const & color );
//	~PointLightComponent( void );

	virtual void			update( double delta );
	virtual void			updateUniforms( Asset<Shader> const & shader, std::string const & name ) const;

	// SETTER
	void					setAmbient( Colorf const & ambient );
	void					setDiffuse( Colorf const & diffuse );
	void					setSpecular( Colorf const & specular );
	void					setShininess( float shininess );
	void					setRadius( float radius );
	void					setCutoff( float cutoff );

	// GETTER
	Colorf const &			getAmbient( void ) const;
	Colorf const &			getDiffuse( void ) const;
	Colorf const &			getSpecular( void ) const;
	float					getShininess( void ) const;
	float					getRadius( void ) const;
	float					getCutoff( void ) const;

private:
	Colorf				_ambient;
	Colorf				_diffuse;
	Colorf				_specular;
	float				_shininess;
	float				_radius;
	float				_cutoff;
};

#endif // ! _LIGHT_COMPONENT_H_
