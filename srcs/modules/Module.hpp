#ifndef _MODULE_H_
# define _MODULE_H_

#include <string>

extern "C"
{
	#include <lua.h>
};

class Module
{
public:
	Module( lua_State * L, std::string const & path );
	bool isValid( void ) const;

private:
	bool			_isValid;
	lua_State *		_L;
};

#endif // ! _MODULE_H_
