#ifndef _INPUT_COMPONENT_H_
# define _INPUT_COMPONENT_H_

#include "AObjectComponent.hpp"

class InputComponent : public AObjectComponent
{
public:
	virtual void		update( double delta ) {};
	virtual void		init( CoreEngine & coreEngine ) {};
};

#endif // ! _INPUT_COMPONENT_H_
