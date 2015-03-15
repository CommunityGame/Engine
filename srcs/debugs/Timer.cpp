#include <chrono>
#include "Timer.hpp"

time_point		Timer::_epoch = high_resolution_clock::now();
std::map< std::string, time_point >	Timer::_timePoints = std::map< std::string, time_point >();


// FUNCTIONS
double			Timer::getNanotime( void )
{
	return ( std::chrono::duration_cast< nanoseconds >( high_resolution_clock::now() - Timer::_epoch ).count() / 1000000000.0 );
}

void			Timer::pushTimePoint( std::string name, time_point timePoint )
{
	Timer::_timePoints.insert( std::pair< std::string, time_point >( name, timePoint ) );
	return ;
}

void			Timer::pushTimePoint( std::string name )
{
	Timer::pushTimePoint( name, high_resolution_clock::now() );
	return ;
}

// GETTER
