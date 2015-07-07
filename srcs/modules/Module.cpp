#include <dirent.h>
#include <string.h>
#include "Module.hpp"
#include "../debugs/Logger.hpp"
#include <yaml-cpp/yaml.h>

Module::Module( lua_State * L, std::string const & path ) :
		_L( L ),
		_isValid( false )
{
	DIR				*dp;
	struct dirent	*dirp;

	if ( ( dp = opendir( path.c_str() ) ) == NULL )
	{
		std::stringstream ss;
		ss << "Failed to open module path: " << path << ", errno: " << strerror( errno );
		Logger::e( ss.str() );
		return ;
	}
	// TODO: check file or dir
	// TODO: load config.yml
	// TODO: create luaLib instance
	while ( ( dirp = readdir( dp ) ) != NULL )
	{
		std::string filename( dirp->d_name );
		if ( dirp->d_name[0] == '.' )
		{
			continue ;
		}
		else if ( filename == "config.yml" )
		{
			YAML::Node config = YAML::LoadFile( path + "/config.yml" );
			if ( config["version"] )
				std::cout << "POK: " << config["version"] << std::endl; // TODO: do it <<-----
		}
		std::stringstream ss;
		ss << "Load file: " << dirp->d_name;
		Logger::i( ss.str() );
	}
	closedir( dp );
	this->_isValid = true;
}

bool	Module::isValid( void ) const
{
	return ( this->_isValid );
}
