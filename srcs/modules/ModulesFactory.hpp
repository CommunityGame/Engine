#ifndef _MODULES_FACTORY_H_
# define _MODULES_FACTORY_H_

#include <string>
#include <vector>
#include "Module.hpp"
#include "../GameObject.hpp"
#include "lua/LuaScript.hpp"

class ModulesFactory
{
public:
	void					loadModules( std::string const & path );

	void					initModules( GameObject * root );
	void					updateModules( double delta );

	std::vector<Module *>	getModules( void ) const;
//	lua_State *				getLuaState( void ) const;

private:
	std::vector<Module *>	_modules;

	static const std::string	TAG;
};

#endif // ! _MODULES_FACTORY_H_
