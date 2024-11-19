#include "gameFramework/gameApplication.h"
#include "Level/MainMenuLevel.h"
#include "Level/GameLevelOne.h"
#include "framework/AssetManager.h"
#include "config.h"

ly::Application* GetApplication() 
{
	return new ly::GameApplication;
}

namespace ly 
{
	GameApplication::GameApplication()
		: Application {600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		//Calls the config file to set up Asset directory
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
	}

	
}