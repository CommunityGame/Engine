#include "Factory.hpp"

std::map<std::string, Factory::instantiateFunction>	Factory::_instantiateMap;

void		Factory::registerClass( std::string const & className, Factory::instantiateFunction function )
{
	Factory::_instantiateMap.insert( std::pair<std::string, Factory::instantiateFunction>( className, function ) );
}

void *		Factory::instantiate( std::string const & name, void * params )
{
	std::map<std::string, Factory::instantiateFunction>::iterator	it;

	it = Factory::_instantiateMap.find( name );
	if( it != Factory::_instantiateMap.end() )
		return ( it->second( params ) );
	return ( nullptr );
}