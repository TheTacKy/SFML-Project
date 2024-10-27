#include "widgets/Widget.h"

namespace ly
{
	Widget::Widget()
		: mIsVisible{true},
		mWidgetTransform{}
	{

	}

	void Widget::NativeDraw(sf::RenderWindow& windowRef)
	{
		if (mIsVisible)
		{
			Draw(windowRef);
		}
	}
	bool Widget::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	//Implementation of Tranformable Functions
	void Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
	{
		mWidgetTransform.setPosition(newLocation);
		LocationUpdated(newLocation);
	}

	void Widget::SetWidgetRotation(float newRotation)
	{
		mWidgetTransform.setRotation(newRotation);
		RotationUpdated(newRotation);
	}

	void Widget::SetVisibility(bool newVisibility)
	{
		mIsVisible = newVisibility;
	}

	void Widget::Draw(sf::RenderWindow& windowRef)
	{
	}

	void Widget::LocationUpdated(const sf::Vector2f& newLocation)
	{

	}

	void Widget::RotationUpdated(const float newRotation)
	{

	}
	
}