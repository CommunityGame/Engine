#include <glad/glad.h>
#include "Shader.hpp"
#include "../components/Camera.hpp"
#include "../utils/Utils.hpp"

Shader::Shader( const std::string & file ) :
	_program( glCreateProgram() )
{
	if ( this->_program == 0u )
	{
		Logger::e( "Failed to create program shader" );
		return ;
	}

	const std::string vertexFile = this->loadShader( "./resources/shaders/" + file + ".vert" );
	if ( vertexFile.empty() )
		Logger::e( "Unable to load vertex shader" );
	const std::string fragmentFile = this->loadShader( "./resources/shaders/" + file + ".frag" );
	if ( fragmentFile.empty() )
		Logger::e( "Unable to load fragment shader" );

	this->_vertexShader = this->makeShader( GL_VERTEX_SHADER, vertexFile );
	this->_fragmentShader = this->makeShader( GL_FRAGMENT_SHADER, fragmentFile );

	this->linkShaders();
}

Shader::~Shader( void )
{
	glDetachShader( this->_program, this->_vertexShader );
	glDetachShader( this->_program, this->_fragmentShader );

	glDeleteShader( this->_vertexShader );
	glDeleteShader( this->_fragmentShader );

	glDeleteProgram( this->_program );
	return ;
}

GLuint		Shader::makeShader( GLenum type, const std::string & text )
{
	GLuint			shader = 0u;
	GLint			shader_ok;
	const GLchar *	c_text;
	GLsizei			log_length;
	char			info_log[8192];

	shader = glCreateShader( type );
	if ( shader != 0 )
	{
		c_text = text.c_str();
		glShaderSource( shader, 1, &c_text, NULL );
		glCompileShader( shader );
		glGetShaderiv( shader, GL_COMPILE_STATUS, &shader_ok );
		if ( shader_ok != GL_TRUE )
		{
			std::stringstream ss;
			ss << "Failed to compile " << ( ( type == GL_FRAGMENT_SHADER ) ? "fragment" : "vertex" ) << " shader. Logs: " << std::endl;
			glGetShaderInfoLog( shader, 8192, &log_length,info_log );
			ss << info_log;
			Logger::e( ss.str() );
			glDeleteShader( shader );
			shader = 0;
		}
	}
	else
		Logger::e( "Failed to create shader" );
	return ( shader );
}

void		Shader::linkShaders( void )
{
	GLint	program_ok;
	GLsizei	log_length;
	char 	info_log[8192];

	glAttachShader( this->_program, this->_vertexShader );
	glAttachShader( this->_program, this->_fragmentShader );
	glLinkProgram( this->_program );
	glGetProgramiv( this->_program, GL_LINK_STATUS, &program_ok );

	if ( program_ok != GL_TRUE )
	{
		std::stringstream ss;
		ss << "Failed to link shader program" << std::endl;
		glGetProgramInfoLog( this->_program, 8192, &log_length, info_log );
		ss << info_log;
		Logger::e( ss.str() );
	}
}

const std::string		Shader::loadShader( const std::string & file )
{
	std::string					line;
	std::ifstream				fileStream( file );
	std::string					result;
	std::vector<std::string>	tokenLine;

	Logger::d( "Load shader: " + file );
	if ( fileStream.is_open() )
	{
		while ( getline( fileStream, line ) )
		{
			line = line.substr( 0, line.find( "//" ) );
			tokenLine.clear();
			if ( Utils::split( line, tokenLine ).size() == 0 )
				continue ;
			if ( tokenLine[0] == "uniform" )
			{
				std::string type = tokenLine[1];
				std::string name = tokenLine[2].substr( 0, tokenLine[2].find_last_not_of( ';' ) + 1 );
				Logger::d( "Add uniform '" + name + "' to shader: " + file );
				this->_uniforms.push_back( new Uniform( this->_program, Uniform::stringToTypeEnum( type ), name ) );
			}
			result.append( line + "\n" );
		}
		fileStream.close();
	}
	else
		Logger::e( "Unable to open file: " + file );
	return ( result );
}

void Shader::bind( void ) const
{
	if ( this->_program != 0u )
		glUseProgram( this->_program );
	else
		Logger::e( "Unable to bind program shader" );
}

void Shader::updateUniforms( RenderEngine const & renderEngine, Transformf const & transform, Camera const & camera ) const
{
	std::vector<Uniform *>::const_iterator it;

	for ( it = this->_uniforms.begin(); it != this->_uniforms.end(); it++ )
	{
		Uniform *uniform = *it;
		if ( uniform->getName() == "model" )
			glUniformMatrix4fv( uniform->getLocation(), 1, GL_FALSE, transform.getTransformedMatrix().getValues() );
		else if ( uniform->getName() == "view" )
			glUniformMatrix4fv( uniform->getLocation(), 1, GL_FALSE, camera.getTransformedViewMatrix().getValues() );
		else if ( uniform->getName() == "projection" )
			glUniformMatrix4fv( uniform->getLocation(), 1, GL_FALSE, camera.getPerspectiveMatrix().getValues() );
	}
}
