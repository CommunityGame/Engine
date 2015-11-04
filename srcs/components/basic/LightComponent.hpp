#ifndef _LIGHT_COMPONENT_HPP_
# define _LIGHT_COMPONENT_HPP_

#include "AObjectComponent.hpp"

class LightComponent : public AObjectComponent
{
public:
	virtual void	updateUniforms( Asset<Shader> const & shader, std::string const & name ) const = 0;
};

#endif // ! _LIGHT_COMPONENT_HPP_
