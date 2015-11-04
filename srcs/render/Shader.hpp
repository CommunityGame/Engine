#ifndef _SHADER_H_
# define _SHADER_H_

#include <string>
#include <vector>
#include "Uniform.hpp"
#include "../utils/MappedValues.hpp"
#include "../assets/IAsset.hpp"

class RenderEngine;
class Camera;

class Shader : public IAsset
{
public:
	Shader( void );
	~Shader( void );

	bool				addShaderFile( std::string const & file, GLenum type );
	void				bind( void ) const;
	void				unbind( void ) const;
	void				updateUniforms( RenderEngine const & renderEngine, Transformf const & transform, Camera const & camera ) const;
	bool				linkShaders( void );
	MappedValues &		getUniformValues( void );
	Uniform const *		getUniform( std::string const & name ) const;
	Uniform const *		getConstUniform( std::string const & name ) const;
	GLuint				getProgram( void ) const ;

private:
	/*!
	 * @function loadShader
	 * Read shader file and add uniform in vector list
	 *
	 * @param file		The file to read
	 * @result std::string &
	 */
	const std::string	loadShader( const std::string & file );

	void				parseUniforms( const std::string & text );

	/*!
	 * @function makeShader
	 * Creates a shader object of the specified type using the specified text
	 *
	 * @param type		The type of the shader
	 * @param text		The text of the shader
	 * @result GLuint
	 */
	static GLuint		makeShader( GLenum type, const std::string & text );

	GLuint					_program;
	std::vector<GLuint>		_shaders;

//	GLuint					_vertexShader;
//	GLuint					_fragmentShader;
	std::vector<Uniform *>	_uniforms;
	std::vector<Uniform *>	_constUniforms;
	MappedValues			_uniformValues;

	static const std::string	TAG;
};

#endif // ! _SHADER_H_
