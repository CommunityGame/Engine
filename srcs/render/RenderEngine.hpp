#ifndef _RENDER_ENGINE_H_
# define _RENDER_ENGINE_H_

#include "Window.hpp"

class RenderEngine
{
public:
	RenderEngine( Window * window );

private:
	Window *			_window;
};

#endif // ! _RENDER_ENGINE_H_
