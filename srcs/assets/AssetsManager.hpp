#ifndef _ASSETS_MANAGER_HPP_
# define _ASSETS_MANAGER_HPP_

#include <typeindex>
#include <unordered_map>
#include "Asset.hpp"
#include "../factories/IFactory.hpp"
#include "../EngineException.hpp"
#include "../debugs/Logger.hpp"

class AssetsManager
{
public:
	template <typename T, typename U,
			typename = typename std::enable_if<std::is_base_of<IAsset, T>::value, T>::type,
			typename = typename std::enable_if<std::is_base_of<IFactory, U>::value, U>::type>
	static bool				addFactory( void )
	{
		std::type_index ti = std::type_index( typeid( T ) );

		std::unordered_map<std::type_index, t_loader>::iterator it = AssetsManager::_factories.find( ti );
		if ( it != AssetsManager::_factories.end() )
			return ( false );

		t_loader const & factoryLoader = U().getLoader();

		AssetsManager::_factories.insert( std::pair<std::type_index, t_loader>( ti, factoryLoader ) );
		return ( true );
	}

	template<typename T>
	static Asset<T> const &		loadAsset( std::string const & path, std::string const & uidName )
	{
		std::type_index	ti = std::type_index( typeid( T ) );

		std::unordered_map<std::type_index, t_loader>::iterator it = AssetsManager::_factories.find( ti );

		if ( it == AssetsManager::_factories.end() )
			throw EngineException( std::string( "No registered factory of type " ) + ti.name() );

		t_loader f = it->second;

		shared_ptr<T>	ptr = static_pointer_cast<T>( f( path ) );
		std::string name = uidName;
		if ( name == "" )
			name = path;
		Asset<T> *		asset = new Asset<T>( ptr, name );

		AssetsManager::_assetsByUidName.insert( std::pair<std::string, void *>( asset->getUidName(), asset ) );
		AssetsManager::_assetsByUid.insert( std::pair<int, void *>( asset->getUid(), asset ) );

		return ( * asset );
	}

	template<typename T>
	static Asset<T> const &		getAssetByUidName( std::string const & uidName )
	{
		std::unordered_map<std::string, void *>::const_iterator it;

		it = AssetsManager::_assetsByUidName.find( uidName );
		if ( it == AssetsManager::_assetsByUidName.end() )
			Logger::e( TAG, "Can't find asset: " + uidName );

		Asset<T> *		asset = static_cast<Asset<T> *>( it->second );
		return ( * asset );
	}

	template<typename T>
	static Asset<T> const &		getAssetByUid( int uid )
	{
		std::unordered_map<int, void *>::const_iterator it;

		it = AssetsManager::_assetsByUid.find( uid );
		if ( it == AssetsManager::_assetsByUid.end() )
			Logger::e( TAG, "Can't find asset: " + uid );

		Asset<T> *		asset = static_cast<Asset<T> *>( it->second );
		return ( * asset );
	}

private:
	static std::unordered_map<std::string, void *>		_assetsByUidName;
	static std::unordered_map<int, void *>				_assetsByUid;
	static std::unordered_map<std::type_index, t_loader>	_factories;

	static const std::string	TAG;
};

#endif // ! _ASSETS_MANAGER_HPP_
