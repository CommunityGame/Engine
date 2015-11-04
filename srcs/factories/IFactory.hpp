#ifndef _I_FACTORY_H_
# define _I_FACTORY_H_

#include "../assets/IAsset.hpp"
# include <boost/shared_ptr.hpp>

using namespace boost;

typedef std::function<shared_ptr<IAsset> (std::string const &)> t_loader;

class IFactory
{
public:
	virtual t_loader			getLoader( void ) const = 0;
};

#endif // ! _I_FACTORY_H_
