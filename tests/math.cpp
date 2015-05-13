#include <iostream>
#include "../srcs/math/Math.hpp"

int		main( void )
{
//	std::cout << "90 to rad: " << Math::toRadians( 90 ) << std::endl;
//	std::cout << "12.21f to rad: " << Math::toRadians( 12.21f ) << std::endl;
//	std::cout << "321.31321 to rad: " << Math::toRadians( 321.31321 ) << std::endl;
//	std::cout << "321L to rad: " << Math::toRadians( 321L ) << std::endl;
//
//	Mat4i	mat4i = Mat4i().initIdentity();
//	std::cout << mat4i << std::endl;
//
//	mat4i[1] = 12;
//	std::cout << mat4i << std::endl;
//
//	mat4i = Mat4i().initScale( Vec3i( 1, 2, 3 ) );
//	std::cout << mat4i << std::endl;
//
//	mat4i = Mat4i().initTranslation( Vec3i( 4, 5, 6 ) );
//	std::cout << mat4i << std::endl;
//
//	std::cout << mat4i * Mat4i().initScale( Vec3i( 1, 2, 3 ) ) << std::endl;
//
//	std::cout << mat4i + Mat4i().initScale( Vec3i( 1, 2, 3 ) ) << std::endl;
//
//	std::cout << mat4i.transposed() << std::endl;
//
//	std::cout << mat4i[0] << std::endl;

	std::cout << Quatf( 3, 1.75, -4, -5 ) * Quatf( 3, 1.75, -4, -6 ) << std::endl;
	std::cout << ( Quatf( 3, 1.75, -4, -5 ) * Quatf( 3, 1.75, -4, -6 ) ).norm() << std::endl;
	std::cout << ( Quatf( 3, 1.75, -4, -5 ) * Quatf( 3, 1.75, -4, -6 ) ).normalize() << std::endl;
	std::cout << ( Quatf( 3, 1.75, -4, -5 ) * Quatf( 3, 1.75, -4, -6 ) ).conjugate() << std::endl;
	std::cout << ( Quatf( 3, 1.75, -4, -5 ) * Quatf( 3, 1.75, -4, -6 ) ).inverse() << std::endl;
	std::cout << ( Quatf( 3, 1.75, -4, -5 ) * Quatf( 3, 1.75, -4, -6 ) ).toMatrix() << std::endl;

	return ( 0 );
}
