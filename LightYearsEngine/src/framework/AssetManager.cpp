#include "framework/AssetManager.h"

namespace ly
{
	unique<AssetManager> AssetManager::assetManager{nullptr};

	AssetManager& AssetManager::Get()
	{
		if (!assetManager)
		{
			assetManager = std::move(unique<AssetManager>{new AssetManager});
		}
		return *assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		//use the dictionary/map to see if we already have the asset loaded
		auto found = mLoadedTextureMap.find(path);
		if (found != mLoadedTextureMap.end())
		{
			//return texture if found
			return found->second;
		}
		shared<sf::Texture> newTexture{new sf::Texture};
		if (newTexture->loadFromFile(mRootDirectory + path)) 
		{
			mLoadedTextureMap.insert({path, newTexture});
			return newTexture;
		}
		return shared<sf::Texture> {nullptr};
	}

	void AssetManager::UnloadTexture(const std::string& path)
	{
		auto found = mLoadedTextureMap.find(path);
		if (found != mLoadedTextureMap.end())
		{
			if (found->second.unique())
			{
				LOG("unloading texture: %s", path.c_str());
				mLoadedTextureMap.erase(found);
			}
		}
	}

	void AssetManager::CleanCycle()
	{
		
		for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
		{
			if(iter->second.unique())
			{ 
				LOG("cleaning texture: %s", iter->first.c_str());
				iter = mLoadedTextureMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		mRootDirectory = directory;
	}

	AssetManager::AssetManager() : mRootDirectory{}
	{

	}

}