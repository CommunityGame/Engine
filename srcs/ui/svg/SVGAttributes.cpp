#include "SVGAttributes.hpp"

SVGAttributes const &	SVGAttributes::NO_ATTRIBUTES = SVGAttributes();

SVGAttributes::SVGAttributes( rapidxml::xml_node<> * node ) :
	haveAttributes( false ),
	id( "" ),
	strokeWidth( 1 ),
	strokeLineCap( VG_CAP_BUTT ),
	strokeDashArray( VG_JOIN_MITER ),
	fill( 0, 0, 0, 1 ),
	stroke( 0, 0, 0, 0 ),
	mode( VG_FILL_PATH )
{
	if ( node != nullptr )
		overrideIt( node );
}

void				SVGAttributes::overrideIt( rapidxml::xml_node<> * node )
{
	this->mode |= VG_FILL_PATH;
	if ( node->first_attribute() != nullptr )
		this->haveAttributes = true;
	else
		return;

	rapidxml::xml_attribute<> * attr;
	if ( ( attr = node->first_attribute( "id" ) ) != nullptr )
		this->id = attr->value();
	if ( ( attr = node->first_attribute( "stroke-width" ) ) != nullptr )
		this->strokeWidth = (float) std::atof( attr->value() );
	if ( ( attr = node->first_attribute( "stroke-linecap" ) ) != nullptr )
		this->strokeLineCap = strcmp( attr->value(), "butt" ) == 0 ? VG_CAP_BUTT : strcmp( attr->value(), "round" ) == 0 ? VG_CAP_ROUND : VG_CAP_SQUARE;
	if ( ( attr = node->first_attribute( "stroke" ) ) != nullptr )
	{
		this->mode |= VG_STROKE_PATH;
		this->stroke = Colorf( attr->value() );
	}
	if ( ( attr = node->first_attribute( "fill" ) ) != nullptr && strcmp( attr->value(), "none" ) != 0 )
		this->fill = Colorf( attr->value() );
	if ( node->first_attribute() != nullptr )
		this->haveAttributes = true;
}

SVGAttributes::SVGAttributes( SVGAttributes const & cpy )
{
	*this = cpy;
}

SVGAttributes &		SVGAttributes::operator=( SVGAttributes const & rhs )
{
	this->id = rhs.id;
	this->strokeWidth = rhs.strokeWidth;
	this->strokeLineCap = rhs.strokeLineCap;
	this->strokeDashArray = rhs.strokeDashArray;
	this->fill = rhs.fill;
	this->stroke = rhs.stroke;
	this->mode = rhs.mode;
	return ( *this );
}
