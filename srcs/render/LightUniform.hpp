#ifndef _LIGHT_UNIFORM_H_
# define _LIGHT_UNIFORM_H_

#include "Uniform.hpp"

class LightComponent;

class LightUniform
{
public:
	LightUniform( LightComponent * light, GLuint const program, std::string const & name );

	void			update( void ) const;

private:
	Uniform			_position;
	Uniform			_ambient;
	Uniform			_diffuse;
	Uniform			_specular;
	Uniform			_shininess;

	LightComponent *_light;
};

#endif // ! _LIGHT_UNIFORM_H_
