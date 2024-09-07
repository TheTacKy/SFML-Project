#include "framework/Application.h"
#include "framework/Core.h"

namespace ly {
	Application::Application()
		: mWindow{ sf::VideoMode(1014, 1440), "MyWindow" },
		mTargetFrameRate(60.f),
		mTickClock{}
	{

	}
	void Application::Run() {
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFrameRate;
		while (mWindow.isOpen()) 
			{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent)) 
			{
				if (windowEvent.type == sf::Event::EventType::Closed) 
				{
					mWindow.close();
				}
			}
			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += mTickClock.restart().asSeconds();
			while(accumulatedTime > targetDeltaTime) 
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
			LOG("ticking at framerate: %f\n", 1.f / frameDeltaTime);
		}
	}
	

	void Application::TickInternal(float deltaTime) {
		Tick(deltaTime);
	}


	void Application::RenderInternal() {
		mWindow.clear();

		Render();
		
		mWindow.display();
	}

	void Application::Render() {
		sf::RectangleShape rect{ sf::Vector2f{100, 100} };
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(50, 50);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);

		mWindow.draw(rect);
	}
	void Application::Tick(float deltaTime) {

	}
} 
