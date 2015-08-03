#include "RenderEngine.hpp"
#include "Shader.hpp"
#include "../GameObject.hpp"
#include "../components/Camera.hpp"
#include "../components/LightComponent.hpp"

RenderEngine::RenderEngine( Window const & window ) :
	_window( window )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glFrontFace( GL_CW );
	glCullFace( GL_BACK );
	glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


//	glShadeModel(GL_FLAT);
//	glProvokingVertex( GL_FIRST_VERTEX_CONVENTION );

	GLuint vertexArrayID;
	glGenVertexArrays( 1, &vertexArrayID );
	glBindVertexArray( vertexArrayID );

//	this->_defaultShader = new Shader( "ambiant" );
	this->_defaultShader = new Shader( "phong" );
	this->_defaultShader->getUniformValues().addValue( "ambiantColor", Vec3f( 0.3f, 0.3f, 0.3f ) );
	this->_defaultShader->getUniformValues().addValue( "numLights", 0 );
//	int maxLights = 10;
//	for ( int i = 0; i < maxLights; ++i )
//	{
//		std::stringstream	ss;
//		ss << "lights[" << i << "]";
//		this->_lightsUniform.push_back( LightUniform( this->_defaultShader->getProgram(), ss.str() ) );
//	}
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

	this->_defaultShader->getUniformValues().addValue( "numLights", (int)this->_lights.size() );
	this->_defaultShader->getUniformValues().addValue( "eyePos", this->_camera->getTransform().getPosition() );


	std::vector<LightComponent *>::const_iterator it;
	int i = 0;
	for ( it = this->_lights.begin(); it != this->_lights.end(); it++ )
	{
		this->_defaultShader->getUniformValues().addValue( "lights[" + std::to_string( i ) + "]", (*it)->getUniform() );
		i++;
	}

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

void RenderEngine::addLight( LightComponent * light )
{
	light->setUniform( new LightUniform( light, this->_defaultShader->getProgram(), "lights[" + std::to_string( this->_lights.size() ) + "]" ) );
	this->_lights.push_back( light );
}
