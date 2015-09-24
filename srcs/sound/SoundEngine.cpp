#include "SoundEngine.hpp"
#include "Sound.hpp"
#include "../GameObject.hpp"

const std::string	SoundEngine::TAG = "SoundEngine";

SoundEngine::SoundEngine( void )
{
	// open default device
	this->_device = alcOpenDevice( nullptr );
	if ( this->_device != nullptr )
	{
		// create context
		this->_context = alcCreateContext( this->_device, nullptr );
		if ( this->_context != nullptr )
		{
			// set active context
			alcMakeContextCurrent( this->_context );
		}
	}

	const ALchar *	renderer = alGetString( AL_RENDERER );
	const ALchar *	version = alGetString( AL_VERSION );

	std::stringstream ss;
	ss << "Renderer: " << renderer;
	Logger::i( TAG, ss.str() );
	ss.str( "" );
	ss << "OpenAL version supported " << version;
	Logger::i( TAG, ss.str() );
	return ;
}

SoundEngine::~SoundEngine( void )
{
	alcMakeContextCurrent( nullptr );
	alcDestroyContext( this->_context );
	alcCloseDevice( this->_device );
	this->_context = nullptr;
	this->_device = nullptr;
	return ;
}

void SoundEngine::update( double delta, GameObject const & listener ) const
{
	ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };

	Vec3f pos = listener.getTransform().getPosition();
	Vec3f forward = listener.getTransform().getRotation().getBack();
	Vec3f up = listener.getTransform().getRotation().getUp();

	listenerOri[0] = forward.getX();
	listenerOri[1] = forward.getY();
	listenerOri[2] = forward.getZ();
	listenerOri[3] = up.getX();
	listenerOri[4] = up.getY();
	listenerOri[5] = up.getZ();
	alListener3f( AL_POSITION, pos.getX(), pos.getY(), pos.getZ() );
	alListenerfv( AL_VELOCITY, listenerVel );
	alListenerfv( AL_ORIENTATION, listenerOri );
}


// GETTER
std::string		SoundEngine::getError( void )
{
	ALenum	error;

	error = alGetError();
	switch ( error )
	{
		case AL_INVALID_NAME: return "Invalid name parameter.";
		case AL_INVALID_ENUM: return "Invalid parameter.";
		case AL_INVALID_VALUE: return "Invalid parameter.";
		case AL_INVALID_OPERATION: return "Illegal call.";
		case AL_OUT_OF_MEMORY: return "Unable to allocate memory.";
		default: return "There is no current error."; //AL_NO_ERROR
	}
}
