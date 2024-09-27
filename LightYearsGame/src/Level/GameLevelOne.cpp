#include "Level/GameLevelOne.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "framework/AssetManager.h"
#include "Enemy/Vanguard.h"
#include "framework/TimerManager.h"
#include "framework/Object.h"
namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{owningApp}
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceShip = SpawnActor<Vanguard>();
		testSpaceShip.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });

	}

	void GameLevelOne::BeginPlay()
	{

		TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallBack_Test, 10);
	}

	void GameLevelOne::TimerCallBack_Test()
	{
		LOG("Callback called");
	}
}