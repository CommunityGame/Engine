#ifndef _MATH_H_
# define _MATH_H_

# include "Transform.tpp"
# include "Vertex.tpp"
# include <cmath>
# include <ostream>
# define MATH_PI 3.1415926535897932384626433832795
# define TO_RADIANS(a) (float)( ( (a) * MATH_PI / 180.0f ) )
# define TO_DEGREES(a) (float)( ( (a) * 180.0f / MATH_PI ) )
# define MIN(a,b) ( ( (a) < (b) ) ? (a) : (b) )
# define MAX(a,b) ( ( (a) > (b) ) ? (a) : (b) )

#define Point2i Point<int, 2>
#define Point2f Point<float, 2>
#define Point2d Point<double, 2>
#define Point3i Point<int, 3>
#define Point3f Point<float, 3>
#define Point3d Point<double, 3>

#define Vec2i Vec2<int>
#define Vec2f Vec2<float>
#define Vec2d Vec2<double>
#define Vec3i Vec3<int>
#define Vec3f Vec3<float>
#define Vec3d Vec3<double>

#define Mat4i Mat4<int>
#define Mat4f Mat4<float>
#define Mat4d Mat4<double>

#define Quati Quat<int>
#define Quatf Quat<float>
#define Quatd Quat<double>

#define Transformi Transform<int>
#define Transformf Transform<float>
#define Transformd Transform<double>

#define Colori Color<int>
#define Colorf Color<float>
#define Colord Color<double>

#define Vertexi Vertex<int>
#define Vertexf Vertex<float>
#define Vertexd Vertex<double>

class Math
{
public:
	template <typename T>
	static T		toDegrees( T value );

	template <typename T>
	static T		toRadians( T value );
};

#endif // ! _MATH_H_
