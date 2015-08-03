#ifndef _FACTORY_H_
# define _FACTORY_H_

#include <string>
#include <map>
#include "IFactory.hpp"

class Factory
{
public:
	typedef IFactory *				(*instantiateFunction)( void * params );

	static void						registerClass( std::string const & className, Factory::instantiateFunction function );
	static IFactory *				instantiate( std::string const & name, void * params = nullptr );

private:
	static std::map<std::string, instantiateFunction>	_instantiateMap;
};

#endif // ! _FACTORY_H_
