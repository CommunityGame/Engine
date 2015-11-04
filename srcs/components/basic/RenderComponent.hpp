#ifndef _RENDER_COMPONENT_H_
# define _RENDER_COMPONENT_H_

#include "AObjectComponent.hpp"

class RenderComponent : public AObjectComponent
{
public:
	/*!
	 * @function render
	 * @param renderEngine: is a reference to the instance of RenderEngine
	 * render this AObjectComponent
	 *
	 * @return void
	*/
	virtual void		render( RenderEngine const & renderEngine, GameObject const & parent, Asset<Shader> const & shader, Camera const & camera ) const = 0;

	virtual void		update( double delta ) {};
	virtual void		init( CoreEngine & coreEngine ) {};
};

#endif // ! _RENDER_COMPONENT_H_
