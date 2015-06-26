#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SFML/Graphics.hpp>

class StartScreen
{
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	int m_timeOne, m_timeTwo;
	sf::Time m_currentTime;

	bool m_done;

public:
	sf::Sprite getSprite();
	sf::Texture getTexture();
	int getTimeOne(), getTimeTwo();
	sf::Time getCurrentTime();
	bool getDone();

public:
	StartScreen();
	void Update();
	void Draw(sf::RenderWindow &window);
};

#endif