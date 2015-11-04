#include "Shader.hpp"
#include "../utils/Utils.hpp"
#include "RenderEngine.hpp"
#include "../components/Camera.hpp"

const std::string	Shader::TAG = "Shader";

Shader::Shader( void ) :
	_program( glCreateProgram() )
{
	if ( this->_program == 0u )
	{
		Logger::e( TAG, "Failed to create program shader" );
		return ;
	}
}

Shader::~Shader( void )
{
	std::vector<GLuint>::iterator it;

	for ( it = this->_shaders.begin(); it != this->_shaders.end(); it++ )
	{
		glDetachShader( this->_program, *it );
		glDeleteShader( *it );
	}

	glDeleteProgram( this->_program );
	return ;
}

bool		Shader::addShaderFile( std::string const & file, GLenum type )
{
	const std::string shaderText = this->loadShader( file );

	this->parseUniforms( shaderText );
	GLuint shader = this->makeShader( type, shaderText );

	if ( ! shader )
		return ( false );
	this->_shaders.push_back( shader );
	return ( true );
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

bool	Shader::linkShaders( void )
{
	GLint	program_ok;
	GLsizei	log_length;
	char 	info_log[8192];
	std::vector<GLuint>::iterator it;

	for ( it = this->_shaders.begin(); it != this->_shaders.end(); it++ )
		glAttachShader( this->_program, *it );

	glLinkProgram( this->_program );
	glGetProgramiv( this->_program, GL_LINK_STATUS, &program_ok );

	if ( program_ok != GL_TRUE )
	{
		std::stringstream ss;
		ss << "Failed to link shader program" << std::endl;
		glGetProgramInfoLog( this->_program, 8192, &log_length, info_log );
		ss << info_log;
		Logger::e( TAG, ss.str() );
		return ( false );
	}
	return ( true );
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
			if ( tokenLine[0] == "#include" )
			{
				std::string includeFile = file.substr( 0, file.find_last_of( '/' ) + 1 ) + tokenLine[1];
				Logger::d( TAG, "Include shader: " + includeFile );
				result.append( loadShader( includeFile ) );
				line = "";
			}
			result.append( line + "\n" );
		}
		fileStream.close();
		Logger::i( TAG, "Loaded shader: " + file );
	}
	else
		Logger::e( TAG, "Unable to open file: " + file );
	return ( result );
}

void		Shader::parseUniforms( const std::string & text )
{
	std::map<std::string, std::map<std::string, std::string>> structsAttrs;
	std::map<std::string, std::map<std::string, std::string>>::iterator it;
	std::map<std::string, std::string>::iterator it2;
	size_t begin = 0;
	size_t end;
	size_t begin2;
	size_t end2;
	std::vector<std::string>	tmp;
	std::vector<std::string>	tmp2;

	//Parse structs
	while( ( begin = text.find( "struct", begin ) ) != std::string::npos )
	{
		end = text.find( "{", begin );
		tmp.clear();
		Utils::split( text.substr( begin, end - begin ), tmp );

		structsAttrs[tmp[1]] = std::map<std::string, std::string>();

		begin = text.find( "{", end ) + 1;
		end = text.find( "}", begin );

		std::string structData = text.substr( begin, end - begin );

		begin2 = 0;
		end2 = structData.find( ";", begin2 );
		Utils::split( structData.substr( begin2, end2 - begin2 ), tmp2 );
		while ( tmp2.size() >= 2 )
		{
			std::string attrType = tmp2[0];
			std::string attrName = tmp2[1];
			structsAttrs[tmp[1]][attrName] = attrType;
			begin2 = end2 + 1;
			end2 = structData.find( ";", begin2 );
			tmp2.clear();
			Utils::split( structData.substr( begin2, end2 - begin2 ), tmp2 );
		}
		tmp2.clear();
		begin = end;
	}

	begin = 0;
	//Parse uniform
	while( ( begin = text.find( "uniform", begin ) ) != std::string::npos )
	{
		end = text.find( ";", begin );
		std::string uniformDef = text.substr( begin, end - begin );

		tmp.clear();
		Utils::split( uniformDef, tmp );
		std::string uniformType = tmp[1];
		std::string uniformName = tmp[2];

		size_t pos = uniformName.find( '[' );
		int uniformArray = pos != std::string::npos ? atoi( uniformName.substr( pos + 1, uniformName.find( ']' ) - pos - 1 ).c_str() ) : 1;

		if ( pos != std::string::npos )
			uniformName = uniformName.substr( 0, pos );

		std::vector<Uniform *> *	uniforms;
		uniforms = ( uniformName.substr( 0, 2 ) == "C_" ) ? & this->_constUniforms : & this->_uniforms;

		for ( size_t i = 0; i < uniformArray || pos == std::string::npos; i++ )
		{
			std::string name = ( pos != std::string::npos ) ? uniformName + "[" + std::to_string( i ) + "]" : uniformName;
			if ( ( it = structsAttrs.find( uniformType ) ) != structsAttrs.end() )
			{
				it2 = (*it).second.begin();
				for ( it2; it2 != (*it).second.end(); it2++ )
					uniforms->push_back( new Uniform( this->_program, Uniform::stringToTypeEnum((*it2).second ), name + "." + (*it2).first ) );
			}
			else
				uniforms->push_back( new Uniform( this->_program, Uniform::stringToTypeEnum( uniformType ), name ) );
			pos = 0;
		}
		begin = end;
	}
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
		Uniform *	uniform = *it;
		if ( uniform->getName() == "model" )
			uniform->update( transform.getTransformedMatrix() );
//		else if ( uniform->getName() == "view" )
//			uniform->update( camera.getTransformedViewMatrix() );
//		else if ( uniform->getName() == "projection" )
//			uniform->update( camera.getPerspectiveMatrix() );

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
	}
}

// GETTER

MappedValues &		Shader::getUniformValues( void )
{
	return ( this->_uniformValues );
}

Uniform const *		Shader::getUniform( std::string const & name ) const
{
	std::vector<Uniform *>::const_iterator it;

	for ( it = this->_uniforms.begin(); it != this->_uniforms.end(); it++ )
	{
		if ( (*it)->getName() == name )
			return ( (*it) );
	}
	return ( nullptr );
}

Uniform const *		Shader::getConstUniform( std::string const & name ) const
{
	std::vector<Uniform *>::const_iterator it;

	for ( it = this->_constUniforms.begin(); it != this->_constUniforms.end(); it++ )
	{
		if ( (*it)->getName() == name )
			return ( (*it) );
	}
	return ( nullptr );
}

GLuint				Shader::getProgram( void ) const
{
	return ( this->_program );
}
