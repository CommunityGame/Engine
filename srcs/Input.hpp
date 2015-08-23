#ifndef _INPUT_H_
# define _INPUT_H_

# include "render/GLWindow.hpp"
# include "math/Math.hpp"

#define LEFT_STICKER	0
#define RIGHT_STICKER	1
#define TRIGGER			2

#define LEFT			0
#define RIGHT			1
#define UP				2
#define DOWN			3

class Input
{
public:

	// FUNCTIONS
	static void		init( shared_ptr<GLWindow> const & window );
	static void		pollEvents( shared_ptr<GLWindow> const & window );
	static bool		isCloseRequested( void );

	// GETTER
	static bool		isKeyPressed( int key );
	static bool		isMouseButtonPressed( int button );
	static Vec2f	getMousePosition( void );
	static Vec2f	getWindowCenter( void );
	static Vec2f	getScrollOffset( void );
	static bool		isJoystickPresent( int joystick );
	static std::string	getJoystickName( int joystick );
	static bool		isJoystickButtonPressed( int joystick, int button );
	static float	getJoystickPressure( int joystick, int button, int direction );
	static Vec2f	getJoystickDirection( int joystick, int button );

	// SETTER
	static void		setCursor( bool visible );
	static void		setMousePosition( Vec2f pos );
	static void		setScrollOffset( Vec2f pos );

private:
	Input( void ) {};

	static shared_ptr<GLWindow>	_window;
	static bool		_keyPressed[GLFW_KEY_LAST];
	static bool		_mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST];
	static Vec2f	_scrollOffset;

	static const std::string	TAG;
};

#endif // ! _INPUT_H_
