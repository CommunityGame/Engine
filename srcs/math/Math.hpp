#ifndef _MATH_H_
# define _MATH_H_

# include "Vec.tpp"
# include <cmath>
# define MATH_PI 3.1415926535897932384626433832795
# define toRadians(x) (float)( ( x * MATH_PI / 180.0f ) )
# define toDegrees(x) (float)( ( x * 180.0f / MATH_PI ) )

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

class Math
{

};

#endif // ! _MATH_H_
