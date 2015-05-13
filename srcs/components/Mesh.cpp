#include <glad/glad.h>
#include "Mesh.hpp"
#include "../render/Shader.hpp"
#include "../GameObject.hpp"

Mesh::Mesh( void )
{
	glGenBuffers( 1, & this->_vertexBufferObject );
	glGenBuffers( 1, & this->_indexBufferObject );
	return ;
}

Mesh::~Mesh( void )
{
	glDeleteBuffers( 1, & this->_vertexBufferObject );
	glDeleteBuffers( 1, & this->_indexBufferObject );
	return ;
}

void	Mesh::putVertex( Vec3f const & vertex )
{
	static GLuint i = 0;
	this->_vertices.push_back( vertex );
	this->_indices.push_back( i++ );
	return ;
}

void	Mesh::bufferData( void ) const
{
	glBindBuffer( GL_ARRAY_BUFFER, this->_vertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER, this->_vertices.size() * sizeof( this->_vertices[0] ), & this->_vertices[0], GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_indexBufferObject );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof( this->_indices[0] ), & this->_indices[0], GL_STATIC_DRAW );
	return ;
}

void	Mesh::draw( void ) const
{
	glBindBuffer( GL_ARRAY_BUFFER, this->_vertexBufferObject );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_indexBufferObject );
	glDrawElements( GL_TRIANGLES, (GLsizei) this->_indices.size(), GL_UNSIGNED_INT, nullptr );
	return ;
}

void	Mesh::input( Input const & input )
{
	return ;
}

void	Mesh::update( double delta )
{
	return ;
}

void	Mesh::render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{
	shader.bind();
	shader.updateUniforms( renderEngine, this->getTransform(), camera/*, material*/ );
	this->draw();
	return ;
}

//	GETTER
Transformf const &	Mesh::getTransform( void ) const
{
	return ( this->_parent->getTransform() );
}
