#ifndef _ENGINE_EXCEPTION_H_
# define _ENGINE_EXCEPTION_H_
# include <exception>
# include <string>

class EngineException : public std::exception
{
public:
	EngineException( void ) : _msg( "" ) {};
	EngineException( std::string const & msg ) :
			_msg( msg )
	{
		return;
	}
	virtual ~EngineException( void ) {};

	virtual const char*		what() const throw()
	{
		return ( this->_msg.c_str() );
	}

private:
	std::string 				_msg;
};

#endif // ! _ENGINE_EXCEPTION_H_
