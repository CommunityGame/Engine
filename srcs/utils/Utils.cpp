#include "Utils.hpp"

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
