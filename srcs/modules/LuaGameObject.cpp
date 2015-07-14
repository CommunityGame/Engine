#include "LuaGameObject.hpp"
#include "../components/Mesh.hpp"

const char LuaGameObject::className[] = "GameObject";

#define method(class, name) {#name, &class::name}
Luna<LuaGameObject>::RegType LuaGameObject::methods[] = {
		method( LuaGameObject, addObject ),
		method( LuaGameObject, setPos ),
		method( LuaGameObject, update ),
		{0, 0}
};

LuaGameObject::LuaGameObject( lua_State * L )
{
	this->_real = (GameObject *) lua_touserdata( L, 1 );

	if ( this->_real == nullptr )
	{
		this->_real = new GameObject();
		Mesh * mesh = new Mesh();
		mesh->putVertex( Vertexf( Vec3f( -1, 1, -1 ), Colorf( 1, 0, 0, 1 ) ) );
		mesh->putVertex( Vertexf( Vec3f( -1, 1, 1 ), Colorf( 1, 0, 0, 1 ) ) );
		mesh->putVertex( Vertexf( Vec3f( 1, 1, -1 ), Colorf( 1, 0, 0, 1 ) ) );
		mesh->putVertex( Vertexf( Vec3f( 1, 1, 1 ), Colorf( 1, 0, 0, 1 ) ) );
		mesh->calcNormal();
		mesh->bufferData();
		this->_real->addComponent( mesh );

	}
}

int LuaGameObject::addObject( lua_State * L )
{
	LuaGameObject *		luaGameObject = *(LuaGameObject **)lua_touserdata( L, -1 );
	lua_pop( L, 1 );

	if ( luaGameObject != nullptr )
		this->_real->addChild( luaGameObject->getReal() );
	return ( 0 );
}

int LuaGameObject::setPos( lua_State * L )
{
	Vec3f pos;
	pos.setX( (float)lua_tonumber( L, 1 ) );
	pos.setY( (float)lua_tonumber( L, 2 ) );
	pos.setZ( (float)lua_tonumber( L, 3 ) );
//	std::cout << pos << std::endl;
	this->_real->getTransform()->setPosition( pos );
	return ( 0 );
}

int LuaGameObject::update( lua_State * L )
{
	return ( 0 );
}

// GETTTER
GameObject *	LuaGameObject::getReal( void ) const
{
	return ( this->_real );
}
