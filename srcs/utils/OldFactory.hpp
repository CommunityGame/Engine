#ifndef _FACTORY_H_
# define _FACTORY_H_

#include <string>
#include <map>

class OldFactory
{
public:
	typedef void *					(*instantiateFunction)( void * params );

	static void						registerClass( std::string const & className, OldFactory::instantiateFunction function );
	static void *					instantiate( std::string const & name, void * params = nullptr );

private:
	static std::map<std::string, instantiateFunction>	_instantiateMap;
};

#endif // ! _FACTORY_H_