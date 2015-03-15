#ifndef _INPUT_H_
# define _INPUT_H_
#include "render/Window.hpp"

class Input
{
public:
	Input( Window * window );

	// FUNCTIONS
	void			pollEvents( void ) const;
	bool			isCloseRequested( void ) const;

	// GETTER
	bool			isKeyDown( int key ) const;
	bool			isKeyUp( int key ) const;

private:
	Window *		_window;
};

#endif // ! _INPUT_H_
