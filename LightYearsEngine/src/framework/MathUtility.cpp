#include "framework/MathUtility.h"

namespace ly
{
	const float PI = 3.1415926535;

	sf::Vector2f ly::RotationToVector(float rotation)
	{
		//cos gives x cords and sin y cords
		float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	//trig
	float DegreesToRadians(float degrees)
	{
		return degrees * (PI/180.f);
	}

	float RadiansToDegrees(float radians)
	{
		return radians * (180.f/PI);
	}
}