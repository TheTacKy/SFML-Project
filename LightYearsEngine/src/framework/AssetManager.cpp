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
		return LoadAsset(path, mLoadedTextureMap);
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		return LoadAsset(path, mLoadedFontMap);
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
		CleanUniqueRef(mLoadedFontMap);
		CleanUniqueRef(mLoadedTextureMap);
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		mRootDirectory = directory;
	}

	AssetManager::AssetManager() : mRootDirectory{}
	{

	}

}