#include "SoundComponent.hpp"

SoundComponent::SoundComponent( void )
{
	generateBuffers();
}

SoundComponent::SoundComponent( Asset<Sound> const & sound ) :
	_sound( sound )
{
	generateBuffers();
	alSourcei( this->_source, AL_BUFFER, this->_sound->getBufferId() );
}

void		SoundComponent::generateBuffers( void )
{
	alGenSources( 1, &this->_source );
	alSourcef( this->_source, AL_PITCH, 1 );
	alSourcef( this->_source, AL_GAIN, 1 );
	alSource3f( this->_source, AL_POSITION, 0, 0, 0 );
	alSource3f( this->_source, AL_VELOCITY, 0, 0, 0 );
	alSourcei( this->_source, AL_LOOPING, AL_FALSE );
}

SoundComponent::~SoundComponent( void )
{
	alDeleteSources( 1, &this->_source );
}

void	SoundComponent::update( double delta )
{
	if ( this->_onEventCallback )
	{
		this->_onEventCallback( Event::FRAME_UPDATE, * this );
		if ( getState() == AL_BUFFERS_PROCESSED )
			this->_onEventCallback( Event::END, * this );
	}
}

void	SoundComponent::play( bool looping ) const
{
	alSourcei( this->_source, AL_LOOPING, looping );
	alSourcePlay( this->_source );
	if ( this->_onEventCallback )
		this->_onEventCallback( Event::PLAY, * this );
}

void	SoundComponent::pause( void ) const
{
	alSourcePause( this->_source );
	if ( this->_onEventCallback )
		this->_onEventCallback( Event::PAUSE, * this );
}

void	SoundComponent::stop( void ) const
{
	alSourceStop( this->_source );
	if ( this->_onEventCallback )
		this->_onEventCallback( Event::STOP, * this );
}

// SETTER
void	SoundComponent::setPosition( Vec3f const & pos )
{
	alSource3f( this->_source, AL_POSITION, pos.getX(), pos.getY(), pos.getZ() );
}

void	SoundComponent::setSound( Asset<Sound> const & sound )
{
	this->_sound = sound;
	alSourcei( this->_source, AL_BUFFER, this->_sound->getBufferId() );
}

void	SoundComponent::setPitch( float pitch )
{
	alSourcef( this->_source, AL_PITCH, pitch );
}

void	SoundComponent::setGain( float gain )
{
	alSourcef( this->_source, AL_GAIN, gain );
}

void	SoundComponent::setLooping( bool looping )
{
	alSourcei( this->_source, AL_LOOPING, looping );
}

void	SoundComponent::setEventCallback( t_event_callback onEventCallback )
{
	this->_onEventCallback = onEventCallback;
}

// GETTER
ALenum			SoundComponent::getState( void ) const
{
	ALenum	state;
	alGetSourcei( this->_source, AL_SOURCE_STATE, &state );
	return ( state );
}

ALfloat			SoundComponent::getTimePlayed( void ) const
{
	ALint byteOffset;

	alGetSourcei( this->_source, AL_BYTE_OFFSET, &byteOffset );
	return ( (float)byteOffset / (float)this->_sound->getFreq() );
}

float			SoundComponent::getPitch( void ) const
{
	ALfloat pitch;
	alGetSourcef( this->_source, AL_PITCH, &pitch );
	return ( pitch );
}

float			SoundComponent::getGain( void ) const
{
	ALfloat gain;
	alGetSourcef( this->_source, AL_GAIN, &gain );
	return ( gain );
}

bool			SoundComponent::isLooping( void ) const
{
	ALint looping = 0;
	alGetSourcei( this->_source, AL_LOOPING, &looping );
	return ( looping == 1 );
}

Asset<Sound> const & SoundComponent::getSound( void ) const
{
	return ( this->_sound );
}