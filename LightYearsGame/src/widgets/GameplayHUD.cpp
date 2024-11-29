#include "widgets/GameplayHUD.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "framework/Actor.h"
namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFramerateText{"Frame Rate:"},
		mPlayerHealthBar{},
		mPlayerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" },
		mPlayerLifeText{ "" },
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerScoreText{ "" },
		mHealthyHealthBarColor{128, 255, 128, 255},
		mCriticalHealthBarColor{250, 0, 0, 255},
		mCriticalThreshold{0.3},
		mWidgetSpacing{10},
		mWinLoseText{""},
		mFinalScoreText{""},
		mRestartButton{"Restart"},
		mQuitButton{"Quit"},
		mWindowSize{}

	{
		mFramerateText.SetTextSize(30);
		mPlayerLifeText.SetTextSize(20);
		mPlayerScoreText.SetTextSize(20);

		mWinLoseText.SetVisibility(false);
		mFinalScoreText.SetVisibility(false);
		mRestartButton.SetVisibility(false);
		mQuitButton.SetVisibility(false);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mWindowSize = windowRef.getSize();
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);

		mWinLoseText.NativeDraw(windowRef);
		mFinalScoreText.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		mFramerateText.SetString(frameRateStr);
	}

	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		if (mRestartButton.HandleEvent(event)) return true;
		if (mQuitButton.HandleEvent(event)) return true;
		return HUD::HandleEvent(event);
	}
	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mWindowSize = windowSize;
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{20.f, windowSize.y - 55.f});
		sf::Vector2f nextWidgetPos = mPlayerHealthBar.GetWidgetLocation();

		nextWidgetPos += sf::Vector2f{ mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeIcon.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeText.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeText.GetBound().width + mWidgetSpacing * 4, -2.f };
		mPlayerScoreIcon.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerScoreText.SetWidgetLocation(nextWidgetPos);



		RefreshHealthBar();
		ConnectPlayerStatus();

		mWinLoseText.SetString("You Win!");
		mWinLoseText.SetTextSize(40);
		mWinLoseText.SetWidgetLocation({ windowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f, 100.f});


		mFinalScoreText.SetString("Score: ");
		mFinalScoreText.SetTextSize(40);
		mFinalScoreText.SetWidgetLocation({ windowSize.x / 2.f - mFinalScoreText.GetBound().width / 2.f, 200.f });



		mWinLoseText.SetWidgetLocation({ windowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f, 100.f });

		mRestartButton.SetWidgetLocation({ windowSize.x / 2.f - mRestartButton.GetBound().width / 2.f, windowSize.y / 2.f });
		mQuitButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 50.f });

		mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
		
	}
	void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth,maxHealth);
		if (currentHealth / maxHealth < mCriticalThreshold)
			mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
		else
			mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
	}

	void GameplayHUD::PlayerLifeCountUpdated(int amt)
	{
		mPlayerLifeText.SetString(std::to_string(amt));
	}

	void GameplayHUD::PlayerScoreUpdated(int newScore)
	{
		mPlayerScoreText.SetString(std::to_string(newScore));
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player && !player->GetCurrentSpaceship().expired())
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);
			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp();
			healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
			PlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::ConnectPlayerStatus()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			int lifeCount = player->GetLifeCount();
			mPlayerLifeText.SetString(std::to_string(lifeCount));
			player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);
			int playerScore = player->GetScore();
			mPlayerScoreText.SetString(std::to_string(playerScore));
			player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
		}
	}  

	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::RestartButtonClicked()
	{
		onRestartButtonClicked.Broadcast();
	}

	void GameplayHUD::QuitButtonClicked()
	{
		onQuitButtonClicked.Broadcast();
	}

	void GameplayHUD::GameFinished(bool playerWon)
	{
		mWinLoseText.SetVisibility(true);
		mFinalScoreText.SetVisibility(true);
		mRestartButton.SetVisibility(true);
		mQuitButton.SetVisibility(true);

		int score = PlayerManager::Get().GetPlayer()->GetScore();
		mFinalScoreText.SetString("score: " + std::to_string(score));

		if (playerWon)
		{
			mWinLoseText.SetString("You Win!");
		}
		else
		{
			mWinLoseText.SetString("You Lose!");

		}
		mWinLoseText.SetWidgetLocation({mWindowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f, 100.f});
		mFinalScoreText.SetWidgetLocation({ mWindowSize.x / 2.f - mFinalScoreText.GetBound().width / 2.f, 200.f });

	}
	
}