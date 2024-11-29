#include "Level/GameLevelOne.h"

#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/BackdropActor.h"
#include "framework/TimerManager.h"

#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"

#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/Hexagon.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "Enemy/ChaosStage.h"
#include "Enemy/BossStage.h"

#include "gameplay/WaitStage.h"
#include "gameplay/GameStage.h"

#include "widgets/GameplayHUD.h"
namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{owningApp}
	{
		
	}

	void GameLevelOne::AllGameStageFinished()
	{
		mGameplayHUD.lock()->GameFinished(true);
	}

	void GameLevelOne::BeginPlay()
	{
		SpawnCosmetics();
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
		mGameplayHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
		mGameplayHUD.lock()->onRestartButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::Restart);
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
		AddStage(shared<ChaosStage>{new ChaosStage{ this }});
		//AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		//AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		//AddStage(shared<WaitStage>{new WaitStage{ this, 10.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});

		AddStage(shared<UFOStage>{new UFOStage{ this }});

		AddStage(shared<BossStage>{new BossStage{this}});
	}

	void GameLevelOne::QuitGame()
	{
		GetApplication()->QuitApplication();
	}

	void GameLevelOne::Restart()
	{
		PlayerManager::Get().Reset();
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::GameOver()
	{
		mGameplayHUD.lock()->GameFinished(false);
	}

	void GameLevelOne::SpawnCosmetics()
	{
		auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
	}
}