#ifndef _SOUND_COMPONENT_HPP_
# define _SOUND_COMPONENT_HPP_

#include <alc.h>
#include <al.h>
#include "../math/Math.hpp"
#include "../assets/IAsset.hpp"

class Sound : public IAsset
{
public:
	Sound( void );
	Sound( ALenum format, ALvoid const * data, ALsizei size, ALsizei freq );
	~Sound( void );

	void			bufferData( void ) const;

	// GETTER
	ALuint			getBufferId( void ) const;
	ALenum			getFormat( void ) const;
	ALsizei			getSize( void ) const;
	ALsizei			getFreq( void ) const;

private:
	ALuint			_buffer;

	ALvoid const *	_data;
	ALenum			_format;
	ALsizei			_size;
	ALsizei			_freq;
};

#endif // ! _SOUND_COMPONENT_HPP_
