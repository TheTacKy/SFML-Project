#pragma once
#include <SFML/Graphics.hpp>
#include <framework/Core.h>
#include "framework/Actor.h"
namespace ly 
{
	class Actor;
	class Application;
	class World
	{
	public: 
		World(Application* owningApp);
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World();

		template<typename ActorType>
		weak<ActorType> SpawnActor();

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		Application* mOwningApp;
		bool mBeganPlay;

		List<shared<Actor>> mActors;

		List<shared<Actor>> mPendingActors;
	};
	


	template<typename ActorType>
	weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this} };
		mPendingActors.push_back(newActor);
		return newActor;
	}

}