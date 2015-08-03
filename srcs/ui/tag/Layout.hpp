#ifndef _LAYOUT_H_
# define _LAYOUT_H_

#include "ATag.hpp"
#include "../UiComponent.hpp"

class Layout : public ATag
{
public:
	Layout( rapidxml::xml_node<> * node, UiComponent * parent = nullptr, int level = 0 );

	virtual void			init( CoreEngine & coreEngine );

	static IFactory *		instantiate( void * params = nullptr );

	// SETTER
	void					setColor( Colorf const & color );

	// GETTER
	Colorf const &			getColor( void ) const;

private:
	Colorf					_color;
};

#endif // ! _LAYOUT_H_
