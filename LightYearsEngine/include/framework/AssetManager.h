#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	//singleton
	class AssetManager
	{
	public:
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& path);
		void UnloadTexture(const std::string& path);
		//clean assets we dont need anymore
		void CleanCycle();
		void SetAssetRootDirectory(const std::string& directory);
	protected:
		AssetManager();
	private:
		static unique<AssetManager> assetManager;
		Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
		std::string mRootDirectory;
	};
}