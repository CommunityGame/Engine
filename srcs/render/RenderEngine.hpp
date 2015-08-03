#ifndef _RENDER_ENGINE_H_
# define _RENDER_ENGINE_H_

#include <vector>
#include "Window.hpp"
#include "Uniform.hpp"
#include "LightUniform.hpp"

class GameObject;
class LightComponent;
class Camera;
class Shader;

class RenderEngine
{
public:
	RenderEngine( Window const & window );
	~RenderEngine( void );

	void				render( GameObject const & object ) const;

	void				addLight( LightComponent * light );

	//	GETTER
	Camera *			getCamera( void ) const;

	//	SETTER
	void				setCamera( Camera * camera ) const;

private:
	const Window &		_window;
	mutable Camera *	_camera;
	Shader *			_defaultShader;
	std::vector<LightComponent *>	_lights;
};

#endif // ! _RENDER_ENGINE_H_
