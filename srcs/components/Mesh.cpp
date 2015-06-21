#include <glad/glad.h>
#include "Mesh.hpp"
#include "../render/Shader.hpp"

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

void	Mesh::putVertex( Vertexf const & vertex )
{
	static GLuint i = 0;
	this->_vertices.push_back( vertex );
	if (i >= 3)
	{
		this->_indices.push_back( i - 1 );
		this->_indices.push_back( i - 2 );
		this->_indices.push_back( i++ );
	}
	else
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
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexf), 0 );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void *)12 );
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void *)24 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_indexBufferObject );
	glDrawElements( GL_TRIANGLES, (GLsizei) this->_indices.size(), GL_UNSIGNED_INT, nullptr );
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );

	return ;
}

void	Mesh::input( Input & input, double delta )
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

void	Mesh::calcNormal( void )
{
	std::vector< GLuint >::const_iterator it;
	std::vector< Vertexf >::iterator it2;

	for ( it = this->_indices.begin(); it != this->_indices.end(); it += 3 )
	{
		Vertexf * v1 = &this->_vertices[it[0]];
		Vertexf * v2 = &this->_vertices[it[1]];
		Vertexf * v3 = &this->_vertices[it[2]];
		Vec3f vec1 = v2->getPosition() - v1->getPosition();
		Vec3f vec2 = v3->getPosition() - v1->getPosition();
		Vec3f normal = vec2.cross( vec1 ).normalized();
		v1->setNormal( v1->getNormal() + normal );
		v2->setNormal( v2->getNormal() + normal );
		v3->setNormal( v3->getNormal() + normal );
	}
	for ( it2 = this->_vertices.begin(); it2 != this->_vertices.end(); it2++ )
		(*it2).setNormal( (*it2).getNormal().normalized() );
}