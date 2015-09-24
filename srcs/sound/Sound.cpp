#include "Sound.hpp"

Sound::Sound( void )
{
	alGenBuffers( 1, &this->_buffer );
}

Sound::Sound( ALenum format, ALvoid const * data, ALsizei size, ALsizei freq ) :
	_format( format ),
	_data( data ),
	_size( size ),
	_freq( freq )
{
	alGenBuffers( 1, &this->_buffer );
}

Sound::~Sound( void )
{
	alDeleteBuffers( 1, &this->_buffer );
}

void	Sound::bufferData( void ) const
{
	alBufferData( this->_buffer, this->_format, this->_data, this->_size, this->_freq );
	return ;
}

// GETTER
ALuint	Sound::getBufferId( void ) const
{
	return ( this->_buffer );
}

ALenum	Sound::getFormat( void ) const
{
	return ( this->_format );
}

ALsizei	Sound::getSize( void ) const
{
	return ( this->_size );
}

ALsizei	Sound::getFreq( void ) const
{
	return ( this->_freq );
}

