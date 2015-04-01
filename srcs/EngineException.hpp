#ifndef _ENGINE_EXCEPTION_H_
# define _ENGINE_EXCEPTION_H_
# include <exception>
# include <string>
# include "debugs/Logger.hpp"

class EngineException : public std::exception
{
public:
	EngineException( void ) : _msg( "" ) {};
	EngineException( std::string const & msg ) :
			_msg( msg )
	{
		Logger::e( msg );
		return;
	}
	virtual ~EngineException( void ) {};

	virtual const char *	what( void ) const _GLIBCXX_USE_NOEXCEPT
	{
		return ( this->_msg.c_str() );
	}

private:
	std::string 			_msg;
};

#endif // ! _ENGINE_EXCEPTION_H_