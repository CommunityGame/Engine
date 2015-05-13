#include "Math.hpp"

template <typename T>
T		Math::toDegrees( T value )
{
	return ( value * T( 180 ) / T( MATH_PI ) );
}

template <typename T>
T		Math::toRadians( T value )
{
	return ( value * T( MATH_PI ) / T( 180 ) );
}