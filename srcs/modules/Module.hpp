#ifndef _MODULE_H_
# define _MODULE_H_

#include <string>
#include "lua/LuaScript.hpp"
#include "../GameObject.hpp"
#include <boost/python.hpp>

//extern "C"
//{
//	#include <lua.h>
//};

class Module
{
public:
	Module( void );
	Module( std::string const & path );

	virtual void	init( GameObject * rootObject );
	virtual void	update( double delta );

	// GETTER
	bool			isValid( void ) const;
	std::string		getPath( void ) const;
	std::string		getName( void ) const;
	std::string		getVersion( void ) const;
	std::string		getAuthor( void ) const;
//	LuaScript const *	getLuaScript( void ) const;

private:
	bool			_isValid;
//	LuaScript *		_luaScript;
	PyObject *		_self;
	std::string		_path;

	std::string		_name;
	std::string		_version;
	std::string		_author;

	static const std::string	TAG;
};

#endif // ! _MODULE_H_
