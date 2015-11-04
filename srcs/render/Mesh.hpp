#ifndef _MESH_HPP_
# define _MESH_HPP_

#include <vector>
#include "../GameObject.hpp"
#include "../assets/IAsset.hpp"

class Mesh : public IAsset
{
public:
	Mesh( void );
	Mesh( Mesh const & cpy );
	Mesh( std::vector<Vertexf> const & vertex, std::vector<GLuint> const & indices );
	virtual ~Mesh( void );

	Mesh &					operator=( Mesh const & rhs );

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
	GLuint					_vertexBufferObject;
	GLuint					_indexBufferObject;

	std::vector<Vertexf>	_vertices;
	std::vector<GLuint>		_indices;
	GLuint					_index;
};

#endif // ! _MESH_HPP_
