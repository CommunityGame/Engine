#include "Factories.hpp"
#include "SoundFactory.hpp"
#include "../assets/AssetsManager.hpp"
#include "../render/Mesh.hpp"
#include "MeshFactory.hpp"
#include "ShaderFactory.hpp"

void	Factories::registerFactories( void )
{
	AssetsManager::addFactory<Sound, SoundFactory>();
	AssetsManager::addFactory<Mesh, MeshFactory>();
	AssetsManager::addFactory<Shader, ShaderFactory>();
}
