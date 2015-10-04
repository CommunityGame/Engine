#ifndef _SVG_GROUP_HPP_
# define _SVG_GROUP_HPP_

#include <rapidxml/rapidxml.hpp>
#include <vg/openvg.h>
#include <string.h>
#include "../../math/Math.hpp"

class SVGAttributes
{
public:
	SVGAttributes( rapidxml::xml_node<> * node = nullptr );
	SVGAttributes( SVGAttributes const & cpy );

	SVGAttributes & operator=( SVGAttributes const & rhs );

	void			overrideIt( rapidxml::xml_node<> * node );

	bool			haveAttributes;
	std::string		id;
	float			strokeWidth;
	VGCapStyle		strokeLineCap;
	VGJoinStyle		strokeDashArray;
	Colorf			fill;
	Colorf			stroke;
	VGbitfield		mode;

	static SVGAttributes const &	NO_ATTRIBUTES;
};

#endif // ! _SVG_GROUP_HPP_
