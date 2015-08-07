#include "Mesh.hpp"
#include "../render/Shader.hpp"

Mesh::Mesh( void )
{
	glGenBuffers( 1, & this->_vertexBufferObject );
	glGenBuffers( 1, & this->_indexBufferObject );
	this->_index = 0;
	return ;
}

Mesh::Mesh( std::vector<Vertexf> const & vertex, std::vector<GLuint> const & indices )
{
	glGenBuffers( 1, & this->_vertexBufferObject );
	glGenBuffers( 1, & this->_indexBufferObject );
	this->_vertices = vertex;
	this->_indices = indices;
	this->_index = (GLuint) indices.size();
}

Mesh::Mesh( Mesh const & cpy )
{
	*this = cpy;
}

Mesh::~Mesh( void )
{
	glDeleteBuffers( 1, & this->_vertexBufferObject );
	glDeleteBuffers( 1, & this->_indexBufferObject );
	return ;
}

Mesh & Mesh::operator=( Mesh const & rhs )
{
	if ( this != &rhs )
	{
		this->_vertexBufferObject = rhs.getVertexBufferObject();
		this->_indexBufferObject = rhs.getIndexBufferObject();
		this->_vertices = rhs.getVertices();
		this->_indices = rhs.getIndices();
		this->_index = rhs.getIndex();
	}
	return ( *this );
}

void	Mesh::putVertex( Vertexf const & vertex )
{
	this->_vertices.push_back( vertex );
	if (this->_index >= 3)
	{
		this->_indices.push_back( this->_index - 1 );
		this->_indices.push_back( this->_index - 2 );
		this->_indices.push_back( this->_index++ );
	}
	else
		this->_indices.push_back( this->_index++ );
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

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	return ;
}

void	Mesh::update( double delta )
{
	return ;
}

void	Mesh::render( RenderEngine const & renderEngine, GameObject const & parent, Shader const & shader, Camera const & camera ) const
{
	shader.bind();
	shader.updateUniforms( renderEngine, parent.getTransform(), camera/*, material*/ ); //TODO: material
	this->draw();
	shader.unbind();
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
		Vec3f normal = vec1.cross( vec2 ).normalized();
		v1->setNormal( v1->getNormal() + normal );
		v2->setNormal( v2->getNormal() + normal );
		v3->setNormal( v3->getNormal() + normal );
	}
	for ( it2 = this->_vertices.begin(); it2 != this->_vertices.end(); it2++ )
		(*it2).setNormal( (*it2).getNormal().normalized() );
}

// GETTER
GLuint const &			Mesh::getVertexBufferObject( void ) const
{
	return ( this->_vertexBufferObject );
}

GLuint const &			Mesh::getIndexBufferObject( void ) const
{
	return ( this->_indexBufferObject );
}

std::vector<Vertexf> const & Mesh::getVertices( void ) const
{
	return ( this->_vertices );
}

std::vector<GLuint> const &	Mesh::getIndices( void ) const
{
	return ( this->_indices );
}

GLuint const &			Mesh::getIndex( void ) const
{
	return ( this->_index );
}
