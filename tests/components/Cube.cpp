#include "Cube.hpp"

shared_ptr<Mesh>	Cube::_cube = nullptr;

Cube::Cube( float size )
{
	if ( Cube::_cube == nullptr )
	{
		Cube::_cube = shared_ptr<Mesh>( new Mesh(
				std::vector<Vertexf>( {
						Vertexf( Vec3f( -1, -1, -1 ) ),
						Vertexf( Vec3f( -1, +1, -1 ) ),
						Vertexf( Vec3f( +1, -1, -1 ) ),
						Vertexf( Vec3f( +1, +1, -1 ) ),
						Vertexf( Vec3f( +1, -1, +1 ) ),
						Vertexf( Vec3f( +1, +1, +1 ) ),
						Vertexf( Vec3f( -1, -1, +1 ) ),
						Vertexf( Vec3f( -1, +1, +1 ) ),
				} ),
				std::vector<GLuint>( {
						0, 1, 2,  2, 1, 3,
						2, 3, 4,  4, 3, 5,
						4, 5, 6,  6, 5, 7,
						6, 7, 0,  0, 7, 1,
						1, 7, 3,  3, 7, 5,
						6, 0, 4,  4, 0, 2
				} )
		) );
		Cube::_cube->calcNormal();
		Cube::_cube->bufferData();
	}

	this->getTransform().setScale( Vec3f( size, size, size ) );
	this->addComponent( Cube::_cube );
}
