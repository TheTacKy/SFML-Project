#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class PlayerSpaceship;
	class World;
	class Player : public Object
	{
	public:
		Player();
		//passing world b/c word is where actors are spawned 
		weak<PlayerSpaceship> SpawnSpaceship(World* world);
		weak<PlayerSpaceship> GetCurrentSpaceship() const { return mCurrentPlayerSpaceship; };

		void AddLifeCount(unsigned int count);
		int GetLifeCount() const { return mLifeCount; }
		void AddScore(unsigned int amt);
		int GetScore() const { return mScore; }

		//for the players UI
		Delegate<int> onLifeChange;
		Delegate<int> onScoreChange;
		Delegate<> onLifeExhausted;
	private:

		unsigned int mLifeCount;
		unsigned int mScore;
		weak<PlayerSpaceship> mCurrentPlayerSpaceship;

	};
}