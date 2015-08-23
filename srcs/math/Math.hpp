#ifndef _MATH_H_
# define _MATH_H_

# include "Transform.tpp"
# include "Color.tpp"
# include "Vertex.tpp"
# include <cmath>
# include <ostream>
# define MATH_PI 3.1415926535897932384626433832795
# define TO_RADIANS(a) (float)( ( (a) * MATH_PI / 180.0f ) )
# define TO_DEGREES(a) (float)( ( (a) * 180.0f / MATH_PI ) )
# define MIN(a,b) ( ( (a) < (b) ) ? (a) : (b) )
# define MAX(a,b) ( ( (a) > (b) ) ? (a) : (b) )

typedef Point<int, 2> Point2i;
typedef Point<float, 2> Point2f;
typedef Point<double, 2> Point2d;
typedef Point<int, 3> Point3i;
typedef Point<float, 3> Point3f;
typedef Point<double, 3> Point3d;

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> vec3d;

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

typedef Quat<int> Quati;
typedef Quat<float> Quatf;
typedef Quat<double> Quatd;

typedef Transform<int> Transformi;
typedef Transform<float> Transformf;
typedef Transform<double> Transformd;

typedef Color<int> Colori;
typedef Color<float> Colorf;
typedef Color<double> Colord;

typedef Vertex<int> Vertexi;
typedef Vertex<float> Vertexf;
typedef Vertex<double> Vertexd;

class Math
{
public:
	template <typename T>
	static T		toDegrees( T value );

	template <typename T>
	static T		toRadians( T value );
};

#endif // ! _MATH_H_
