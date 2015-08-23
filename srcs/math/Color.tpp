#ifndef _COLOR_HPP_
# define _COLOR_HPP_

#include <iostream>
#include <map>
#include "../debugs/Logger.hpp"

template <typename T = float>
class Color
{
public:
	Color()
	{
		this->_r = 0;
		this->_g = 0;
		this->_b = 0;
		this->_a = 1;
	}

	Color( const std::string & hex )
	{
		long			iVal;

		if ( hex[0] != '#' )
		{
			std::map<std::string, int>::const_iterator it = Color::HTML_COLOR_CODES.find( hex );
			iVal = it != Color::HTML_COLOR_CODES.end() ? it->second : 0;
			this->_r = (T)( ( iVal & 0xFF0000 ) >> 16 ) / T( 255 );
			this->_g = (T)( ( iVal & 0x00FF00 ) >> 8 ) / T( 255 );
			this->_b = (T)( ( iVal & 0x0000FF ) >> 0 ) / T( 255 );
			this->_a = T( 1 );
			return ;
		}
		std::string		val( hex.substr( 1 ) );
		iVal = strtol( val.c_str(), 0, 16 );
		if ( val.length() == 6 )
		{
			this->_r = (T)( ( iVal & 0xFF0000 ) >> 16 ) / T( 255 );
			this->_g = (T)( ( iVal & 0x00FF00 ) >> 8 ) / T( 255 );
			this->_b = (T)( ( iVal & 0x0000FF ) >> 0 ) / T( 255 );
			this->_a = T( 1 );
		}
		else if ( val.length() == 8 )
		{
			this->_r = (T)( ( iVal & 0xFF000000 ) >> 24 ) / T( 255 );
			this->_g = (T)( ( iVal & 0x00FF0000 ) >> 16 ) / T( 255 );
			this->_b = (T)( ( iVal & 0x0000FF00 ) >> 8 ) / T( 255 );
			this->_a = (T)( ( iVal & 0x000000FF ) ) / T( 255 );
		}
		else
		{
			Logger::e( TAG, "Invalid format, expeted: #RRGGBB or #RRGGBBAA" );
			return ;
		}
	}

	Color( int32_t color )
	{
		this->_r = (T)( ( color & 0xFF000000 ) >> 24 ) / T( 255 );
		this->_g = (T)( ( color & 0x00FF0000 ) >> 16 ) / T( 255 );
		this->_b = (T)( ( color & 0x0000FF00 ) >> 8 ) / T( 255 );
		this->_a = (T)( ( color & 0x000000FF ) ) / T( 255 );
	}

	Color( T const & r, T const & g, T const & b, T const & a )
	{
		this->_r = r;
		this->_g = g;
		this->_b = b;
		this->_a = a;
	}

	inline Color( Color const & cpy )
	{
		*this = cpy;
		return ;
	}

	inline Color<T> &	operator=( Color<T> const & rhs )
	{
		this->_r = rhs.getR();
		this->_g = rhs.getG();
		this->_b = rhs.getB();
		this->_a = rhs.getA();
		return ( *this );
	}

	inline T	getR( void ) const
	{
		return ( this->_r );
	}

	inline T	getG( void ) const
	{
		return ( this->_g );
	}

	inline T	getB( void ) const
	{
		return ( this->_b );
	}

	inline T	getA( void ) const
	{
		return ( this->_a );
	}

private:
	T		_r;
	T		_g;
	T		_b;
	T		_a;

	static const std::string	TAG;
	static const std::map<std::string, int>	HTML_COLOR_CODES;
};

template <typename T>
const std::string	Color<T>::TAG = "Color";

template <typename T>
std::ostream &		operator<<( std::ostream & o, Color<T> const & c )
{
	return ( o << "r: " << c.getR() << ", g: " << c.getG() << ", b: " << c.getB() << ", a: " << c.getA() );
}

#define RGB( r, g, b ) ( r << 16 | g << 8 | b )

