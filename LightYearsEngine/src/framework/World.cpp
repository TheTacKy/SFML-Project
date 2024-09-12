#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
namespace ly {
	World::World(Application* owningApp)
		:mOwningApp{owningApp},
		mBeganPlay{ false },
		mActors{},
		mPendingActors{}
	{

	}
	World::~World() {
		// Clean up any resources here if needed
	}
	void World::BeginPlayInternal()
	{
		if (!mBeganPlay) 
		{
			mBeganPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors) {
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}

		mPendingActors.clear();

		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				iter->get()->Tick(deltaTime);
				++iter;
			}
		}

		
		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}
	}

	void World::BeginPlay()
	{
		LOG("began play");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Tick at frame rate %f", 1.f/deltaTime);
	}
}