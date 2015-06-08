#ifndef _MESH_H_
# define _MESH_H_

#include <vector>
#include "../AObjectComponent.hpp"
#include "../math/Math.hpp"

class Mesh : public AObjectComponent
{
public:
	Mesh( void );
	virtual ~Mesh( void );

	virtual void		input( Input & input );
	virtual void		update( double delta );
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;
	void				putVertex( Vec3f const & vertex );
	void				bufferData( void ) const;

	//	GETTER

private:
	void				draw( void ) const;

	GLuint				_vertexBufferObject;
	GLuint				_indexBufferObject;

	std::vector<Vec3f>	_vertices;
	std::vector<GLuint>	_indices;
};

#endif // ! _MESH_H_
