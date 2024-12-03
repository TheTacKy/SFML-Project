#pragma once
#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	class VanguardStage : public GameStage
	{
	public:


		VanguardStage(World* world);
		virtual void StartStage() override;
	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;
		sf::Vector2f mSpawnLoc;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn;
		int mRowSpawnCount;

		int mVanguardsPerRow;
		int mCurrentRowVanguardCount;

		sf::Vector2f RandomSpawnLocation();
		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();
	};
}
