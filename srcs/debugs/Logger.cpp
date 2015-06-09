#include "Logger.hpp"

std::string			Logger::_extension = "log";
std::string			Logger::_logsPath = "logs/";
std::string			Logger::_logsName = "Engine";
int					Logger::_VERBOSITY = INFO;
bool				Logger::_printLogs = false;

void				Logger::setVerbosity( int verbosity )
{
	Logger::_VERBOSITY = verbosity;
}

void				Logger::setPrintLogs( bool state )
{
	Logger::_printLogs = state;
}