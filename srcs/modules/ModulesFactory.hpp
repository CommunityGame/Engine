#ifndef _MODULES_FACTORY_H_
# define _MODULES_FACTORY_H_

#include <string>
#include <vector>
#include "Module.hpp"

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

class ModulesFactory
{
public:
	void loadModules( std::string const & path );

private:
	std::vector<Module>		_modules;
	lua_State *				_L;
};

#endif // ! _MODULES_FACTORY_H_
