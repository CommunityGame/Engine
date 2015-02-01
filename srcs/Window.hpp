#ifndef _WINDOW_H_
# define _WINDOW_H_
# include <exception>
# include <iostream>
# include <GLFW/glfw3.h>

# include "EngineException.hpp"
# include "Logger.hpp"

class Window
{
public:
	~Window( void );

	// FUNCTIONS
	void					refresh( void );

	// STATIC FUNCTIONS
	static Window *			create( int width, int height, std::string const & title );
	static void 			initGLFW( void );

	// GETTER
	int 					getWidth( void ) const;
	int 					getHeight( void ) const;
	std::string				getTitle( void ) const;
	GLFWwindow * 			getGLFWWindow( void ) const;
	bool					isCloseRequested( void ) const;

private:
	Window( void );
	Window( int width, int height, std::string const & title );

	int 					_width;
	int 					_height;
	std::string 			_title;
	GLFWwindow *			_GLFWwindow;

	static bool 			_glfwIsInit;
	static int				_nbWindow;
};

#endif // ! _WINDOW_H_