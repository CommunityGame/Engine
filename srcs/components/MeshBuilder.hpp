#ifndef _MESH_BUILDER_H_
# define _MESH_BUILDER_H_

#include <map>
#include "Mesh.hpp"

class MeshBuilder
{
public:
	static shared_ptr<Mesh>		loadFromObj( std::string const & file );

private:
	static const std::string	TAG;
	static std::map<std::string, shared_ptr<Mesh>>	_loadedMesh;
};

#endif // ! _MESH_BUILDER_H_
