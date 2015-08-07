#include "components/basic/AObjectComponent.hpp"
#include "GameObject.hpp"
#include "utils/Utils.hpp"
#include "AGame.hpp"

GameObject::GameObject( void ) :
	_transform( Transformf() ),
	_coreEngine( nullptr )
{
	return ;
}

shared_ptr<GameObject>	GameObject::_new( void )
{
	return ( shared_ptr<GameObject>( new GameObject() ) );
}

GameObject::GameObject( GameObject const & cpy )
{
	*this = cpy;
}

GameObject &	GameObject::operator=( GameObject const & rhs )
{
	if ( this != &rhs )
	{
		this->_childrens = rhs.getChildrens();
		this->_components = rhs.getComponents();
		this->_parent = rhs.getParent();
		this->_coreEngine = rhs.getCoreEngine();
		this->_transform = rhs.getTransform();
	}
	return ( *this );
}

void	GameObject::render( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{
	std::vector<shared_ptr<RenderComponent>>::const_iterator it;

	for ( it = this->_renderComponents.begin(); it != this->_renderComponents.end(); it++ )
		(*it)->render( renderEngine, * this, shader, camera );
	return ;
}

void	GameObject::physics( double delta )
{
	std::vector<shared_ptr<PhysicsComponent>>::iterator it;

	for ( it = this->_physicsComponents.begin(); it != this->_physicsComponents.end(); it++ )
		(*it)->physics( delta );
	return ;
}

void	GameObject::update( double delta )
{
	std::vector<shared_ptr<AObjectComponent>>::iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->update( delta );
	return ;
}

void	GameObject::init( CoreEngine & coreEngine )
{
	std::vector<shared_ptr<AObjectComponent>>::const_iterator it;

	for ( it = this->_components.begin(); it != this->_components.end(); it++ )
		(*it)->init( coreEngine );
	return ;
}

void	GameObject::renderAll( RenderEngine const & renderEngine, Shader const & shader, Camera const & camera ) const
{
	std::vector<shared_ptr<GameObject>>::const_iterator it;

	this->render( renderEngine, shader, camera );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->renderAll( renderEngine, shader, camera );
}

void	GameObject::updateAll( double delta )
{
	std::vector<shared_ptr<GameObject>>::iterator it;

	this->update( delta );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->updateAll( delta );
}

void	GameObject::initAll( CoreEngine & coreEngine )
{
	std::vector<shared_ptr<GameObject>>::const_iterator it;

	this->init( coreEngine );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->initAll( coreEngine );
}

void	GameObject::addChild( shared_ptr<GameObject> const & object )
{
	object->setParent( this );
	object->getTransform().setParent( & this->_transform );
	this->_childrens.push_back( object );
}

void	GameObject::addComponent( shared_ptr<AObjectComponent> component )
{
	component->setParent( this );
	if ( Utils::instanceOf<RenderComponent>( * component.get() ) )
		this->_renderComponents.push_back( shared_ptr<RenderComponent>( dynamic_cast<RenderComponent *>( component.get() ) ) );
	else if ( Utils::instanceOf<PhysicsComponent>( * component.get() ) )
	{
		PhysicsEngine::refreshPhysicsObjectList( true );
		this->_physicsComponents.push_back( shared_ptr<PhysicsComponent>( dynamic_cast<PhysicsComponent *>( component.get()  ) ) );
	}
	else if ( Utils::instanceOf<InputComponent>( * component.get() ) )
		this->_inputComponents.push_back( shared_ptr<InputComponent>( dynamic_cast<InputComponent *>( component.get() ) ) );
	this->_components.push_back( component );
//	return ( shared_from_this() );
}

//	GETTER
Transformf &	GameObject::getTransform( void ) const
{
	return ( this->_transform );
}

GameObject *		GameObject::getParent( void ) const
{
	return ( this->_parent );
}

CoreEngine *		GameObject::getCoreEngine( void ) const
{
	return ( this->_coreEngine );
}


std::vector<shared_ptr<GameObject>> const &		GameObject::getChildrens( void ) const
{
	return ( this->_childrens );
}

std::vector<shared_ptr<AObjectComponent>> const &	GameObject::getComponents( void ) const
{
	return ( this->_components );
}

std::vector<shared_ptr<PhysicsComponent>> const & GameObject::getPhysicsComponents( void ) const
{
	return ( this->_physicsComponents );
}

void GameObject::getPhysicsObjects( std::vector< GameObject * > & havePhysicComponent )
{
	std::vector<shared_ptr<GameObject>>::const_iterator it;

	if ( this->_physicsComponents.size() > 0 )
		havePhysicComponent.push_back( this );
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->getPhysicsObjects( havePhysicComponent );
}

//	SETTER
void					GameObject::setTransform( Transformf const & transform )
{
	this->_transform = transform;
	return ;
}

void					GameObject::setParent( GameObject * parent )
{
	this->_parent = parent;
	return ;
}

void					GameObject::setCoreEngine( CoreEngine * coreEngine )
{
	std::vector<shared_ptr<GameObject>>::const_iterator it;

	this->_coreEngine = coreEngine;
	for ( it = this->_childrens.begin(); it != this->_childrens.end(); it++ )
		(*it)->setCoreEngine( coreEngine );
}

