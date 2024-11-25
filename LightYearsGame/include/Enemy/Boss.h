#pragma once
#include "Enemy/EnemySpaceship.h"

#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
namespace ly
{
	class BulletShooter;
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);
		virtual void Tick(float deltaTime)override;
		virtual void BeginPlay() override;
	private:
		float mSpeed;
		float mSwitchDistanceToEdge;

		void CheckMove();

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;

		ThreeWayShooter mThreeWayShooter;

		FrontalWiper mFrontalWiperLeft;
		FrontalWiper mFrontalWiperRight;
		
		BulletShooter mFinalStageShooterLeft;
		BulletShooter mFinalStageShooterRight;
		
		void ShootBaseShooters();
		void ShootThreeWayShooters();
		void ShootFrontalWipers();

		//leveling system
		void SetStage(int newStage);
		int mStage;
		void HealthChanged(float amt, float currentHealth, float maxHealth);

	};
}