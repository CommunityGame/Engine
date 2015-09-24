#include "SoundFactory.hpp"
#include "../sound/Formats.hpp"

const std::string	SoundFactory::TAG = "SoundFactory";

shared_ptr<Sound> SoundFactory::loadWave( std::string const & file )
{
	std::ifstream		ifs( file, std::ios::in | std::ios::binary );
	Sound *	sound;
	ALenum				format;
	char *				data;

	if ( ! ifs.is_open() )
	{
		Logger::e( TAG, "Can't open: " + file );
		return ( nullptr );
	}
	Logger::d( TAG, "Load wave file: " + file );

	t_wave_format *	header = new t_wave_format;
	ifs.read( (char *)header, sizeof( t_wave_format ) );

	char * f = header->chunk_id;
	if ( f[0] != 'R' || f[1] != 'I' || f[2] != 'F' || f[3] != 'F' )
	{
		Logger::e( TAG, "Invalid format" );
		return ( nullptr );
	}

	data = new char[header->subchunk2_size];
	ifs.read( data, header->subchunk2_size );

	Logger::i( TAG, "Loaded wave file: " + file );

//	std::cout << "chunk_id: " << header->chunk_id << std::endl;
//	std::cout << "chunk_size: " << header->chunk_size << std::endl;
//	std::cout << "format: " << header->format << std::endl;
//	std::cout << "subchunk1_id: " << header->subchunk1_id << std::endl;
//	std::cout << "subchunk1_size: " << header->subchunk1_size << std::endl;
//	std::cout << "audio_format: " << header->audio_format << std::endl;
//	std::cout << "num_channels: " << header->num_channels << std::endl;
//	std::cout << "sample_rate: " << header->sample_rate << std::endl;
//	std::cout << "byte_rate: " << header->byte_rate << std::endl;
//	std::cout << "block_align: " << header->block_align << std::endl;
//	std::cout << "bits_per_sample: " << header->bits_per_sample << std::endl;
//	std::cout << "subchunk2_id: " << header->subchunk2_id << std::endl;
//	std::cout << "subchunk2_size: " << header->subchunk2_size << std::endl;

	format = header->num_channels == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
	format += header->bits_per_sample == 16 ? 1 : 0;

	sound = new Sound( format, data, header->subchunk2_size, header->sample_rate );
	sound->bufferData();
	return shared_ptr<Sound>( sound );
}
