#ifndef _LOGGER_H_
# define _LOGGER_H_
# include <fstream>

class Logger
{
public:
	template < typename T >
	static void				log( std::string const & mode, T const & msg )
	{
		//TODO: Timer
		std::ofstream	logsFile;
		logsFile.open ( Logger::_logsPath + Logger::_logsName + "." + Logger::_extension );
		if ( logsFile.is_open() )
		{
			logsFile << "[" << mode << "] : " << msg << std::endl;
			logsFile.close();
		}
		return ;
	}

private:
	static std::string		_extension;
	static std::string		_logsPath;
	static std::string		_logsName;
};

#endif // ! _LOGGER_H_