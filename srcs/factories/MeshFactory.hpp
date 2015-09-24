#ifndef _MESH_BUILDER_H_
# define _MESH_BUILDER_H_

#include "IFactory.hpp"
#include "../components/MeshComponent.hpp"
#include <map>

class MeshFactory : public IFactory
{
public:
	static shared_ptr<MeshComponent>		loadObj( std::string const & file );

private:
	static const std::string	TAG;
	static std::map<std::string, shared_ptr<MeshComponent>>	_loadedMesh;
};

#endif // ! _MESH_BUILDER_H_
