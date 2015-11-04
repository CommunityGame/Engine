#include "OldFactory.hpp"

//TODO: remove all this class
std::map<std::string, OldFactory::instantiateFunction>	OldFactory::_instantiateMap;

void		OldFactory::registerClass( std::string const & className, OldFactory::instantiateFunction function )
{
	OldFactory::_instantiateMap.insert( std::pair<std::string, OldFactory::instantiateFunction>( className, function ) );
}

void * OldFactory::instantiate( std::string const & name, void * params )
{
	std::map<std::string, OldFactory::instantiateFunction>::iterator	it;

	it = OldFactory::_instantiateMap.find( name );
	if( it != OldFactory::_instantiateMap.end() )
		return ( it->second( params ) );
	return ( nullptr );
}