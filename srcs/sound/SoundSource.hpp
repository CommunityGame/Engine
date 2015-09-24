#ifndef _SOURCE_HPP_
# define _SOURCE_HPP_

#include <al.h>
#include "../GameObject.hpp"
#include "Sound.hpp"


class SoundSource
{
public:
	enum Event
	{
		PLAY,
		PAUSE,
		STOP,
		FRAME_UPDATE,
		END,
		SIZE
	};
	typedef std::function<void(enum Event, SoundSource const &)> t_event_callback;

	SoundSource( void );
	SoundSource( GameObject const & object );
	~SoundSource( void );

	void			update( double delta );

	void			play( bool looping = false ) const;
	void			pause( void ) const;
	void			stop( void ) const;

	// SETTER
	void			setPosition( Vec3f const & pos );
	void			setSound( shared_ptr<Sound> const & sound );
	void			setPitch( float pitch );
	void			setGain( float gain );
	void			setLooping( bool looping );
	void			setEventCallback( t_event_callback _onEventCallback );

	// GETTER
	ALenum			getState( void ) const;
	ALfloat			getTimePlayed( void ) const;
	float			getPitch( void ) const;
	float			getGain( void ) const;
	bool			isLooping( void ) const;
	shared_ptr<Sound> const &	getSound( void ) const;

private:
	void			generateBuffers( void );
	ALuint			_source;

	t_event_callback	_onEventCallback;
	shared_ptr<Sound>	_sound;
};

#endif // ! _SOURCE_HPP_
