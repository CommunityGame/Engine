#include <dirent.h>
#include <string.h>
#include "ModulesFactory.hpp"
#include "LuaGameObject.hpp"

const std::string	ModulesFactory::TAG = "ModulesFactory";

void ModulesFactory::loadModules( std::string const & path )
{
	DIR				*dp;
	struct dirent	*dirp;

	if ( ( dp = opendir( path.c_str() ) ) == NULL )
	{
		std::stringstream ss;
		ss << "Failed to open modules path: " << path << ", errno: " << strerror( errno );
		Logger::e( TAG, ss.str() );
		return ;
	}

	// TODO: don't forget Py_Finalize()

	while ( ( dirp = readdir( dp ) ) != NULL )
	{
		if ( dirp->d_name[0] == '.' )
			continue ;
		std::stringstream ss;
		ss << "Load module: " << dirp->d_name;
		Logger::i( TAG, ss.str() );
		Module *	module = new Module( path + "/" + dirp->d_name );
		if ( module->isValid() )
			this->_modules.push_back( module );
	}
	closedir( dp );
}

void ModulesFactory::initModules( GameObject * root )
{
	std::vector<Module *>::iterator	it;

	for ( it = this->_modules.begin(); it != this->_modules.end(); it++ )
	{
//		Luna<LuaGameObject>::Register( (*it)->getLuaScript()->getLuaState() );
//		(*it)->init( root );
	}
}

void ModulesFactory::updateModules( double delta )
{
	std::vector<Module *>::iterator	it;

	for ( it = this->_modules.begin(); it != this->_modules.end(); it++ )
	{
//		Luna<LuaGameObject>::Register( (*it)->getLuaScript()->getLuaState() );
//		(*it)->update( delta );
	}
}

std::vector<Module *>	ModulesFactory::getModules( void ) const
{
	return ( this->_modules );
}
