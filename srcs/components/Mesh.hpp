#ifndef _MESH_H_
# define _MESH_H_

#include <vector>
#include "basic/RenderComponent.hpp"
#include "../GameObject.hpp"

class Mesh : public RenderComponent
{
public:
	Mesh( void );
	Mesh( Mesh const & cpy );
	Mesh( std::vector<Vertexf> const & vertex, std::vector<GLuint> const & indices );
	virtual ~Mesh( void );

	Mesh &	operator=( Mesh const & rhs );

	virtual void			render( RenderEngine const & renderEngine, GameObject const & parent, Shader const & shader, Camera const & camera ) const;
	virtual void			update( double delta );
	virtual void			init( CoreEngine & coreEngine ) {};
	void					putVertex( Vertexf const & vertex );
	void					bufferData( void ) const;
	void					calcNormal( void );

	//	GETTER
	GLuint const &			getVertexBufferObject( void ) const;
	GLuint const &			getIndexBufferObject( void ) const;
	std::vector<Vertexf> const & getVertices( void ) const;
	std::vector<GLuint> const &	getIndices( void ) const;
	GLuint const &			getIndex( void ) const;


private:
	void					draw( void ) const;

	GLuint					_vertexBufferObject;
	GLuint					_indexBufferObject;

	std::vector<Vertexf>	_vertices;
	std::vector<GLuint>		_indices;
	GLuint					_index;
};

#endif // ! _MESH_H_
