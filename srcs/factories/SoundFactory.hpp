#ifndef _SOUND_FACTORY_HPP_
#define _SOUND_FACTORY_HPP_

#include <string>
#include "IFactory.hpp"
#include "../sound/Sound.hpp"

class SoundFactory : public IFactory
{
public:
	static shared_ptr<Sound>	loadWave( std::string const & file );

private:
	static const std::string	TAG;
};

#endif // ! _SOUND_FACTORY_HPP_
