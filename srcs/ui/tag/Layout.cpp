#include <iostream>
#include <algorithm>
#include "Layout.hpp"

Layout::Layout( rapidxml::xml_node<> * node, UiComponent * component, int level ) : ATag( node, this, component, level )
{
	for ( rapidxml::xml_attribute<> * attr = node->first_attribute(); attr; attr = attr->next_attribute() )
	{
		std::string attrName( attr->name() );
		std::transform( attrName.begin(), attrName.end(), attrName.begin(), ::tolower );
		if ( attrName == "color" )
			this->_color = Colorf( attr->value() );
		else if ( attrName == "width" )
			this->_width = std::stoi( attr->value() );
		else if ( attrName == "height" )
			this->_height = std::stoi( attr->value() );
	}
}

void			Layout::init( CoreEngine & coreEngine )
{
	float widthWin = coreEngine.getWindow().getWidth();
	float heightWin = coreEngine.getWindow().getHeight();
	ATag::init( coreEngine );
	std::cout << (float)this->_level / 1000.0f << std::endl;
	float posX1 = 0;
	float posX2 = 1;
	float posY1 = 0;
	float posY2 = 1;
	this->_component->putVertex( UiPoint( Vec2f( -1 + posX1, 1 - posY1 ), this->_color ) );
	this->_component->putVertex( UiPoint( Vec2f( -1 + posX2, 1 - posY1 ), this->_color ) );
	this->_component->putVertex( UiPoint( Vec2f( -1 + posX1, 1 - posY2 ), this->_color ) );
	this->_component->putVertex( UiPoint( Vec2f( -1 + posX2, 1 - posY2 ), this->_color ) );
	this->_component->putIndices( { 0, 1, 2, 2, 1, 3 } );
}

IFactory *		Layout::instantiate( void * params )
{
	rapidxml::xml_node<> * node = (rapidxml::xml_node<> *) params;
	return ( new Layout( node ) );
}

// SETTER
void			Layout::setColor( Colorf const & color )
{
	this->_color = color;
}

// GETTER
Colorf const &	Layout::getColor( void ) const
{
	return ( this->_color );
}
