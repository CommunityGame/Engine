#ifndef _MESH_H_
# define _MESH_H_

#include <vector>
#include "basic/RenderComponent.hpp"
#include "../GameObject.hpp"
#include "../assets/IAsset.hpp"
#include "../assets/Asset.hpp"
#include "../render/Mesh.hpp"

class MeshComponent : public RenderComponent
{
public:
	MeshComponent( void );
	MeshComponent( Asset<Mesh> const & mesh );
	MeshComponent( MeshComponent const & cpy );
	virtual ~MeshComponent( void );

	MeshComponent &		operator=( MeshComponent const & rhs );

	virtual void		render( RenderEngine const & renderEngine, GameObject const & parent, Asset<Shader> const & shader, Camera const & camera ) const;
	virtual void		update( double delta );
	virtual void		init( CoreEngine & coreEngine ) {};

	//GETTER
	Asset<Mesh>			getMesh( void ) const;

private:
	void				draw( void ) const;

	Asset<Mesh>			_mesh;
};

#endif // ! _MESH_H_
