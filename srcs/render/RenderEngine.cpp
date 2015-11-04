#include "RenderEngine.hpp"
#include "Shader.hpp"
#include "../GameObject.hpp"
#include "../components/Camera.hpp"
#include "../components/PointLightComponent.hpp"
#include "../assets/AssetsManager.hpp"
#include "../components/basic/LightComponent.hpp"

RenderEngine::RenderEngine( GLWindow const & window ) :
	_window( window )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glFrontFace( GL_CW );
	glCullFace( GL_BACK );
	glEnable( GL_CULL_FACE );

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


//	glShadeModel(GL_FLAT);
//	glProvokingVertex( GL_FIRST_VERTEX_CONVENTION );

//	GLuint vertexArrayID;
//	glGenVertexArrays( 1, &vertexArrayID );
//	glBindVertexArray( vertexArrayID );

	this->_defaultShader = AssetsManager::loadAsset<Shader>( "point_phong", "point_phong" );
	this->_defaultShader->getUniformValues().addValue( "ambientColor", Vec3f( 0.3f, 0.3f, 0.3f ) );
//	this->_defaultShader->getUniformValues().addValue( "numLights", 0 );
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
	return ;
}

void			RenderEngine::render( GameObject const & rootObject ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	this->_defaultShader->bind();

	Uniform const *	uniform;
	if ( ( uniform = this->_defaultShader->getConstUniform( "C_eyePos" ) ) != nullptr )
		uniform->update( this->_camera->getTransform().getPosition() );
	if ( ( uniform = this->_defaultShader->getConstUniform( "C_view" ) ) != nullptr )
		uniform->update( this->_camera->getTransformedViewMatrix() );
	if ( ( uniform = this->_defaultShader->getConstUniform( "C_projection" ) ) != nullptr )
		uniform->update( this->_camera->getPerspectiveMatrix() );

	int numLights = rootObject.updateAllUniforms( this->_defaultShader );
	if ( ( uniform = this->_defaultShader->getConstUniform( "C_numLights" ) ) != nullptr )
		uniform->update( numLights );

	rootObject.renderAll( * this, this->_defaultShader, * this->_camera );

	this->_defaultShader->unbind();

	//TODO: post process shaders
	//TODO: scattering light
}

//	GETTER
shared_ptr<Camera>	RenderEngine::getCamera( void ) const
{
	return ( this->_camera );
}

//	SETTER
void				RenderEngine::setCamera( shared_ptr<Camera> camera ) const
{
	this->_camera = camera;
	return ;
}
