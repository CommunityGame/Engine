#ifndef _GAME_OBJECT_H_
# define _GAME_OBJECT_H_

# include <vector>
# include "Input.hpp"
# include "math/Math.hpp"
# include "render/RenderEngine.hpp"
# include "render/Shader.hpp"
# include "CoreEngine.hpp"
# include "components/basic/AObjectComponent.hpp"
# include "components/basic/PhysicsComponent.hpp"
# include "components/basic/RenderComponent.hpp"
# include "components/basic/InputComponent.hpp"
# include <boost/enable_shared_from_this.hpp>

class Camera;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject( void );
	GameObject( GameObject const & cpy );

	static shared_ptr<GameObject>	_new( void );

	GameObject & operator=( GameObject const & rhs );

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
	 * @function physics
	 * @param delta: time passed to run the previous loop
	 * update this GameObject
	 *
	 * @return void
	 */
	void				physics( double delta );

	/*!
	 * @function init
	 * @param coreEngine: is a reference to the instance of CoreEngine
	 * init this GameObject
	 *
	 * @return void
	*/
	virtual void		init( CoreEngine & coreEngine );

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
	 * @function initAll
	 * @param coreEngine: is a reference to the instance of CoreEngine
	 * call init and initAll for all children of this GameObject
	 *
	 * @return void
	*/
	virtual void		initAll( CoreEngine & coreEngine );

	/*!
	 * @function addChild
	 * @param object: object to add to the child list
	 * add GameObject to the childrens list
	 *
	 * @return void
	 */
	void 				addChild( shared_ptr<GameObject> const & object );

	/*!
	 * @function addComponent
	 * @param component: component to add to the component list
	 * add AObjectComponent to the components list
	 *
	 * @return void
	 */
	void				addComponent( shared_ptr<AObjectComponent> component );

	//	GETTER
	Transformf &		getTransform( void ) const;
	GameObject *		getParent( void ) const;
	CoreEngine *		getCoreEngine( void ) const;
	std::vector<shared_ptr<GameObject>> const &			getChildrens( void ) const;
	std::vector<shared_ptr<AObjectComponent>> const &	getComponents( void ) const;
	std::vector<shared_ptr<PhysicsComponent>> const &	getPhysicsComponents( void ) const;
	void				getPhysicsObjects( std::vector< GameObject * > & havePhysicComponent );

	//	SETTER
	void				setTransform( Transformf const & transform );
	void				setParent( GameObject * parent );
	void				setCoreEngine( CoreEngine * coreEngine );

private:
	std::vector<shared_ptr<GameObject>>			_childrens;
	std::vector<shared_ptr<AObjectComponent>>	_components;
	std::vector<shared_ptr<RenderComponent>>	_renderComponents;
	std::vector<shared_ptr<InputComponent>>		_inputComponents;
	std::vector<shared_ptr<PhysicsComponent>>	_physicsComponents;
	GameObject *		_parent;
	CoreEngine *		_coreEngine;
	mutable Transformf	_transform;
};

#endif // ! _GAME_OBJECT_H_
