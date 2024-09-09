#pragma once

namespace ly
{
	class World;
	class Actor
	{
	public:
		Actor(World* owningWorld);

		void BeginPlayInternal();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
	private:
		World* mOwningWorld;
		bool mHasBeganPlay;
	};
}