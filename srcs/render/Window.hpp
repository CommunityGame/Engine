#ifndef _WINDOW_H_
# define _WINDOW_H_
# include <glad/glad.h>
# include <exception>
# include <iostream>
# include <GLFW/glfw3.h>

# include "../EngineException.hpp"
# include "../debugs/Logger.hpp"

/*!
 * @class Window
 */
class Window
{
public:
	~Window( void );

	// FUNCTIONS
	/*!
	 * @function refresh
	 * Refresh glfw window with glfwSwapBuffer
	 *
	 * @result void
	 */
	void					refresh( void ) const;

	// STATIC FUNCTIONS
	/*!
	 * @function create
	 * Create new window
	 * Call initGLFW if is not init
	 *
	 * @param width			The width of window
	 * @param height		The height of window
	 * @param title			The title of window
	 * @return Window pointer
	 */
	static Window *			create( int width, int height, std::string const & title );

	/*!
	 * @function initGLFW
	 * Init glfw
	 *
	 * @return void
	 */
	static void				initGLFW( void );

	// GETTER
	int						getWidth( void ) const;
	int						getHeight( void ) const;
	std::string				getTitle( void ) const;
	GLFWwindow *			getGLFWwindow( void ) const;

	// SETTER
	void					setTitle( std::string const & title );
	void					setSize( int width, int height );

	void					setWindowPos( int x, int y );
	void					destroyWindow( void );

private:
	Window( void );
	Window( int width, int height, std::string const & title );

	int						_width;
	int						_height;
	std::string				_title;
	bool					_haveFocus;
	GLFWwindow *			_GLFWwindow;

	static bool				_glfwIsInit;
	static int				_nbWindow;
};

#endif // ! _WINDOW_H_