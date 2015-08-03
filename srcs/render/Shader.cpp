#include "Shader.hpp"
#include "../components/Camera.hpp"
#include "../utils/Utils.hpp"

const std::string	Shader::TAG = "Shader";

Shader::Shader( const std::string & file ) :
	_program( glCreateProgram() )
{
	if ( this->_program == 0u )
	{
		Logger::e( TAG, "Failed to create program shader" );
		return ;
	}

	const std::string vertexFile = this->loadShader( "./resources/shaders/" + file + "_vert.glsl" );
	if ( vertexFile.empty() )
		Logger::e( TAG, "Unable to load vertex shader" );
	const std::string fragmentFile = this->loadShader( "./resources/shaders/" + file + "_frag.glsl" );
	if ( fragmentFile.empty() )
		Logger::e( TAG, "Unable to load fragment shader" );

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
	GLuint			shader;
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
			Logger::e( TAG, ss.str() );
			glDeleteShader( shader );
			shader = 0;
		}
	}
	else
		Logger::e( TAG, "Failed to create shader" );
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
		Logger::e( TAG, ss.str() );
	}
}

const std::string		Shader::loadShader( const std::string & file )
{
	std::string					line;
	std::ifstream				fileStream( file, std::ios::in );
	std::string					result;
	std::vector<std::string>	tokenLine;

	if ( fileStream.is_open() )
	{
		Logger::d( TAG, "Load shader: " + file );
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
				Logger::d( TAG, "Add uniform '" + name + "' to shader: " + file );

				// if array
				if ( name.find( '[' ) != std::string::npos )
				{
					int	nb;
					Uniform::Type t = Uniform::stringToTypeEnum( type );

					nb = atoi( name.substr( name.find( '[' ) + 1, name.length() - name.find( '[' ) - 2 ).c_str() );
					name = name.substr( 0, name.find( '[' ) );
					for ( int i = 0; i < nb; ++i )
						this->_uniforms.push_back( new Uniform( this->_program, t, name + "[" + std::to_string( i ) + "]" ) );
				}
				else
					this->_uniforms.push_back( new Uniform( this->_program, Uniform::stringToTypeEnum( type ), name ) );
			}
			else if ( tokenLine[0] == "#include" )
			{
				std::string includeFile = file.substr( 0, file.find_last_of( '/' ) + 1 ) + tokenLine[1];
				Logger::d( TAG, "Include shader: " + includeFile );
				result.append( loadShader( includeFile ) );
				line = "//" + line;
			}
			result.append( line + "\n" );
		}
		fileStream.close();
	}
	else
		Logger::e( TAG, "Unable to open file: " + file );
	return ( result );
}

void		Shader::bind( void ) const
{
	glUseProgram( this->_program );
}

void		Shader::unbind( void ) const
{
	glUseProgram( 0u );
}

void		Shader::updateUniforms( RenderEngine const & renderEngine, Transformf const & transform, Camera const & camera ) const
{
	std::vector<Uniform *>::const_iterator it;

	for ( it = this->_uniforms.begin(); it != this->_uniforms.end(); it++ )
	{
		Uniform *uniform = *it;
		if ( uniform->getName() == "model" )
			uniform->update( transform.getTransformedMatrix() );
		else if ( uniform->getName() == "view" )
			uniform->update( camera.getTransformedViewMatrix() );
		else if ( uniform->getName() == "projection" )
			uniform->update( camera.getPerspectiveMatrix() );

		else if ( uniform->getType() == Uniform::Type::INT )
			uniform->update( this->_uniformValues.getInt( uniform->getName() ) );
		else if ( uniform->getType() == Uniform::Type::FLOAT )
			uniform->update( this->_uniformValues.getFloat( uniform->getName() ) );
		else if ( uniform->getType() == Uniform::Type::DOUBLE )
			uniform->update( this->_uniformValues.getDouble( uniform->getName() ) );
		else if ( uniform->getType() == Uniform::Type::VEC2 )
			uniform->update( this->_uniformValues.getVec2f( uniform->getName() ) );
		else if ( uniform->getType() == Uniform::Type::VEC3 )
			uniform->update( this->_uniformValues.getVec3f( uniform->getName() ) );
		else if ( uniform->getType() == Uniform::Type::MAT4 )
			uniform->update( this->_uniformValues.getMat4f( uniform->getName() ) );
		else if ( uniform->getType() == Uniform::Type::LIGHT )
		{
			LightUniform const * lightUniform = this->_uniformValues.getLight( uniform->getName() );
			if ( lightUniform != nullptr )
				lightUniform->update();
		}
	}
}

// GETTER

MappedValues &		Shader::getUniformValues( void )
{
	return ( this->_uniformValues );
}

GLuint				Shader::getProgram( void ) const
{
	return ( this->_program );
}
