#ifndef _UTILS_H_
# define _UTILS_H_
# include <string>
# include <vector>
# include <sstream>
# include <iostream>

class Utils
{
public:
	static std::vector<std::string> &		split( std::string const & s, std::vector<std::string> & list );
	static std::string &					ltrim( std::string &s );
	static std::string &					rtrim( std::string &s );
	static std::string &					trim( std::string &s );

	static std::string						readFile( std::string const & file );

	template<typename CheckType, typename InstanceType>
	static bool instanceOf( InstanceType & instance )
	{
		return ( dynamic_cast<CheckType *>( & instance ) != NULL );
	}

private:
	static const std::string	TAG;
};

#endif // ! _UTILS_H_
