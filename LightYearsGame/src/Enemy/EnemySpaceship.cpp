#include "Enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage, float rewardSpawnWeight, const List<RewardFactoryFunc> rewards)
		:Spaceship{ owningWorld, texturePath }, 
		mCollisionDamage{ collisionDamage },
		mRewardFactories{rewards},
		mScoreAwardAmt{},
		mRewardSpawnWeight{rewardSpawnWeight}
	{
		SetTeamID(2);
		SetScoreAwardAmt(10);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
		{
			Destroy();
		}
	}

	//updates Score
	void EnemySpaceship::SetScoreAwardAmt(unsigned int amt)
	{
		mScoreAwardAmt = amt;
	}

	void EnemySpaceship::SetRewardSpawnWeight(float weight)
	{
		if (weight < 0 || weight > 1)
		{
			return;
		}
		mRewardSpawnWeight = weight;
	}

	//handles rewards
	void EnemySpaceship::SpawnReward()
	{
		if (mRewardFactories.size() == 0) return;

		if (mRewardSpawnWeight < RandomRange(0, 1))
			return;

		int pick = (int)RandomRange(0, mRewardFactories.size());
		if (pick >= 0 && pick < mRewardFactories.size())
		{
			weak<Reward> newReward = mRewardFactories[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}
	}

	//Collision dmg
	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(mCollisionDamage);
		}
		
		
	}

	//when enemy dies spawn a reward and add AddScore
	void EnemySpaceship::Blew()
	{
		SpawnReward();
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			player->AddScore(mScoreAwardAmt);
		}
	}
}