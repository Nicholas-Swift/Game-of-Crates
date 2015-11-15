#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "BackgroundProcesses.h"
#include "Tilemap.h"
#include "Player.h"
#include "Menu.h"
#include "StartScreen.h"

class Game
{
public:
	Game();
	void run();

	//void runClock(), run1(), run2(), run3(), run4(), run5();

private:
	void processEvents();
	void update(sf::Time);
	void render();

	//void update1(sf::Time), update2(sf::Time), update3(sf::Time), update4(sf::Time);

private:
	sf::RenderWindow m_window;
	sf::View m_view;

	BackgroundProcesses m_backgroundProcesses;
	Tilemap m_tilemap;
	Player m_player;
	Menu m_menu;
	StartScreen m_startScreen;
};

#endif