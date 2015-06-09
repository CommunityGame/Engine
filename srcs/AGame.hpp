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
	virtual void	init( CoreEngine const & coreEngine ) = 0;

	/*!
	 * @function input
	 * @param input: is a reference to the instance of Input
	 * input all GameObject attached to rootObject
	 *
	 * @return void
	 */
	void			input( Input & input );

	/*!
	 * @function update
	 * @param delta: time passed to run the previous loop
	 * update all GameObject attached to rootObject
	 *
	 * @return void
	 */
	void			update( double delta );

	/*!
	 * @function render
	 * @param renderEngine: is a reference to the instance of RenderEngine
	 * render all GameObject attached to rootObject
	 *
	 * @return void
	 */
	void			render( RenderEngine const & renderEngine ) const;

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
	 * @function getCamera
	 *
	 * @return the main camera
	 */
	Camera *		getCamera( void ) const;

private:
	GameObject *		_rootObject;
	Camera *			_camera;
};

#endif // ! _A_GAME_H_
