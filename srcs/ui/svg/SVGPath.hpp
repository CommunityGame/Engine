#ifndef _SVG_PATH_HPP
#define _SVG_PATH_HPP

#include <iostream>
#include <vg/vgu.h>
#include <rapidxml/rapidxml.hpp>
#include <regex>
#include "../../math/Math.hpp"
#include "SVGAttributes.hpp"
#include "ISVGElement.hpp"

class SVGPath : public ISVGElement
{
public:
	SVGPath( std::string const & path );
	~SVGPath( void );

	void		render( void ) const;
	void		overrideAttributes( rapidxml::xml_node<> * node );

	// SETTER
	void		setAttributes( SVGAttributes const & g );

private:
	VGPath				_vgPath;

	SVGAttributes		_attributes;

	static std::regex	regex;
	static std::regex	regex2;
};

#endif // ! _SVG_PATH_HPP
