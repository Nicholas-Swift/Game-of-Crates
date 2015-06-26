#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform
{
private:
	//classic static platform
	sf::RectangleShape m_rect;

	sf::Vector2f m_size;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	float m_top, m_bottom, m_left, m_right;
	
	//for dynamic movement
	float m_posMaxOne, m_posMaxTwo, m_posMaxFinal;
	float m_movSpeedAddition, m_movSpeedMax;
	sf::Vector2f m_movement;
	bool m_isMovingRight, m_isMovingLeft;

public:
	float getTop(), getBottom(), getLeft(), getRight();
	sf::Vector2f getMovement();

public:
	Platform(int left, int right, sf::Vector2f position);
	void Update(); //only for dynamic movement
	void Move(sf::Time &deltaTime);
	void Draw(sf::RenderWindow &window);
};

#endif