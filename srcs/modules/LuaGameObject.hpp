#ifndef _LUA_GAME_OBJECT_H_
# define _LUA_GAME_OBJECT_H_

#include <lua.h>
#include "../GameObject.hpp"
#include "lua/Luna.hpp"
#include "lua/LuaScript.hpp"

class LuaGameObject
{
public:
	LuaGameObject( lua_State * L );

	int					addObject( lua_State * L );
	int					setPos( lua_State * L );
	virtual int			update( lua_State * L );

	static const char className[];
	static Luna<LuaGameObject>::RegType methods[];

	GameObject *		getReal( void ) const;

private:
	GameObject *		_real;
};

#endif // ! _LUA_GAME_OBJECT_H_
