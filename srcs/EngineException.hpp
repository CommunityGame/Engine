#ifndef _ENGINE_EXCEPTION_H_
# define _ENGINE_EXCEPTION_H_
# include <exception>
# include <string>
# include "debugs/Logger.hpp"
# include <typeinfo>

class EngineException : public std::exception
{
public:
	EngineException( void ) : _msg( "" ) {};
	EngineException( std::string const & msg ) :
			_msg( msg )
	{
		Logger::e( typeid( EngineException ).name(), msg );
		return;
	}
	virtual ~EngineException( void ) {};

	virtual const char *	what( void )
	{
		return ( this->_msg.c_str() );
	}

private:
	std::string 				_msg;
};

#endif // ! _ENGINE_EXCEPTION_H_
