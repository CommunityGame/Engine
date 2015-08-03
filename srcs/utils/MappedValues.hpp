#ifndef _MAPPED_VALUES_H_
# define _MAPPED_VALUES_H_

#include <map>
#include "../math/Math.hpp"
#include "../render/LightUniform.hpp"

class MappedValues
{
public:
	void								addValue( std::string const & name, int value );
	void								addValue( std::string const & name, float value );
	void								addValue( std::string const & name, double value );
	void								addValue( std::string const & name, Vec2f const & value );
	void								addValue( std::string const & name, Vec3f const & value );
	void								addValue( std::string const & name, Mat4f const & value );
	void								addValue( std::string const & name, LightUniform const * value );

	int									getInt( std::string const & name ) const;
	float								getFloat( std::string const & name ) const;
	double								getDouble( std::string const & name ) const;
	Vec2f const &						getVec2f( std::string const & name ) const;
	Vec3f const &						getVec3f( std::string const & name ) const;
	Mat4f const &						getMat4f( std::string const & name ) const;
	LightUniform const *				getLight( std::string const & name ) const;

private:
	std::map<std::string, int>			_intValues;
	std::map<std::string, float>		_floatValues;
	std::map<std::string, double>		_doubleValues;
	std::map<std::string, Vec2f>		_vec2fValues;
	std::map<std::string, Vec3f>		_vec3fValues;
	std::map<std::string, Mat4f>		_mat4fValues;
	std::map<std::string, LightUniform const *>	_lightValues;
};

#endif // ! _MAPPED_VALUES_H_
