#ifndef _RENDER_ENGINE_H_
# define _RENDER_ENGINE_H_

#include <vector>
#include "GLWindow.hpp"
#include "Uniform.hpp"
#include "LightUniform.hpp"

class GameObject;
class LightComponent;
class Camera;
class Shader;

class RenderEngine
{
public:
	RenderEngine( GLWindow const & window );
	~RenderEngine( void );

	void				render( GameObject const & object ) const;

	void				addLight( LightComponent * light );

	//	GETTER
	shared_ptr<Camera>	getCamera( void ) const;

	//	SETTER
	void				setCamera( shared_ptr<Camera> camera ) const;

private:
	const GLWindow &		_window;
	mutable shared_ptr<Camera>	_camera;
	Shader *			_defaultShader;
	std::vector<LightComponent *>	_lights;
};

#endif // ! _RENDER_ENGINE_H_
