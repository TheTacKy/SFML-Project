#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
	#else
	return "C:/Users/ientr/OneDrive/Desktop/Prj/LightYears/LightYearsGame/assets/";
#endif
}
