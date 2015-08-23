#include "ScalableVectorGraphics.hpp"
#include "../../utils/Utils.hpp"

VGPaint				ScalableVectorGraphics::_strokePaint = nullptr;
VGPaint				ScalableVectorGraphics::_fillPaint = nullptr;

ScalableVectorGraphics::ScalableVectorGraphics( std::string const & file )
{
	if ( ScalableVectorGraphics::_strokePaint == nullptr )
	{
		ScalableVectorGraphics::_strokePaint = vgCreatePaint();
		vgSetPaint( ScalableVectorGraphics::_strokePaint, VG_STROKE_PATH );
	}
	if ( ScalableVectorGraphics::_fillPaint == nullptr )
	{
		ScalableVectorGraphics::_fillPaint = vgCreatePaint();
		vgSetPaint( ScalableVectorGraphics::_fillPaint, VG_FILL_PATH );
	}

	rapidxml::xml_document<> ui_doc;

	ui_doc.parse<0>( (char *) Utils::readFile( file ).c_str() );

	rapidxml::xml_node<> * n = ui_doc.first_node( "svg", 0, false );

	parseNode( n->first_node() );
}

void ScalableVectorGraphics::parseNode( rapidxml::xml_node<> * node, SVGAttributes g )
{
	for ( ; node; node = node->next_sibling() )
	{
//		std::cout << node->name() << std::endl;
		//TODO: group, g flag
		if ( std::string( node->name() ) == "g" )
		{
			SVGAttributes group( node );
			parseNode( node->first_node(), group );
		}
		if ( std::string( node->name() ) == "path" )
		{
			rapidxml::xml_attribute<> * attr;
			if ( ( attr = node->first_attribute( "d" ) ) )
			{
				shared_ptr<SVGPath> ptr( new SVGPath( attr->value() ) );
				if ( g.haveAttributes )
					ptr->setAttributes( g );
				ptr->overrideAttributes( node );
				this->_paths.push_back( ptr );
			}
		}
	}
}

void	ScalableVectorGraphics::render( RenderEngine const & renderEngine, GameObject const & parent, Shader const & shader, Camera const & camera ) const
{
	glFrontFace( GL_CCW );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_CULL_FACE );

	vgSeti( VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE );
	vgLoadIdentity();
	vgScale( 0.5, 0.5 );
//	vgTranslate( 900, 900 );
//	vgRotate( 180 );

	std::vector<shared_ptr<SVGPath>>::const_iterator it;

	for ( it = this->_paths.begin(); it != this->_paths.end(); it++ )
		(*it)->render();

	glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	glFrontFace( GL_CW );
}

// SETTER
void	ScalableVectorGraphics::setStrokePaint( VGPaint paint )
{
	ScalableVectorGraphics::_strokePaint = paint;
}

void	ScalableVectorGraphics::setFillPaint( VGPaint paint )
{
	ScalableVectorGraphics::_fillPaint = paint;
}


// GETTER
VGPaint	ScalableVectorGraphics::getStrokePaint( void )
{
	return ( ScalableVectorGraphics::_strokePaint );
}

VGPaint	ScalableVectorGraphics::getFillPaint( void )
{
	return ( ScalableVectorGraphics::_fillPaint );
}
