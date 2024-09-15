#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
namespace ly {
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningWorld{owningWorld},
		mHasBeganPlay{ false },
		mSprite{},
		mTexture{}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor() {
		LOG("Actor Destroyed");
	}
	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganPlay) {
			mHasBeganPlay = true;
			BeginPlay();
		}
	}
	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy()) {
			Tick(deltaTime);
		}
	}
	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}
	void Actor::Tick(float deltaTime)
	{
		LOG("Actor Ticking");
	}
	void Actor::SetTexture(const std::string& texturePath)
	{
		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect(sf::Vector2i{}, sf::Vector2i{ textureWidth, textureHeight}));
	}
	void Actor::Render(sf::RenderWindow& window)
	{
		window.draw(mSprite);
	}
}