#ifndef _A_TAG_H_
# define _A_TAG_H_

#include <rapidxml/rapidxml.hpp>
#include <string>
#include <vector>
#include <map>
#include "../../CoreEngine.hpp"

class UiComponent;

class ATag
{
public:
	ATag( rapidxml::xml_node<> * node, ATag * parent = nullptr, UiComponent * component = nullptr, int level = 0 );

	virtual void					init( CoreEngine & coreEngine );

	// SETTER
	void							setComponent( UiComponent * parent );
	void							setLevel( int level );
	void							setParent( ATag * parent );

	// GETTER
	UiComponent *					getComponent( void ) const;
	int								getLevel( void ) const;
	ATag *							getParent( void ) const;

//	virtual ATag &					operator=( ATag const & rhs ) = 0;

protected:
	UiComponent *					_component;
	ATag *							_parent;
	int								_level;
	std::string						_values;
	std::vector<ATag *>				_tags;

	std::string						_width;
	std::string						_height;

private:
	static const std::string	TAG;
};

#endif // ! _A_TAG_H_
