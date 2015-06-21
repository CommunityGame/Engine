#ifndef _TIMER_H_
# define _TIMER_H_

#include <string>

#define SECOND			( 1000000.0 )

class Timer
{
public:
	/*!
	 * @function getMicrotime
	 * Return the nanoseconds since the program run
	 *
	 * @return double
	 */
	static double								getMicrotime( void );

	static long double							currentNanoSecond( void );

	/*!
	 * @function currentDateTime
	 * Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	 *
	 * @return string
	 */
	static const std::string					currentDateTime( void );

	/*!
	 * @function currentDateTime
	 * Get current date/time
	 *
	 * @return string
	 */
	static const std::string					currentDateTime( std::string const & format );

private:
};

#endif // ! _TIMER_H_
