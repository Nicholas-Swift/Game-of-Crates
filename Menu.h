#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "BackgroundProcesses.h"
#include "Tilemap.h"

class Menu
{
private:
	sf::RenderWindow *m_window;
	Tilemap *m_tilemap;
	Player *m_player;

	bool m_menuUp;
	int m_state; //0 - main menu, 1 - in game menu, 2 - options
	int m_prevState;

	int m_mapLevel;

	sf::Texture m_titleTexture, m_buttonTexture;
	sf::Sprite m_title;

	std::vector<sf::RectangleShape> m_buttonsRect;
	std::vector<sf::Sprite> m_buttonsSprite;

	bool m_dragging; //for dragging on options (m_state 2)
	int m_dragNum;

	//save stuff
	int m_maxLevel, m_musicLevel, m_soundLevel, m_contrastLevel;

public:
	int getState();
	bool getMenuUp();
	void pressedEscape();
	void setWindow(sf::RenderWindow &window), setTilemap(Tilemap &tilemap), setPlayer(Player &player);

	void Load(), Save();

private:
	void PopulateZero(), PopulateOne(), PopulateTwo();
	void UpdateZero(), UpdateOne(), UpdateTwo();
	void ClickZero(), ClickOne(), ClickTwo();
	void ResizeZero(sf::Vector2f size), ResizeZero(), ResizeOne(sf::Vector2f size), ResizeOne(), ResizeTwo(sf::Vector2f size), ResizeTwo();

public:
	Menu();
	void Populate(int i), Update(BackgroundProcesses &b), Click(), Draw();
	void DragSet(), Drag(BackgroundProcesses &b);
	void setOptions(BackgroundProcesses &b);
	void Resize(sf::Vector2f size), Resize();
};

#endif