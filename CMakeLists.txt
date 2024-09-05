cmake_minimum_required(VERSION 3.16)

project(LightYears VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS	   OFF)

#creates a variable
#big balls love balls
set(LIGHT_YEARS_GAME_TARGET_NAME LightYearsGame)

add_subdirectory(LightYears)
