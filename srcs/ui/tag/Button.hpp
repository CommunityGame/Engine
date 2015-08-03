#include "ATag.hpp"

#ifndef _Button_H_
# define _BUTTON_H_

class Button : public ATag
{
public:
	Button( rapidxml::xml_node<> * node );

	virtual void			init( CoreEngine & coreEngine );
};

#endif // ! _BUTTON_H_
