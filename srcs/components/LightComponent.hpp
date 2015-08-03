#ifndef _LIGHT_COMPONENT_H_
# define _LIGHT_COMPONENT_H_

#include "basic/RenderComponent.hpp"

class LightComponent : public RenderComponent
{
public:
	LightComponent( void );
//	LightComponent( Colorf const & color );
//	~LightComponent( void );

	virtual void		update( double delta );
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;
	virtual void		init( CoreEngine & coreEngine );

	// SETTER
	void					setAmbient( Colorf const & ambient );
	void					setDiffuse( Colorf const & diffuse );
	void					setSpecular( Colorf const & specular );
	void					setShininess( float shininess );
	void					setUniform( LightUniform * uniform );

	// GETTER
	Colorf const &			getAmbient( void ) const;
	Colorf const &			getDiffuse( void ) const;
	Colorf const &			getSpecular( void ) const;
	float					getShininess( void ) const;
	LightUniform const *	getUniform( void ) const;

private:
	Colorf				_ambient;
	Colorf				_diffuse;
	Colorf				_specular;
	float				_shininess;
	LightUniform *		_uniform;
};

#endif // ! _LIGHT_COMPONENT_H_
