#include <dirent.h>
#include <string.h>
#include "ModulesFactory.hpp"

const std::string	ModulesFactory::TAG = "ModulesFactory";

void ModulesFactory::loadModules( std::string const & path )
{
	using namespace boost::python;

	DIR				*dp;
	struct dirent	*dirp;

	if ( ( dp = opendir( path.c_str() ) ) == NULL )
	{
		Logger::e( TAG, "Failed to open modules path: " + path + ", errno: " + strerror( errno ) );
		return ;
	}

	try
	{
		Py_Initialize();
	}
	catch( const error_already_set & e )
	{
		PyErr_Print();
	}

	dict global( import( "__main__" ).attr( "__dict__" ) );
	std::string _path;
	_path += "import sys\n";
	_path += "sys.path.append('./libs/py_module/')\n";
	exec( _path.c_str(), global, global );

	while ( ( dirp = readdir( dp ) ) != NULL )
	{
		if ( dirp->d_name[0] == '.' || std::string( dirp->d_name ) == "py_module" )
			continue ;
		Module *	module = Module::load( path, dirp->d_name );
//		if ( module->isValid() )
			this->_modules.push_back( module );
	}
	closedir( dp );
}

void ModulesFactory::initModules( shared_ptr<GameObject> root )
{
	std::vector<Module *>::iterator	it;

	for ( it = this->_modules.begin(); it != this->_modules.end(); it++ )
	{
		try
		{
			(*it)->init( root );
		}
		catch( const boost::python::error_already_set & e )
		{
			PyErr_Print();
		}
	}
}

void ModulesFactory::updateModules( double delta )
{
	std::vector<Module *>::iterator	it;

	for ( it = this->_modules.begin(); it != this->_modules.end(); it++ )
	{
		try
		{
			(*it)->update( delta );
		}
		catch( const boost::python::error_already_set & e )
		{
			PyErr_Print();
		}
	}
}

void ModulesFactory::inputModules( Input const & input )
{
	std::vector<Module *>::iterator	it;

	for ( it = this->_modules.begin(); it != this->_modules.end(); it++ )
	{
		try
		{
			(*it)->input( input );
		}
		catch( const boost::python::error_already_set & e )
		{
			PyErr_Print();
		}
	}
}

std::vector<Module *>	ModulesFactory::getModules( void ) const
{
	return ( this->_modules );
}

void ModulesFactory::unloadModules( void )
{
	Py_Finalize();
}