// @see http://www.w3.org/TR/SVG/types.html#ColorKeywords
template <typename T>
const	std::map<std::string, int>	Color<T>::HTML_COLOR_CODES =
{
	{ "aliceblue", RGB( 240, 248, 255 ) },
	{ "antiquewhite", RGB( 250, 235, 215 ) },
	{ "aqua", RGB(  0, 255, 255 ) },
	{ "aquamarine", RGB( 127, 255, 212 ) },
	{ "azure", RGB( 240, 255, 255 ) },
	{ "beige", RGB( 245, 245, 220 ) },
	{ "bisque", RGB( 255, 228, 196 ) },
	{ "black", RGB(  0, 0, 0 ) },
	{ "blanchedalmond", RGB( 255, 235, 205 ) },
	{ "blue", RGB(  0, 0, 255 ) },
	{ "blueviolet", RGB( 138, 43, 226 ) },
	{ "brown", RGB( 165, 42, 42 ) },
	{ "burlywood", RGB( 222, 184, 135 ) },
	{ "cadetblue", RGB(  95, 158, 160 ) },
	{ "chartreuse", RGB( 127, 255, 0 ) },
	{ "chocolate", RGB( 210, 105, 30 ) },
	{ "coral", RGB( 255, 127, 80 ) },
	{ "cornflowerblue", RGB( 100, 149, 237 ) },
	{ "cornsilk", RGB( 255, 248, 220 ) },
	{ "crimson", RGB( 220, 20, 60 ) },
	{ "cyan", RGB(  0, 255, 255 ) },
	{ "darkblue", RGB(  0, 0, 139 ) },
	{ "darkcyan", RGB(  0, 139, 139 ) },
	{ "darkgoldenrod", RGB( 184, 134, 11 ) },
	{ "darkgray", RGB( 169, 169, 169 ) },
	{ "darkgreen", RGB(  0, 100, 0 ) },
	{ "darkgrey", RGB( 169, 169, 169 ) },
	{ "darkkhaki", RGB( 189, 183, 107 ) },
	{ "darkmagenta", RGB( 139, 0, 139 ) },
	{ "darkolivegreen", RGB(  85, 107, 47 ) },
	{ "darkorange", RGB( 255, 140, 0 ) },
	{ "darkorchid", RGB( 153, 50, 204 ) },
	{ "darkred", RGB( 139, 0, 0 ) },
	{ "darksalmon", RGB( 233, 150, 122 ) },
	{ "darkseagreen", RGB( 143, 188, 143 ) },
	{ "darkslateblue", RGB(  72, 61, 139 ) },
	{ "darkslategray", RGB(  47, 79, 79 ) },
	{ "darkslategrey", RGB(  47, 79, 79 ) },
	{ "darkturquoise", RGB(  0, 206, 209 ) },
	{ "darkviolet", RGB( 148, 0, 211 ) },
	{ "deeppink", RGB( 255, 20, 147 ) },
	{ "deepskyblue", RGB(  0, 191, 255 ) },
	{ "dimgray", RGB( 105, 105, 105 ) },
	{ "dimgrey", RGB( 105, 105, 105 ) },
	{ "dodgerblue", RGB(  30, 144, 255 ) },
	{ "firebrick", RGB( 178, 34, 34 ) },
	{ "floralwhite", RGB( 255, 250, 240 ) },
	{ "forestgreen", RGB(  34, 139, 34 ) },
	{ "fuchsia", RGB( 255, 0, 255 ) },
	{ "gainsboro", RGB( 220, 220, 220 ) },
	{ "ghostwhite", RGB( 248, 248, 255 ) },
	{ "gold", RGB( 255, 215, 0 ) },
	{ "goldenrod", RGB( 218, 165, 32 ) },
	{ "gray", RGB( 128, 128, 128 ) },
	{ "grey", RGB( 128, 128, 128 ) },
	{ "green", RGB(  0, 128, 0 ) },
	{ "greenyellow", RGB( 173, 255, 47 ) },
	{ "honeydew", RGB( 240, 255, 240 ) },
	{ "hotpink", RGB( 255, 105, 180 ) },
	{ "indianred", RGB( 205, 92, 92 ) },
	{ "indigo", RGB(  75, 0, 130 ) },
	{ "ivory", RGB( 255, 255, 240 ) },
	{ "khaki", RGB( 240, 230, 140 ) },
	{ "lavender", RGB( 230, 230, 250 ) },
	{ "lavenderblush", RGB( 255, 240, 245 ) },
	{ "lawngreen", RGB( 124, 252, 0 ) },
	{ "lemonchiffon", RGB( 255, 250, 205 ) },
	{ "lightblue", RGB( 173, 216, 230 ) },
	{ "lightcoral", RGB( 240, 128, 128 ) },
	{ "lightcyan", RGB( 224, 255, 255 ) },
	{ "lightgoldenrodyellow", RGB( 250, 250, 210 ) },
	{ "lightgray", RGB( 211, 211, 211 ) },
	{ "lightgreen", RGB( 144, 238, 144 ) },
	{ "lightgrey", RGB( 211, 211, 211 ) },
	{ "lightpink", RGB( 255, 182, 193 ) },
	{ "lightsalmon", RGB( 255, 160, 122 ) },
	{ "lightseagreen", RGB(  32, 178, 170 ) },
	{ "lightskyblue", RGB( 135, 206, 250 ) },
	{ "lightslategray", RGB( 119, 136, 153 ) },
	{ "lightslategrey", RGB( 119, 136, 153 ) },
	{ "lightsteelblue", RGB( 176, 196, 222 ) },
	{ "lightyellow", RGB( 255, 255, 224 ) },
	{ "lime", RGB(  0, 255, 0 ) },
	{ "limegreen", RGB(  50, 205, 50 ) },
	{ "linen", RGB( 250, 240, 230 ) },
	{ "magenta", RGB( 255, 0, 255 ) },
	{ "maroon", RGB( 128, 0, 0 ) },
	{ "mediumaquamarine", RGB( 102, 205, 170 ) },
	{ "mediumblue", RGB(  0, 0, 205 ) },
	{ "mediumorchid", RGB( 186, 85, 211 ) },
	{ "mediumpurple", RGB( 147, 112, 219 ) },
	{ "mediumseagreen", RGB(  60, 179, 113 ) },
	{ "mediumslateblue", RGB( 123, 104, 238 ) },
	{ "mediumspringgreen", RGB(  0, 250, 154 ) },
	{ "mediumturquoise", RGB(  72, 209, 204 ) },
	{ "mediumvioletred", RGB( 199, 21, 133 ) },
	{ "midnightblue", RGB(  25, 25, 112 ) },
	{ "mintcream", RGB( 245, 255, 250 ) },
	{ "mistyrose", RGB( 255, 228, 225 ) },
	{ "moccasin", RGB( 255, 228, 181 ) },
	{ "navajowhite", RGB( 255, 222, 173 ) },
	{ "navy", RGB(  0, 0, 128 ) },
	{ "oldlace", RGB( 253, 245, 230 ) },
	{ "olive", RGB( 128, 128, 0 ) },
	{ "olivedrab", RGB( 107, 142, 35 ) },
	{ "orange", RGB( 255, 165, 0 ) },
	{ "orangered", RGB( 255, 69, 0 ) },
	{ "orchid", RGB( 218, 112, 214 ) },
	{ "palegoldenrod", RGB( 238, 232, 170 ) },
	{ "palegreen", RGB( 152, 251, 152 ) },
	{ "paleturquoise", RGB( 175, 238, 238 ) },
	{ "palevioletred", RGB( 219, 112, 147 ) },
	{ "papayawhip", RGB( 255, 239, 213 ) },
	{ "peachpuff", RGB( 255, 218, 185 ) },
	{ "peru", RGB( 205, 133, 63 ) },
	{ "pink", RGB( 255, 192, 203 ) },
	{ "plum", RGB( 221, 160, 221 ) },
	{ "powderblue", RGB( 176, 224, 230 ) },
	{ "purple", RGB( 128, 0, 128 ) },
	{ "red", RGB( 255, 0, 0 ) },
	{ "rosybrown", RGB( 188, 143, 143 ) },
	{ "royalblue", RGB(  65, 105, 225 ) },
	{ "saddlebrown", RGB( 139, 69, 19 ) },
	{ "salmon", RGB( 250, 128, 114 ) },
	{ "sandybrown", RGB( 244, 164, 96 ) },
	{ "seagreen", RGB(  46, 139, 87 ) },
	{ "seashell", RGB( 255, 245, 238 ) },
	{ "sienna", RGB( 160, 82, 45 ) },
	{ "silver", RGB( 192, 192, 192 ) },
	{ "skyblue", RGB( 135, 206, 235 ) },
	{ "slateblue", RGB( 106, 90, 205 ) },
	{ "slategray", RGB( 112, 128, 144 ) },
	{ "slategrey", RGB( 112, 128, 144 ) },
	{ "snow", RGB( 255, 250, 250 ) },
	{ "springgreen", RGB(  0, 255, 127 ) },
	{ "steelblue", RGB(  70, 130, 180 ) },
	{ "tan", RGB( 210, 180, 140 ) },
	{ "teal", RGB(  0, 128, 128 ) },
	{ "thistle", RGB( 216, 191, 216 ) },
	{ "tomato", RGB( 255, 99, 71 ) },
	{ "turquoise", RGB(  64, 224, 208 ) },
	{ "violet", RGB( 238, 130, 238 ) },
	{ "wheat", RGB( 245, 222, 179 ) },
	{ "white", RGB( 255, 255, 255 ) },
	{ "whitesmoke", RGB( 245, 245, 245 ) },
	{ "yellow", RGB( 255, 255, 0 ) },
	{ "yellowgreen", RGB( 154, 205, 50 ) }
};

#endif // ! _COLOR_HPP_
