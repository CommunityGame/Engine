#ifndef _LIGHT_COMPONENT_H_
# define _LIGHT_COMPONENT_H_

#include "../AObjectComponent.hpp"

class LightComponent : public AObjectComponent
{
public:
	LightComponent( void );
//	LightComponent( Colorf const & color );
//	~LightComponent( void );

	virtual void		input( Input & input, double delta );
	virtual void		update( double delta );
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;
	virtual void		init( CoreEngine & coreEngine );

	// SETTER
	void					setAmbient( Colorf const & ambient );
	void					setDiffuse( Colorf const & diffuse );
	void					setSpecular( Colorf const & specular );
	void					setShininess( float shininess );

	// GETTER
	Colorf const &			getAmbient( void ) const;
	Colorf const &			getDiffuse( void ) const;
	Colorf const &			getSpecular( void ) const;
	float					getShininess( void ) const;

private:
	Colorf				_ambient;
	Colorf				_diffuse;
	Colorf				_specular;
	float				_shininess;
};

#endif // ! _LIGHT_COMPONENT_H_
