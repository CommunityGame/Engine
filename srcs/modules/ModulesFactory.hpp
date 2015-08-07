#ifndef _MODULES_FACTORY_H_
# define _MODULES_FACTORY_H_

#include <string>
#include <vector>
#include "Module.hpp"
#include "../GameObject.hpp"

class ModulesFactory
{
public:
	void					loadModules( std::string const & path );

	void					initModules( shared_ptr<GameObject> root );
	void					updateModules( double delta );
	void					inputModules( Input const & input );

	std::vector<Module *>	getModules( void ) const;

private:
	std::vector<Module *>	_modules;

	static const std::string	TAG;
};

#endif // ! _MODULES_FACTORY_H_
