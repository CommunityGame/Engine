#include "MeshComponent.hpp"

MeshComponent::MeshComponent( void )
{
	return ;
}

MeshComponent::MeshComponent( Asset<Mesh> const & mesh ) :
	_mesh( mesh )
{
	return ;
}

MeshComponent::MeshComponent( MeshComponent const & cpy )
{
	*this = cpy;
}

MeshComponent::~MeshComponent( void )
{
	return ;
}

MeshComponent & MeshComponent::operator=( MeshComponent const & rhs )
{
	if ( this != &rhs )
	{
		this->_mesh = rhs.getMesh();
	}
	return ( *this );
}

void	MeshComponent::draw( void ) const
{
	glBindBuffer( GL_ARRAY_BUFFER, this->_mesh->getVertexBufferObject() );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexf), 0 );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void *)12 );
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertexf), (void *)24 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_mesh->getIndexBufferObject() );
	glDrawElements( GL_TRIANGLES, (GLsizei) this->_mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr );
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	return ;
}

void	MeshComponent::update( double delta )
{
	return ;
}

void	MeshComponent::render( RenderEngine const & renderEngine, GameObject const & parent, Asset<Shader> const & shader, Camera const & camera ) const
{
//	shader->bind();
	shader->updateUniforms( renderEngine, parent.getTransform(), camera/*, material*/ ); //TODO: material
	this->draw();
//	shader->unbind();
	return ;
}

// GETTER
Asset<Mesh> MeshComponent::getMesh( void ) const
{
	return this->_mesh;
}
