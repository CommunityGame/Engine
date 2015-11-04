#include "AssetsManager.hpp"

const std::string	AssetsManager::TAG = "AssetsManager";

std::unordered_map<std::string, void *>		AssetsManager::_assetsByUidName;
std::unordered_map<int, void *>				AssetsManager::_assetsByUid;
std::unordered_map<std::type_index, t_loader>	AssetsManager::_factories;
