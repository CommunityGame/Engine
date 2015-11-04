#ifndef _OBJECT_COMPONENT_H_
# define _OBJECT_COMPONENT_H_

#include "../../math/Math.hpp"
#include "../../Input.hpp"
#include "../../CoreEngine.hpp"
#include "../../GameObject.hpp"

class AObjectComponent
{
public:

	/*!
	 * @function update
	 * @param delta: time passed to run the previous loop
	 * update this AObjectComponent
	 *
	 * @return void
	 */
	virtual void		update( double delta ) {};

	/*!
	 * @function init
	 * @param coreEngine: is a reference to the instance of CoreEngine
	 * init this AObjectComponent
	 *
	 * @return void
	*/
	virtual void		init( CoreEngine & coreEngine ) {};

	//	GETTER
	GameObject const &	getParent( void ) const;
	Transformf &		getTransform( void ) const;

	//	SETTER
	virtual void		setParent( GameObject * parent );

protected:
	GameObject *		_parent;
};

#endif // ! _OBJECT_COMPONENT_H_
