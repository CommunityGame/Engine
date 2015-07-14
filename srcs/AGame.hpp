#ifndef _A_GAME_H_
# define _A_GAME_H_

#include "render/RenderEngine.hpp"
#include "GameObject.hpp"
#include "Input.hpp"
#include "CoreEngine.hpp"

class AGame
{
public:
	~AGame( void );

	/*!
	 * @function init
	 * Call before the game loop to initialize all objects
	 *
	 * @return void
	 */
	virtual void	init( void ) = 0;

	/*!
	 * @function input
	 * @param input: is a reference to the instance of Input
	 * input all GameObject attached to rootObject
	 *
	 * @return void
	 */
	void			input( Input & input, double delta );

	/*!
	 * @function update
	 * @param delta: time passed to run the previous loop
	 * update all GameObject attached to rootObject
	 *
	 * @return void
	 */
	virtual void	update( double delta );

	/*!
	 * @function render
	 * @param renderEngine: is a reference to the instance of RenderEngine
	 * render all GameObject attached to rootObject
	 *
	 * @return void
	 */
	void			render( RenderEngine const & renderEngine ) const;

	/*!
	 * @function physics
	 * @param physicsEngine: is a reference to the instance of PhysicsEngine
	 * physics all GameObject attached to rootObject
	 *
	 * @return void
	 */
	void			physics( PhysicsEngine const & physicsEngine, double delta ) const;

	/*!
	 * @function addObject
	 * @param object: object to add to the game
	 * add gameObject to the game
	 *
	 * @return void
	 */
	void			addObject( GameObject * object );

	/*!
	 * @function setCamera
	 * @param camera: set the main camera
	 *
	 * @return void
	 */
	void			setCamera( Camera * camera );

	/*!
	 * @function setCoreEngine
	 * @param camera: set the core engine
	 *
	 * @return void
	 */
	void			setCoreEngine( CoreEngine * coreEngine );

	/*!
	 * @function getCamera
	 *
	 * @return the main camera
	 */
	Camera *		getCamera( void ) const;

	/*!
	 * @function getRootObject
	 *
	 * @return th root object
	 */
	GameObject *	getRootObject( void ) const;

private:
	GameObject *		_rootObject;
	Camera *			_camera;

protected:
	CoreEngine *		_coreEngine;
};

#endif // ! _A_GAME_H_
