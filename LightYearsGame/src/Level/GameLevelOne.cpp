#include "Level/GameLevelOne.h"

#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"

#include "framework/AssetManager.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/TimerManager.h"

#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/Hexagon.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"

#include "gameplay/WaitStage.h"
#include "gameplay/GameStage.h"

#include "widgets/GameplayHUD.h"
namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{owningApp}
	{
		
	}

	void GameLevelOne::BeginPlay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
		if (!mPlayerSpaceship.expired())
		{
			mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::InitGameStages()
	{

		//AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 10.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});

		AddStage(shared<UFOStage>{new UFOStage{ this }});
	}

	void GameLevelOne::GameOver()
	{
		LOG("GAME OVER! =============================================================");
	}
}