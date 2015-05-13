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
};

#endif // ! _UTILS_H_
