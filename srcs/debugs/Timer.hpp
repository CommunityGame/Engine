#ifndef _TIMER_H_
# define _TIMER_H_

#include <map>
#include <chrono>

#define SECOND			( 1000000 )

typedef std::chrono::minutes					minutes;
typedef std::chrono::seconds					seconds;
typedef std::chrono::milliseconds				milliseconds;
typedef std::chrono::microseconds				microseconds;
typedef std::chrono::nanoseconds				nanoseconds;
typedef std::chrono::high_resolution_clock		high_resolution_clock;
typedef std::chrono::system_clock::time_point	time_point;

class Timer
{
public:
	/*!
	 * @function getNanotime
	 * Return the nanoseconds since the program run
	 *
	 * @return double
	 */
	static double								getNanotime( void );

	/*!
	 * @function pushTimePoint
	 * Store @timePoint named by @name in map _timePoints
	 *
	 * @return void
	 */
	static void									pushTimePoint( std::string name, time_point timePoint );
	static void									pushTimePoint( std::string name );
private:
	static time_point							_epoch;
	static std::map< std::string, time_point >	_timePoints;
};

#endif // ! _TIMER_H_