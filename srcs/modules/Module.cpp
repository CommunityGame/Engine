#include <dirent.h>
#include "Module.hpp"

const std::string	Module::TAG = "Module";

Module::Module( void )
{
	return ;
}

Module *	Module::load( std::string const & path, std::string const & name )
{
	using namespace boost::python;
	Module * res = nullptr;

	Logger::i( TAG, "Load module: " + name );

	try
	{
		object main = import( "__main__" );
		dict global( main.attr( "__dict__" ) );

		std::string _path;
		_path += "import sys\n";
		_path += "sys.path.append('";
		_path += path + "/" + name;
		_path += "')\n";
		exec( _path.c_str(), global, global );

		object module = import( name.c_str() );

		if ( module.is_none() )
			throw new EngineException( "Unable to t_loader module: " + name );

		object PyModule = module.attr( name.c_str() );
		object instance = PyModule();

		res = extract<Module *>( instance );
		res->setPyModule( PyModule );
		res->setInstance( instance );
	}
	catch( const error_already_set & e )
	{
		PyErr_Print();
	}
	return ( res );
}

void	Module::addObject( GameObject * object )
{
//	std::cout << "pok: " << rootObject << std::endl;
//	rootObject->addChild( object );

}

//	DIR				*dp;
//	struct dirent	*dirp;
//	std::map<std::string, struct dirent *>	dirs;
//
//	if ( ( dp = opendir( path.c_str() ) ) == NULL )
//	{
//		std::stringstream ss;
//		ss << "Failed to open module path: " << path << ", errno: " << strerror( errno );
//		Logger::e( TAG, ss.str() );
//		return ;
//	}
//	// TODO: check file or dir
//	// TODO: t_loader config.yml
//	// TODO: create luaLib instance
//	while ( ( dirp = readdir( dp ) ) != NULL )
//	{
//		if ( dirp->d_name[0] == '.' )
//			continue ;
//		dirs[dirp->d_name] = dirp;
//	}
//	if ( ! dirs["config.yml"] )
//	{
//		Logger::e( TAG, "Failed to t_loader module " + path + ", file not found 'config.yml' !" );
//		return ;
//	}
//	if ( ! dirs["main.lua"] )
//	{
//		Logger::e( TAG, "Failed to t_loader module " + path + ", file not found 'main.lua' !" );
//		return ;
//	}
//
////	this->_luaScript = new LuaScript( path + "/main.lua" );
//
//	YAML::Node config = YAML::LoadFile( path + "/config.yml" );
//	this->_name = config["name"] ? config["name"].as<std::string>() : "Unamed";
//	this->_version = config["version"] ? config["version"].as<std::string>() : "No version";
//	this->_author = config["author"] ? config["author"].as<std::string>() : "Anonymous";
//	closedir( dp );
//
//	Logger::i( TAG, "Module " + this->_name + "(" + this->_version + ") by " + this->_author + " have been loaded" );
//	this->_isValid = true;

// SETTER

void			Module::setPyModule( boost::python::object PyModule )
{
	this->_PyModule = PyModule;
}

void			Module::setInstance( boost::python::object instance )
{
	this->_instance = instance;
}

// GETTER
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
