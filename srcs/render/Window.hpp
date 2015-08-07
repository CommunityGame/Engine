#ifndef _WINDOW_H_
# define _WINDOW_H_

# ifndef GLFW_INCLUDE_ES3
#  define GLFW_INCLUDE_ES3
# endif
# include <GLFW/glfw3.h>

# include <exception>
# include <iostream>
# include <boost/smart_ptr/shared_ptr.hpp>

# include "../EngineException.hpp"
# include "../debugs/Logger.hpp"

using namespace boost;

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
	 * @return shared_ptr<Window>
	 */
	static shared_ptr<Window>	create( int width, int height, std::string const & title );

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
	void					setVsync( bool vSync );
	void					setWidth( int width );
	void					setHeight( int height );

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

	static const std::string	TAG;
};

#endif // ! _WINDOW_H_