#include "weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width)
		: Shooter{ owner },
		mWidth{},
		mShooter1{ owner, cooldownTime, {localOffset.x, localOffset.y - width/2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/LaserGreen11.png"},
		mShooter2{ owner, cooldownTime, {localOffset.x, localOffset.y - width/6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/LaserBlue07.png"},
		mShooter3{ owner, cooldownTime, {localOffset.x, localOffset.y + width/6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/LaserBlue07.png"},
		mShooter4{ owner, cooldownTime, {localOffset.x, localOffset.y + width/2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/LaserGreen11.png"},
		mShooter5{ owner, cooldownTime/1.5f, {localOffset.x, localOffset.y + width/1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/LaserGreen11.png"},
		mShooter6{ owner, cooldownTime/1.5f, {localOffset.x, localOffset.y - width/1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/LaserGreen11.png"}
	{
	}

	void FrontalWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooter1.IncrementLevel(amt);
		mShooter2.IncrementLevel(amt);
		mShooter3.IncrementLevel(amt);
		mShooter4.IncrementLevel(amt);

	}

	void FrontalWiper::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);
		mShooter1.SetCurrentLevel(level);
		mShooter2.SetCurrentLevel(level);
		mShooter3.SetCurrentLevel(level);
		mShooter4.SetCurrentLevel(level);
	}

	void FrontalWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();
		if (GetCurrentLevel() == GetMaxLevel())
		{
			mShooter5.Shoot();
			mShooter6.Shoot();
		}
	}
} 