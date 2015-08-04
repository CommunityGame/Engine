#include "LuaScript.hpp"
#include "../../debugs/Logger.hpp"

//const std::string	LuaScript::TAG = "LuaScript";
//
//LuaScript::LuaScript( std::string const & filename ) :
//	_L( nullptr )
//{
//	if ( ( this->_L = lua_open() ) == nullptr )
//	{
//		Logger::e( TAG, "Unable to create newstate of lua" );
//		return ;
//	}
//
//	luaL_openlibs( this->_L );
//
//	if ( luaL_dofile( this->_L, filename.c_str() ) )
//	{
//		Logger::e( TAG, "Failed to load: " + filename );
//		this->_L = nullptr;
//		return ;
//	}
//	Logger::i( TAG, "Lua script: " + filename + " is loaded" );
//}
//
//LuaScript::~LuaScript()
//{
//	if ( this->_L != nullptr )
//	{
//		std::cout << "lua_close" << std::endl;
//		lua_close( this->_L );
//	}
//}
//
//lua_State * LuaScript::getLuaState( void ) const
//{
//	return ( this->_L );
//}
