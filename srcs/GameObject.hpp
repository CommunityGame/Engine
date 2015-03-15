#ifndef _GAME_OBJECT_H_
# define _GAME_OBJECT_H_

# include <vector>
# include "Input.hpp"
# include "render/RenderEngine.hpp"
# include "AObjectComponent.hpp"

class GameObject
{
public:
	/*!
	 * @function input
	 * @param input: is a reference to the instance of Input
	 * input this GameObject
	 *
	 * @return void
	 */
	virtual void		input( Input const & input );

	/*!
	 * @function update
	 * @param delta: time passed to run the previous loop
	 * update this GameObject
	 *
	 * @return void
	 */
	virtual void		update( double delta );

	/*!
	 * @function render
	 * @param renderEngine: is a reference to the instance of RenderEngine
	 * render this GameObject
	 *
	 * @return void
	*/
	virtual void		render( RenderEngine const & renderEngine ) const;

	/*!
	 * @function inputAll
	 * @param input: is a reference to the instance of Input
	 * call input and inputAll for all children of this GameObject
	 *
	 * @return void
	 */
	void				inputAll( Input const & input );

	/*!
	 * @function updateAll
	 * @param delta: time passed to run the previous loop
	 * call update and updateAll for all children of this GameObject
	 *
	 * @return void
	 */
	void				updateAll( double delta );

	/*!
	 * @function renderAll
	 * @param renderEngine: is a reference to the instance of RenderEngine
	 * call render and renderAll for all children of this GameObject
	 *
	 * @return void
	*/
	void				renderAll( RenderEngine const & renderEngine ) const;

	/*!
	 * @function addChild
	 * @param object: object to add to the child list
	 * add GameObject to the childrens list
	 *
	 * @return void
	 */
	void 				addChild( GameObject * object );

	/*!
	 * @function addComponent
	 * @param component: component to add to the component list
	 * add AObjectComponent to the components list
	 *
	 * @return void
	 */
	void				addComponent( AObjectComponent * component );

private:
	std::vector<GameObject *>			_childrens;
	std::vector<AObjectComponent *>		_components;
};

#endif // ! _GAME_OBJECT_H_
