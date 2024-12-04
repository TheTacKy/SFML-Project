# Light Years Game

### Intro

This is a 2d Alien Spaceship shooter game. You are a player Spaceship with a noble goal to defeat the alien invasion and boss.

Built using:
* [SFML](https://www.sfml-dev.org/) 
* [Box2D](https://box2d.org/)

  
Build:

Ensure yo uhave CMake version 3.16 and gcc/g++ installed
This game works on Windows and maybe Mac

1, Open the folder with command prompt, and configure with cmake:

cmake -S . -B build -G

2, Build with cmake:

cmake --build build

3, open the game:

./build/LightYearsGame/LightYearsGame.exe

### Components
LightYearsEngine

This project is build on top of SFML but also a minimal game engine which has the following implementations:

