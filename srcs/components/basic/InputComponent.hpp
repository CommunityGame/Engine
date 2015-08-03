#ifndef _INPUT_COMPONENT_H_
# define _INPUT_COMPONENT_H_

#include "AObjectComponent.hpp"

class InputComponent : public AObjectComponent
{
public:
	/*!
	 * @function input
	 * @param input: is a reference to the instance of Input
	 * input this AObjectComponent
	 *
	 * @return void
	 */
	virtual void		input( Input & input, double delta ) = 0;

	virtual void		update( double delta ) {};
	virtual void		init( CoreEngine & coreEngine ) {};
};

#endif // ! _INPUT_COMPONENT_H_
