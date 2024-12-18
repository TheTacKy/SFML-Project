#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, 
			float cooldownTime = 0.7f, 
			const sf::Vector2f& localPositionOffset = {0.f, 0.f}, 
			float localRotationOffset = 0.f,
			const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
			);
		virtual bool IsOnCooldown() const override;
		virtual void IncrementLevel(int amt = 1) override;
		void ResetCooldown();
		void SetDamage(float newDamage);

		void SetBulletTexturePath(const std::string& BulletTexturePath);
	private:
		
		virtual void ShootImpl() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mBulletTexturePath;
	};
}