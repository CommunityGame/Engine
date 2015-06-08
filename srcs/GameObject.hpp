#ifndef _GAME_OBJECT_H_
# define _GAME_OBJECT_H_

# include <vector>
# include "Input.hpp"
# include "AObjectComponent.hpp"
# include "math/Math.hpp"

class GameObject
{
public:
	GameObject( void );

	/*!
	 * @function input
	 * @param input: is a reference to the instance of Input
	 * input this GameObject
	 *
	 * @return void
	 */
	virtual void		input( Input & input );

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
	virtual void		render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;

	/*!
	 * @function inputAll
	 * @param input: is a reference to the instance of Input
	 * call input and inputAll for all children of this GameObject
	 *
	 * @return void
	 */
	void				inputAll( Input & input );

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
	void				renderAll( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const;

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
	GameObject			*addComponent( AObjectComponent * component );

	//	GETTER
	Transformf *		getTransform( void );
	Transformf const &	getTransform( void ) const;
	GameObject *		getParent( void ) const;

	//	SETTER
	void				setTransform( Transformf const & transform );
	void				setParent( GameObject * parent );

private:
	std::vector<GameObject *>			_childrens;
	std::vector<AObjectComponent *>		_components;
	GameObject *						_parent;
	Transformf							_transform;
};

#endif // ! _GAME_OBJECT_H_
