#include "RenderEngine.hpp"
#include "Shader.hpp"

RenderEngine::RenderEngine( Window const & window ) :
	_window( window )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glFrontFace( GL_CW );
	glCullFace( GL_BACK );
	// glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	GLuint vertexArrayID;
	glGenVertexArrays( 1, &vertexArrayID );
	glBindVertexArray( vertexArrayID );

	this->_defaultShader = new Shader( "basic" );
	return ;
}
RenderEngine::~RenderEngine( void )
{
	delete this->_defaultShader;
	return ;
}

void			RenderEngine::render( GameObject const & object ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	object.renderAll( * this, * this->_defaultShader, * this->_camera );
}

//	GETTER
Camera *		RenderEngine::getCamera( void ) const
{
	return ( this->_camera );
}

//	SETTER
void			RenderEngine::setCamera( Camera * camera ) const
{
	this->_camera = camera;
	return ;
}
