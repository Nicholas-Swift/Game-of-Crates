#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SFML/Graphics.hpp>

class StartScreen
{
private:
	sf::RectangleShape m_rect;

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	int m_timeOne, m_timeTwo;
	float m_currentTime;

	bool m_done, m_destroyed;

public:
	void setPosition(sf::RenderWindow &window);
	bool getDone(), getDestroyed();

public:
	StartScreen();
	void Update(sf::Time &deltaTime);
	void Destroy();
	void Draw(sf::RenderWindow &window);
};

#endif