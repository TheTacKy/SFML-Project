#include "widgets/HUD.h"

namespace ly
{
	void HUD::NativeInit(sf::RenderWindow& windowRef)
	{
		if (!mAlreadyInit)
		{
			mAlreadyInit = true;
			Init(windowRef);
		}
	}

	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	HUD::HUD()
		: mAlreadyInit{false}
	{

	}

	void HUD::Init(const sf::RenderWindow& winderRef)
	{
		
	}
}