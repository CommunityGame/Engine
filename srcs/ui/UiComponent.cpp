#include <rapidxml.hpp>
#include "UiComponent.hpp"
#include "../utils/Utils.hpp"
#include "tag/Layout.hpp"
#include "../AGame.hpp"

const std::string	UiComponent::TAG = "UiComponent";

Shader *			UiComponent::_uiShader = nullptr;

UiComponent::UiComponent( const std::string & xml_file )
{
	if ( UiComponent::_uiShader == nullptr )
		UiComponent::_uiShader = new Shader( "ui" );

	glGenBuffers( 1, & this->_vertexBufferObject );
	glGenBuffers( 1, & this->_indexBufferObject );
	this->_index = 0;

	rapidxml::xml_document<> ui_doc;

	ui_doc.parse<0>( (char *) Utils::readFile( xml_file ).c_str() );

	rapidxml::xml_node<> * root_node = ui_doc.first_node( "Layout" );

	if ( root_node == nullptr )
	{
		Logger::e( TAG, "You must have a main Layout to contain other tags" );
		return ;
	}

	this->_mainLayout = new Layout( root_node, this, 0 );
	return ;
}

void		UiComponent::init( CoreEngine & coreEngine )
{
	this->_mainLayout->init( coreEngine );

	glBindBuffer( GL_ARRAY_BUFFER, this->_vertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER, this->_vertices.size() * sizeof( this->_vertices[0] ), & this->_vertices[0], GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_indexBufferObject );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof( this->_indices[0] ), & this->_indices[0], GL_STATIC_DRAW );
}

void		UiComponent::putVertex( UiPoint const & uiPoint ) const
{
	this->_vertices.push_back( uiPoint );
	return ;
}

void UiComponent::putIndices( std::vector<GLuint> indices ) const
{
	std::vector<GLuint>::iterator it;

	for ( it = indices.begin(); it != indices.end(); it++ )
		this->_indices.push_back( (*it) + this->_index );
	this->_index += indices.size();
}


void		UiComponent::render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{
	//TODO: change shader system
	UiComponent::_uiShader->bind();
	UiComponent::_uiShader->updateUniforms( renderEngine, this->getTransform(), camera/*, material*/ );

	glBindBuffer( GL_ARRAY_BUFFER, this->_vertexBufferObject );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof(UiPoint), 0 );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof(UiPoint), (void *)sizeof(Vec2i) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_indexBufferObject );
	glDrawElements( GL_TRIANGLES, (GLsizei) this->_indices.size(), GL_UNSIGNED_INT, nullptr );
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	UiComponent::_uiShader->unbind();

	return ;
}