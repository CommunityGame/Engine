#include "Utils.hpp"
#include "../debugs/Logger.hpp"
#include <algorithm>
#include <string.h>

const std::string	Utils::TAG = "Utils";

std::vector<std::string> &		Utils::split( std::string const & s, std::vector<std::string> & list )
{
	std::istringstream			iss( s );

	do
	{
		std::string sub;
		iss >> sub;
		list.push_back( sub );
	}
	while ( iss );
	return ( list );
}

// trim from start
std::string &					Utils::ltrim( std::string &s )
{
	s.erase( s.begin(), std::find_if( s.begin(), s.end(), std::not1( std::ptr_fun< int, int >( std::isspace ) ) ) );
	return ( s );
}

// trim from end
std::string &					Utils::rtrim( std::string &s )
{
	s.erase( std::find_if( s.rbegin(), s.rend(), std::not1( std::ptr_fun< int, int >( std::isspace ) ) ).base(), s.end() );
	return ( s );
}

// trim from both ends
std::string &					Utils::trim( std::string &s )
{
	return ltrim( rtrim( s ) );
}

std::string						Utils::readFile( std::string const & file )
{
	std::string			line;
	std::stringstream	ss;
	std::ifstream		fileStream( file, std::ios::in );

	if ( fileStream.is_open() )
		ss << fileStream.rdbuf();
	else
		Logger::e( TAG, "readFile(" + file + ") " + std::string( strerror( errno ) ) );
	return ( ss.str() );
}
