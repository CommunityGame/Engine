#ifndef _SOUND_FACTORY_HPP_
#define _SOUND_FACTORY_HPP_

#include <string>
#include "IFactory.hpp"
#include "../sound/Sound.hpp"

class SoundFactory : public IFactory
{
public:
	virtual t_loader			getLoader( void ) const;

private:
	static shared_ptr<Sound>	load( std::string const & path );
	static shared_ptr<Sound>	loadWave( std::string const & file );
	static const std::string	TAG;
};

#endif // ! _SOUND_FACTORY_HPP_
