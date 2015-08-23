#include <algorithm>
#include "SVGPath.hpp"
#include "ScalableVectorGraphics.hpp"
#include <boost/algorithm/string.hpp>

std::regex	SVGPath::regex( "([ZzMmLlHhVvQqCcTtSsAa])([^ZzMmLlHhVvQqCcTtSsAa]*)" );
std::regex	SVGPath::regex2( "([-+]?\\.?[0-9][^, +-]*)" );

SVGPath::SVGPath( std::string const & path )
{
	VGint					numSegments;
	std::vector<VGubyte>	pathSegments;
	std::vector<float>		pathData;

	this->_vgPath = vgCreatePath( VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL );
	numSegments = 0;

	int cmds[][3] = {
			{ 'Z', VG_CLOSE_PATH | VG_ABSOLUTE, 0 },
			{ 'z', VG_CLOSE_PATH | VG_RELATIVE, 0 },
			{ 'M', VG_MOVE_TO_ABS, 2 },
			{ 'm', VG_MOVE_TO_REL, 2 },
			{ 'L', VG_LINE_TO_ABS, 2 },
			{ 'l', VG_LINE_TO_REL, 2 },
			{ 'H', VG_HLINE_TO_ABS, 1 },
			{ 'h', VG_HLINE_TO_REL, 1 },
			{ 'V', VG_VLINE_TO_ABS, 1 },
			{ 'v', VG_VLINE_TO_REL, 1 },
			{ 'Q', VG_QUAD_TO_ABS, 4 },
			{ 'q', VG_QUAD_TO_REL, 4 },
			{ 'C', VG_CUBIC_TO_ABS, 6 },
			{ 'c', VG_CUBIC_TO_REL, 6 },
			{ 'T', VG_SQUAD_TO_ABS, 2 },
			{ 't', VG_SQUAD_TO_REL, 2 },
			{ 'S', VG_SCUBIC_TO_ABS, 4 },
			{ 's', VG_SCUBIC_TO_REL, 4 },
			{ 'A', VG_SCCWARC_TO_ABS, 5 },
			{ 'a', VG_SCCWARC_TO_REL, 5 },
			0
	};
	//TODO: elliptical arc large-arc-flag and sweep-flag

	std::smatch smatch;
	std::string tmp( path );
	while ( std::regex_search( tmp, smatch, regex ) )
	{
		int count = 0;
		std::smatch smatch2;
		std::string tmp2( smatch[2].str() );
		while ( std::regex_search( tmp2, smatch2, regex2 ) )
		{
			pathData.push_back( (float)std::atof( smatch2[1].str().c_str() ) );
			count++;
			tmp2 = smatch2.suffix().str();
		}

		int i = 0;
		while ( cmds[i] && cmds[i][0] != smatch[1].str()[0] )
			i++;

		for ( int j = 0; j < ( cmds[i][2] ? count / cmds[i][2] : 0 ); j++, numSegments++ )
			pathSegments.push_back( (VGubyte) cmds[i][1] );
		if ( cmds[i][0] == 'z' || cmds[i][0] == 'Z' )
		{
			pathSegments.push_back( (VGubyte) cmds[i][1] );
			numSegments++;
		}
		tmp = smatch.suffix().str();
	}
	vgAppendPathData( this->_vgPath, numSegments, &( * pathSegments.begin() ), &( * pathData.begin() ) );
}

SVGPath::~SVGPath( void )
{
	vgDestroyPath( this->_vgPath );
}

void		SVGPath::render( void ) const
{
	float style[] = {
			this->_attributes.stroke.getR(), this->_attributes.stroke.getG(), this->_attributes.stroke.getB(), this->_attributes.stroke.getA(),
			this->_attributes.fill.getR(), this->_attributes.fill.getG(), this->_attributes.fill.getB(), this->_attributes.fill.getA()
	};
//	std::cout << this->_attributes.mode << std::endl;

	vgSetParameterfv( ScalableVectorGraphics::getStrokePaint(), VG_PAINT_COLOR, 4, &style[0] );
	vgSetParameterfv( ScalableVectorGraphics::getFillPaint(), VG_PAINT_COLOR, 4, &style[4] );
	vgSetf( VG_STROKE_LINE_WIDTH, this->_attributes.strokeWidth );
//	vgSetf( VG_STROKE_CAP_STYLE, this->_attributes.strokeLineCap );
	vgSetf( VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND ); //VG_JOIN_MITER, VG_JOIN_BEVEL, VG_JOIN_ROUND
	vgDrawPath( this->_vgPath, this->_attributes.mode );
}

void		SVGPath::setAttributes( SVGAttributes const & a )
{
	this->_attributes = a;
}

void		SVGPath::overrideAttributes( rapidxml::xml_node<> * node )
{
	this->_attributes.overrideIt( node );
}