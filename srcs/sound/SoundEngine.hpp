#ifndef _SOUND_ENGINE_HPP_
# define _SOUND_ENGINE_HPP_

# include <string>
# include <vector>
# include <alc.h>

class GameObject;

class SoundEngine
{
public:
	SoundEngine( void );
	~SoundEngine( void );

	virtual void			update( double delta, GameObject const & listener ) const;

	std::string				getError( void );

private:
	ALCdevice *				_device;
	ALCcontext *			_context;

	static const std::string	TAG;
};

#endif // ! _SOUND_ENGINE_HPP_
