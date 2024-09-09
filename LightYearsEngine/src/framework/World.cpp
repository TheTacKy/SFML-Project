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

		for (shared<Actor> actor : mActors)
		{
			actor->Tick(deltaTime);
		}

		
		Tick(deltaTime);
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