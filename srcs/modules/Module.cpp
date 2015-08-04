#include <dirent.h>
#include <string.h>
#include "Module.hpp"
//#include <yaml-cpp/yaml.h>

const std::string	Module::TAG = "Module";

BOOST_PYTHON_MODULE(LibModule)
{
	using namespace boost::python;

	class_<Module>( "Module", init<>() )
			.def( "update", &Module::update )
			;
}

Module::Module( void )
{
	std::cout << "ho yeah" << std::endl;
}

Module::Module( std::string const & path ) :
	_isValid( false )
{
	using namespace boost::python;

	try
	{
		// Retrieve the main module.
		object main = import( "__main__" );
		// Retrieve the main module's namespace
		dict global( main.attr( "__dict__" ) );

		std::string _path;
		_path += "import sys\n";
		_path += "sys.path.append('./resources/modules/lib_module')\n";
		_path += "sys.path.append('";
		_path += path;
		_path += "')\n";
		_path += "print(sys.path)";
		exec( _path.c_str(), global, global );

		object module = import( "main_module" );

		//	std::cout << module.is_none() << std::endl;

//		object Test = module.attr( "Test" );
//
//		object test = Test();
		object test = module.attr( "c1" );

		test.attr( "update" )( 123.0 );
	}
	catch( const error_already_set & e )
	{
		PyErr_Print();
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
//	// TODO: load config.yml
//	// TODO: create luaLib instance
//	while ( ( dirp = readdir( dp ) ) != NULL )
//	{
//		if ( dirp->d_name[0] == '.' )
//			continue ;
//		dirs[dirp->d_name] = dirp;
//	}
//	if ( ! dirs["config.yml"] )
//	{
//		Logger::e( TAG, "Failed to load module " + path + ", file not found 'config.yml' !" );
//		return ;
//	}
//	if ( ! dirs["main.lua"] )
//	{
//		Logger::e( TAG, "Failed to load module " + path + ", file not found 'main.lua' !" );
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
}

void		Module::init( GameObject * rootObject )
{
//	lua_pushlightuserdata( this->_luaScript->getLuaState(), (void*)luaRootObject );
//	lua_setglobal( this->_luaScript->getLuaState(),"rootGameObject" );
//	lua_pop( this->_luaScript->getLuaState(), -1 );
//	lua_getglobal( this->_luaScript->getLuaState(), "init" );
//	lua_call( this->_luaScript->getLuaState(), 0, 0 );
}

void		Module::update( double delta )
{
	using namespace boost::python;

	std::cout << "poky" << std::endl;
//	lua_getglobal( this->_luaScript->getLuaState(), "update" );
//	lua_pushnumber( this->_luaScript->getLuaState(), delta );
//	lua_call( this->_luaScript->getLuaState(), 1, 0 );
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

//LuaScript const *	Module::getLuaScript( void ) const
//{
//	return ( this->_luaScript );
//}
