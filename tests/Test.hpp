#ifndef _TEST_HPP
# define _TEST_HPP
# include "../srcs/AGame.hpp"

class Test : public AGame
{
public:
	Test( void );
	virtual void	init( CoreEngine const & coreEngine );
};

#endif // ! _TEST_HPP
