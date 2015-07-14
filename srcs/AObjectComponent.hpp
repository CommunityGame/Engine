#ifndef _OBJECT_COMPONENT_H_
# define _OBJECT_COMPONENT_H_

#include "Input.hpp"
#include "math/Math.hpp"
#include "CoreEngine.hpp"

class AObjectComponent
{
public:
	/*!
	 * @function input
	 * @param input: is a reference to the instance of Input
	 * input this AObjectComponent
	 *
	 * @return void
	 */
	virtual void		input( Input & input, double delta ) {};

	/*!
	 * @function update
	 * @param delta: time passed to run the previous loop
	 * update this AObjectComponent
	 *
	 * @return void
	 */
	virtual void		update( double delta ) {};

	/*!
	 * @function render
	 * @param renderEngine: is a reference to the instance of RenderEngine
	 * render this AObjectComponent
	 *
	 * @return void
	*/
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const {};

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
