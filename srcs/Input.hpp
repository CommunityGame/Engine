#ifndef _INPUT_H_
# define _INPUT_H_

# include "render/Window.hpp"
# include "math/Math.hpp"

class Input
{
public:
	Input( Window * window );

	// FUNCTIONS
	void			pollEvents( void );
	bool			isCloseRequested( void ) const;

	// GETTER
	bool			isKeyPressed( int key ) const;
	bool			isMouseButtonPressed( int button ) const;
	Vec2d			getMousePosition( void ) const;
	Vec2d			getWindowCenter( void ) const;

	// SETTER
	void			setCursor( bool visible );
	void			setMousePosition( Vec2d pos );

private:
	Window *		_window;
	bool			_keyPressed[GLFW_KEY_LAST];
	bool			_mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST];
};

#endif // ! _INPUT_H_
