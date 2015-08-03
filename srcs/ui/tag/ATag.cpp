#include <iostream>
#include <algorithm>
#include "ATag.hpp"
#include "../../debugs/Logger.hpp"
#include "../../utils/Factory.hpp"

const std::string		ATag::TAG = "ATag";

ATag::ATag( rapidxml::xml_node<> * node, ATag * parent, UiComponent * component, int level ) :
	_component( component ),
	_level( level ),
	_parent( parent )
{
	if ( node == nullptr )
		return ;
	for ( node = node->first_node(); node; node = node->next_sibling() )
	{
		std::string name( node->name() );
		std::transform( name.begin(), name.end(), name.begin(), ::tolower );

		ATag *	tag = static_cast<ATag *>( Factory::instantiate( name, node ) );
		tag->_level = this->_level + 1;
		tag->_component = this->_component;
		if ( tag )
			this->_tags.push_back( tag );
		else
			Logger::e( TAG, name + " constructor not found" );
	}
}

void ATag::init( CoreEngine & coreEngine )
{
	std::vector<ATag *>::iterator it;

	for ( it = this->_tags.begin(); it != this->_tags.end(); it++ )
		(*it)->init( coreEngine );
}

// SETTER
void			ATag::setComponent( UiComponent * component )
{
	this->_component = component;
}

void			ATag::setLevel( int level )
{
	this->_level = level;
}

void			ATag::setParent( ATag * parent )
{
	this->_parent = parent;
}

// GETTER
UiComponent *	ATag::getComponent( void ) const
{
	return ( this->_component );
}

int				ATag::getLevel( void ) const
{
	return ( this->_level );
}

ATag *			ATag::getParent( void ) const
{
	return ( this->_parent );
}
