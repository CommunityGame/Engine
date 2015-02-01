#include <string>
#include <GLFW/glfw3.h>

#include "Window.hpp"

int     main( void )
{
   	Window *	window;

    window = Window::create( 850, 550, "First test" );

    /* Make the window's context current */
//    glfwMakeContextCurrent( window->getGLFWWindow() );

    /* Loop until the user closes the window */
    while ( ! window->isCloseRequested() )
    {
        /* Render here */

        /* Swap front and back buffers */
		window->refresh();

        /* Poll for and process events */
        glfwPollEvents();
    }

	delete window;
    return ( 0 );
}