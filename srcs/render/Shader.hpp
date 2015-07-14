#ifndef _SHADER_H_
# define _SHADER_H_

#include <string>
#include <vector>
#include "Uniform.hpp"
#include "RenderEngine.hpp"
#include "../utils/MappedValues.hpp"

class Shader
{
public:
	Shader( const std::string & name );
	~Shader( void );

	void				bind( void ) const;
	void				updateUniforms( RenderEngine const & renderEngine, Transformf const & transform, Camera const & camera ) const;

	MappedValues &		getUniformValues( void );
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

	/*!
	 * @function makeShader
	 * Creates a shader object of the specified type using the specified text
	 *
	 * @param type		The type of the shader
	 * @param text		The text of the shader
	 * @result GLuint
	 */
	static GLuint		makeShader( GLenum type, const std::string & text );

	void				linkShaders( void );

	GLuint					_program;
	GLuint					_vertexShader;
	GLuint					_fragmentShader;
	std::vector<Uniform *>	_uniforms;
	MappedValues			_uniformValues;

	static const std::string	TAG;
};

#endif // ! _SHADER_H_
