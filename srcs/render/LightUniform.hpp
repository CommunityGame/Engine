#ifndef _LIGHT_UNIFORM_H_
# define _LIGHT_UNIFORM_H_

#include "Uniform.hpp"

class LightComponent;

class LightUniform
{
public:
	LightUniform( GLuint const program, std::string const & name );

	void			update( LightComponent & light );

private:
	Uniform			_position;
	Uniform			_ambient;
	Uniform			_diffuse;
	Uniform			_specular;
	Uniform			_shininess;
};

#endif // ! _LIGHT_UNIFORM_H_
