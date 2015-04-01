#ifndef _LOGGER_H_
# define _LOGGER_H_
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

# define INFO		( 1 )
# define DEBUG		( 2 )
# define WARNING	( 4 )
# define ERROR		( 8 )
# define VERBOSE	( 15 )

class Logger
{
public:
	static void				setVerbosity( int verbosity );
	static void				setPrintLogs( bool state );

	template < typename T >
	static void				i( T const & msg )
	{
		if ( ( Logger::_VERBOSITY & INFO ) == INFO )
			Logger::log( "INFO", msg );
	}

	template < typename T >
	static void				d( T const & msg )
	{
		if ( ( Logger::_VERBOSITY & DEBUG ) == DEBUG )
			Logger::log( "DEBUG", msg );
	}

	template < typename T >
	static void				w( T const & msg )
	{
		if ( ( Logger::_VERBOSITY & WARNING ) == WARNING )
			Logger::log( "WARNING", msg );
	}

	template < typename T >
	static void				e( T const & msg )
	{
		if ( ( Logger::_VERBOSITY & ERROR ) == ERROR )
			Logger::log( "ERROR", msg );
	}

	template < typename T >
	static void				log( std::string const & mode, T const & msg )
	{
		//TODO: Timer
		if ( mkdir( Logger::_logsPath.c_str(), 0755 ) == -1 && errno != EEXIST )
		{
			std::cerr << "Error, mkdir: " << errno << std::endl;
			return ;
		}

		if ( Logger::_PRINT_LOGS )
			std::cout << "[" << mode << "] : " << msg << std::endl;

		std::ofstream outFile( Logger::_logsPath + Logger::_logsName + "." + Logger::_extension, std::ios::app );
		if ( outFile.is_open() )
		{
			outFile << "[" << mode << "] : " << msg << std::endl;
			outFile.close();
		}
		else
			std::cerr << "Error, open: " << errno << std::endl;
		return ;
	}

private:
	static int				_VERBOSITY;
	static bool				_PRINT_LOGS;
	static std::string		_extension;
	static std::string		_logsPath;
	static std::string		_logsName;
};

#endif // ! _LOGGER_H_