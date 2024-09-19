#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

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

	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::BeginPlay()
	{
		
	}

	void World::Tick(float deltaTime)
	{
		
	}
}