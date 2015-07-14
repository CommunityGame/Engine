#ifndef _MESH_BUILDER_H_
# define _MESH_BUILDER_H_

#include "Mesh.hpp"

class MeshBuilder
{
public:
	static Mesh *		loadFromObj( std::string const & file );

private:
	static const std::string	TAG;
};

#endif // ! _MESH_BUILDER_H_
