#include "ShaderFactory.hpp"

const std::string	ShaderFactory::TAG = "ShaderFactory";

t_loader			ShaderFactory::getLoader( void ) const
{
	return ( ShaderFactory::load );
}

shared_ptr<Shader>	ShaderFactory::load( std::string const & path )
{
	bool fullPath = path.find( '/' ) != std::string::npos;
	std::string vertPath;
	std::string fragPath;

	vertPath = fragPath = path;
	if ( ! fullPath )
	{
		vertPath = "./assets/shaders/" + vertPath;
		fragPath = "./assets/shaders/" + fragPath;
	}
	vertPath += "_vert.glsl";
	fragPath += "_frag.glsl";

	return ShaderFactory::loadGlsl( vertPath, fragPath );
}

shared_ptr<Shader>	ShaderFactory::loadGlsl( std::string const & vertFile, std::string const & fragFile )
{
	Shader *		shader = new Shader();

	if ( ! shader->addShaderFile( vertFile, GL_VERTEX_SHADER ) )
		Logger::e( TAG, "Unable to load shader: " + vertFile );
	if ( ! shader->addShaderFile( fragFile, GL_FRAGMENT_SHADER ) )
		Logger::e( TAG, "Unable to load shader: " + fragFile );

	shader->linkShaders();

	return ( shared_ptr<Shader>( shader ) );
}

