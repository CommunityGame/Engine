#ifndef _UI_COMPONENT_H_
# define _UI_COMPONENT_H_

#include "../components/basic/RenderComponent.hpp"
#include "../render/Shader.hpp"
#include "../components/Camera.hpp"
#include "UiPoint.hpp"

class Layout;

class UiComponent : public RenderComponent
{
public:
	UiComponent( std::string const & xml );
	virtual void			render( RenderEngine const & renderEngine, GameObject const & parent, Shader const & shader, Camera const & camera ) const;

	virtual void			init( CoreEngine & coreEngine );

	void					putVertex( UiPoint const & uiPoint ) const;
	void					putIndices( std::vector<GLuint> indices ) const;

private:
	Layout *					_mainLayout;
	static Shader *				_uiShader;

	GLuint						_vertexBufferObject;
	GLuint						_indexBufferObject;

	mutable std::vector<UiPoint>		_vertices;
	mutable std::vector<GLuint>			_indices;
	mutable GLuint						_index;

	static const std::string	TAG;
};

#endif // ! _UI_COMPONENT_H_
