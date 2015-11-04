#ifndef _SOURCE_HPP_
# define _SOURCE_HPP_

#include <al.h>
#include "../GameObject.hpp"
#include "../assets/Asset.hpp"
#include "../sound/Sound.hpp"

// TODO: component
class SoundComponent
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
	typedef std::function<void(enum Event, SoundComponent const &)> t_event_callback;

	SoundComponent( void );
	SoundComponent( Asset<Sound> const & sound );
	~SoundComponent( void );

	void				update( double delta );

	void				play( bool looping = false ) const;
	void				pause( void ) const;
	void				stop( void ) const;

	// SETTER
	void				setPosition( Vec3f const & pos );
	void				setSound( Asset<Sound> const & sound );
	void				setPitch( float pitch );
	void				setGain( float gain );
	void				setLooping( bool looping );
	void				setEventCallback( t_event_callback _onEventCallback );

	// GETTER
	ALenum				getState( void ) const;
	ALfloat				getTimePlayed( void ) const;
	float				getPitch( void ) const;
	float				getGain( void ) const;
	bool				isLooping( void ) const;
	Asset<Sound> const &	getSound( void ) const;

private:
	void				generateBuffers( void );
	ALuint				_source;

	t_event_callback	_onEventCallback;
	Asset<Sound>		_sound;
};

#endif // ! _SOURCE_HPP_
