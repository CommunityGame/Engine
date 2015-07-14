#ifndef _MESH_H_
# define _MESH_H_

#include <vector>
#include "../AObjectComponent.hpp"
#include "../math/Math.hpp"

class Mesh : public AObjectComponent
{
public:
	Mesh( void );
	Mesh( std::vector<Vertexf> const & vertex, std::vector<GLuint> const & indices );
	virtual ~Mesh( void );

	virtual void			input( Input & input, double delta );
	virtual void			update( double delta );
	virtual void			render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;
	virtual void			init( CoreEngine & coreEngine ) {};
	void					putVertex( Vertexf const & vertex );
	void					bufferData( void ) const;
	void					calcNormal( void );

	//	GETTER

private:
	void					draw( void ) const;

	GLuint					_vertexBufferObject;
	GLuint					_indexBufferObject;

	std::vector<Vertexf>	_vertices;
	std::vector<GLuint>		_indices;
	GLuint					_index;
};

#endif // ! _MESH_H_
