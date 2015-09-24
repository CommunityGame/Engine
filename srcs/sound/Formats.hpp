#ifndef _FORMATS_HPP_
#define _FORMATS_HPP_

typedef struct	s_wave_format
{
	char		chunk_id[4];
	int			chunk_size;
	char		format[4];
	char		subchunk1_id[4];
	int			subchunk1_size;
	short int	audio_format;
	short int	num_channels;
	int			sample_rate;
	int			byte_rate;
	short int	block_align;
	short int	bits_per_sample;
	char		subchunk2_id[4];
	int			subchunk2_size;
}				t_wave_format;

#endif // ! _FORMATS_HPP_
