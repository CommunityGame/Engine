#ifndef _MATH_H_
# define _MATH_H_

# include "Vec.tpp"
# include "Mat.tpp"
# include "Quat.tpp"
# include <cmath>
# define MATH_PI 3.1415926535897932384626433832795
# define TO_RADIANS(a) (float)( ( (a) * MATH_PI / 180.0f ) )
# define TO_DEGREES(a) (float)( ( (a) * 180.0f / MATH_PI ) )
# define MIN(a,b) ( ( (a) < (b) ) ? (a) : (b) )
# define MAX(a,b) ( ( (a) > (b) ) ? (a) : (b) )

typedef Point<int, 2>		Point2i;
typedef Point<float, 2>		Point2f;
typedef Point<double, 2>	Point2d;
typedef Point<int, 3>		Point3i;
typedef Point<float, 3>		Point3f;
typedef Point<double, 3>	Point3d;

typedef Vec2<int>			Vec2i;
typedef Vec2<float>			Vec2f;
typedef Vec2<double>		Vec2d;
typedef Vec3<int>			Vec3i;
typedef Vec3<float>			Vec3f;
typedef Vec3<double>		Vec3d;

typedef Mat<int, 4, 4>		Mat4i;
typedef Mat<float, 4, 4>	Mat4f;
typedef Mat<double, 4, 4>	Mat4d;

typedef Quat<int>			Quati;
typedef Quat<float>			Quatf;
typedef Quat<double>		Quatd;

class Math
{
public:
	template <typename T>
	static T		toDegrees( T value )
	{
		return ( value * T( 180 ) / T( MATH_PI ) );
	}

	template <typename T>
	static T		toRadians( T value )
	{
		return ( value * T( MATH_PI ) / T( 180 ) );
	}
};

#endif // ! _MATH_H_
