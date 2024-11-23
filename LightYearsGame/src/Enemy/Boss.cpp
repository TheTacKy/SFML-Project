#include "Enemy/Boss.h"



namespace ly
{
	Boss::Boss(World* world)
		: EnemySpaceship{world, "SpaceShooterRedux/PNG/Enemies/boss.png" },
		mSpeed{100.f},
		mSwitchDistanceToEdge{100.f}

	{
		SetVelocity({ mSpeed, 0.f });
		SetActorRotation(90);
	}
	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		CheckMove();
	}
	void Boss::CheckMove()
	{
		if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge)
		{
			SetVelocity({ -mSpeed, 0.f });
		}
		else if (GetActorLocation().x < mSwitchDistanceToEdge)
		{
			SetVelocity({mSpeed, 0.f});
		}
	}
	void Boss::ShootBaseShooters()
	{
		mBaseShooterLeft.Shoot();
		mBaseShooterRight.Shoot();
	}
}