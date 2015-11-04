#ifndef _MESH_BUILDER_H_
# define _MESH_BUILDER_H_

#include "IFactory.hpp"
#include "../components/MeshComponent.hpp"
#include <map>

class MeshFactory : public IFactory
{
public:
	virtual t_loader			getLoader( void ) const;

private:
	static shared_ptr<Mesh>		load( std::string const & path );
	static shared_ptr<Mesh>		loadObj( std::string const & file );

	static const std::string	TAG;
};

#endif // ! _MESH_BUILDER_H_
