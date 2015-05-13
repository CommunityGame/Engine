#ifndef _RENDER_ENGINE_H_
# define _RENDER_ENGINE_H_

#include "Window.hpp"
#include "../GameObject.hpp"

class RenderEngine
{
public:
	RenderEngine( Window const & window );
	~RenderEngine( void );

	void				render( GameObject const & object ) const;

	//	GETTER
	const Camera &		getCamera( void ) const;

	//	SETTER
	void				setCamera( Camera * camera ) const;

private:
	const Window &		_window;
	mutable Camera *	_camera;
	Shader *			_defaultShader;
};

#endif // ! _RENDER_ENGINE_H_
