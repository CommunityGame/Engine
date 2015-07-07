#include <dirent.h>
#include <string.h>
#include "ModulesFactory.hpp"
#include "../debugs/Logger.hpp"

void ModulesFactory::loadModules( std::string const & path )
{
	DIR				*dp;
	struct dirent	*dirp;

	this->_L = lua_open();
	luaL_openlibs( this->_L );

	if ( ( dp = opendir( path.c_str() ) ) == NULL )
	{
		std::stringstream ss;
		ss << "Failed to open modules path: " << path << ", errno: " << strerror( errno );
		Logger::e( ss.str() );
		return ;
	}

	while ( ( dirp = readdir( dp ) ) != NULL )
	{
		if ( dirp->d_name[0] == '.' )
			continue ;
		std::stringstream ss;
		ss << "Load module: " << dirp->d_name;
		Logger::i( ss.str() );
		Module	module( this->_L, path + "/" + dirp->d_name );
		if ( module.isValid() )
			this->_modules.push_back( module );
	}
	closedir( dp );
}
