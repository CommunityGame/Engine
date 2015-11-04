#ifndef _SHADER_FACTORY_HPP_
#define _SHADER_FACTORY_HPP_

#include "IFactory.hpp"
#include "../render/Shader.hpp"

class ShaderFactory : public IFactory
{
public:
	virtual t_loader			getLoader( void ) const;

private:
	static shared_ptr<Shader>	load( std::string const & path );
	static shared_ptr<Shader>	loadGlsl( std::string const & vertFile, std::string const & fragFile );

	static const std::string	TAG;
};

#endif // ! _SHADER_FACTORY_HPP_
