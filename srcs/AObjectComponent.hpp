#ifndef _OBJECT_COMPONENT_H_
# define _OBJECT_COMPONENT_H_

#include "Input.hpp"
#include "math/Math.hpp"

class GameObject;
class RenderEngine;
class Shader;
class Camera;

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
	virtual void		input( Input const & input ) = 0;

	/*!
	 * @function update
	 * @param delta: time passed to run the previous loop
	 * update this AObjectComponent
	 *
	 * @return void
	 */
	virtual void		update( double delta ) = 0;

	/*!
	 * @function render
	 * @param renderEngine: is a reference to the instance of RenderEngine
	 * render this AObjectComponent
	 *
	 * @return void
	*/
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const = 0;

	//	GETTER
	GameObject const &	getParent( void ) const;
	Transformf const &	getTransform( void ) const;

	//	SETTER
	void				setParent( GameObject * parent );

protected:
	GameObject *		_parent;
};

#endif // ! _OBJECT_COMPONENT_H_
