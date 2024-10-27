#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/World.h"

namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		:Actor{world, texturePath},
		mRewardFunc{rewardFunc},
		mSpeed{speed}
	{

	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({0.f, mSpeed * deltaTime});
	}

	void Reward::OnActorBeginOverlap(Actor* otherActor)
	{
		//TODO: clean up casting.
		PlayerSpaceship* playerSpaceship = dynamic_cast<PlayerSpaceship*>(otherActor);
		if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
		{
			mRewardFunc(playerSpaceship);
			Destroy();
		}
		
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreewayShooter(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreewayShooter);
	}

	weak<Reward> CreateFrontalWiper(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
	}

	
	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmt = 10.f;
		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComp().ChangeHealth(rewardAmt);
		}
	}

	void RewardThreewayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.4, {50.f, 0.f} }});
		}
	}

	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new FrontalWiper{ player, 0.4, {50.f, 0.f} }});
		}
	}

}