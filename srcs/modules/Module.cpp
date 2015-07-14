#include <dirent.h>
#include <string.h>
#include "Module.hpp"
#include <yaml-cpp/yaml.h>

const std::string	Module::TAG = "Module";

Module::Module( std::string const & path ) :
	_isValid( false ),
	_path( path )
{
	DIR				*dp;
	struct dirent	*dirp;
	std::map<std::string, struct dirent *>	dirs;

	if ( ( dp = opendir( path.c_str() ) ) == NULL )
	{
		std::stringstream ss;
		ss << "Failed to open module path: " << path << ", errno: " << strerror( errno );
		Logger::e( TAG, ss.str() );
		return ;
	}
	// TODO: check file or dir
	// TODO: load config.yml
	// TODO: create luaLib instance
	while ( ( dirp = readdir( dp ) ) != NULL )
	{
		if ( dirp->d_name[0] == '.' )
			continue ;
		dirs[dirp->d_name] = dirp;
	}
	if ( ! dirs["config.yml"] )
	{
		Logger::e( TAG, "Failed to load module " + path + ", file not found 'config.yml' !" );
		return ;
	}
	if ( ! dirs["main.lua"] )
	{
		Logger::e( TAG, "Failed to load module " + path + ", file not found 'main.lua' !" );
		return ;
	}

	this->_luaScript = new LuaScript( path + "/main.lua" );

	YAML::Node config = YAML::LoadFile( path + "/config.yml" );
	this->_name = config["name"] ? config["name"].as<std::string>() : "Unamed";
	this->_version = config["version"] ? config["version"].as<std::string>() : "No version";
	this->_author = config["author"] ? config["author"].as<std::string>() : "Anonymous";
	closedir( dp );

	Logger::i( TAG, "Module " + this->_name + "(" + this->_version + ") by " + this->_author + " have been loaded" );
	this->_isValid = true;
}

void Module::init( GameObject * luaRootObject )
{
	lua_pushlightuserdata( this->_luaScript->getLuaState(), (void*)luaRootObject );
	lua_setglobal( this->_luaScript->getLuaState(),"rootGameObject" );
//	lua_pop( this->_luaScript->getLuaState(), -1 );
	lua_getglobal( this->_luaScript->getLuaState(), "init" );
	lua_call( this->_luaScript->getLuaState(), 0, 0 );
}

void Module::update( double delta )
{
	lua_getglobal( this->_luaScript->getLuaState(), "update" );
	lua_pushnumber( this->_luaScript->getLuaState(), delta );
	lua_call( this->_luaScript->getLuaState(), 1, 0 );
}

// GETTER
bool			Module::isValid( void ) const
{
	return ( this->_isValid );
}

std::string		Module::getPath( void ) const
{
	return ( this->_path );
}

std::string		Module::getName( void ) const
{
	return ( this->_name );
}

std::string		Module::getVersion( void ) const
{
	return ( this->_version );
}

std::string		Module::getAuthor( void ) const
{
	return ( this->_author );
}

LuaScript const *	Module::getLuaScript( void ) const
{
	return ( this->_luaScript );
}
