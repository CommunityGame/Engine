#include "SoundSource.hpp"

SoundSource::SoundSource( void )
{
	generateBuffers();
}

SoundSource::SoundSource( GameObject const & object )
{
	generateBuffers();
}

void		SoundSource::generateBuffers( void )
{
	alGenSources( 1, &this->_source );
	alSourcef( this->_source, AL_PITCH, 1 );
	alSourcef( this->_source, AL_GAIN, 1 );
	alSource3f( this->_source, AL_POSITION, 0, 0, 0 );
	alSource3f( this->_source, AL_VELOCITY, 0, 0, 0 );
	alSourcei( this->_source, AL_LOOPING, AL_FALSE );
}

SoundSource::~SoundSource( void )
{
	alDeleteSources( 1, &this->_source );
}

void	SoundSource::update( double delta )
{
	if ( this->_onEventCallback )
	{
		this->_onEventCallback( Event::FRAME_UPDATE, * this );
		if ( getState() == AL_BUFFERS_PROCESSED )
			this->_onEventCallback( Event::END, * this );
	}
}

void	SoundSource::play( bool looping ) const
{
	alSourcei( this->_source, AL_LOOPING, looping );
	alSourcePlay( this->_source );
	if ( this->_onEventCallback )
		this->_onEventCallback( Event::PLAY, * this );
}

void	SoundSource::pause( void ) const
{
	alSourcePause( this->_source );
	if ( this->_onEventCallback )
		this->_onEventCallback( Event::PAUSE, * this );
}

void	SoundSource::stop( void ) const
{
	alSourceStop( this->_source );
	if ( this->_onEventCallback )
		this->_onEventCallback( Event::STOP, * this );
}

// SETTER
void	SoundSource::setPosition( Vec3f const & pos )
{
	alSource3f( this->_source, AL_POSITION, pos.getX(), pos.getY(), pos.getZ() );
}

void	SoundSource::setSound( shared_ptr<Sound> const & sound )
{
	this->_sound = sound;
	alSourcei( this->_source, AL_BUFFER, this->_sound->getBufferId() );
}

void	SoundSource::setPitch( float pitch )
{
	alSourcef( this->_source, AL_PITCH, pitch );
}

void	SoundSource::setGain( float gain )
{
	alSourcef( this->_source, AL_GAIN, gain );
}

void	SoundSource::setLooping( bool looping )
{
	alSourcei( this->_source, AL_LOOPING, looping );
}

void	SoundSource::setEventCallback( t_event_callback onEventCallback )
{
	this->_onEventCallback = onEventCallback;
}

// GETTER
ALenum	SoundSource::getState( void ) const
{
	ALenum	state;
	alGetSourcei( this->_source, AL_SOURCE_STATE, &state );
	return ( state );
}

ALfloat SoundSource::getTimePlayed( void ) const
{
	ALint byteOffset;

	alGetSourcei( this->_source, AL_BYTE_OFFSET, &byteOffset );
	return ( (float)byteOffset / (float)this->_sound->getFreq() );
}

float	SoundSource::getPitch( void ) const
{
	ALfloat pitch;
	alGetSourcef( this->_source, AL_PITCH, &pitch );
	return ( pitch );
}

float	SoundSource::getGain( void ) const
{
	ALfloat gain;
	alGetSourcef( this->_source, AL_GAIN, &gain );
	return ( gain );
}

bool	SoundSource::isLooping( void ) const
{
	ALint looping = 0;
	alGetSourcei( this->_source, AL_LOOPING, &looping );
	return ( looping == 1 );
}

shared_ptr<Sound> const & SoundSource::getSound( void ) const
{
	return ( this->_sound );
}