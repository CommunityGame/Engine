#ifndef _RENDER_ENGINE_H_
# define _RENDER_ENGINE_H_

#include <vector>
#include "GLWindow.hpp"
#include "Uniform.hpp"
#include "LightUniform.hpp"
#include "../assets/Asset.hpp"
#include "Shader.hpp"

class GameObject;
class LightComponent;
class Camera;

class RenderEngine
{
public:
	RenderEngine( GLWindow const & window );
	~RenderEngine( void );

	void				render( GameObject const & rootObject ) const;

	//	GETTER
	shared_ptr<Camera>	getCamera( void ) const;

	//	SETTER
	void				setCamera( shared_ptr<Camera> camera ) const;

private:
	const GLWindow &				_window;
	mutable shared_ptr<Camera>		_camera;
	Asset<Shader>					_defaultShader;
};

#endif // ! _RENDER_ENGINE_H_
