#ifndef _TIMER_H_
# define _TIMER_H_

// #include <map>
#include <string>
#include <chrono>

#define SECOND			( 1000000.0 )

typedef std::chrono::minutes					minutes;
typedef std::chrono::seconds					seconds;
typedef std::chrono::milliseconds				milliseconds;
typedef std::chrono::microseconds				microseconds;
typedef std::chrono::nanoseconds				nanoseconds;
typedef std::chrono::high_resolution_clock		high_resolution_clock;
typedef std::chrono::steady_clock::time_point	time_point;

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

	/*!
	 * @function pushTimePoint
	 * Store @timePoint named by @name in map _timePoints
	 *
	 * @return void
	 */
	// static void									pushTimePoint( std::string const & name, time_point timePoint );
	// static void									pushTimePoint( std::string const & name );
private:
	static time_point							_epoch;
	// static std::map< std::string, time_point >	_timePoints;
};

#endif // ! _TIMER_H_
