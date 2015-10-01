#ifndef CRATE_H
#define CRATE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Crate
{
private:
	sf::RectangleShape m_rect;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;

	float m_top, m_bottom, m_left, m_right;
	sf::Vector2f m_movement;
	float m_gravity;

	bool m_onGround, m_onCrate, m_onLeft, m_onRight;

public:
	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetSize(), getMovement();
	float getTop(), getBottom(), getLeft(), getRight();
	bool getOnLeft(), getOnRight(), getOnCrate();
	void setOnCrate();
	void CrateCollide(float top, float bottom, float left, float right);

public:
	Crate();
	void Update(sf::RenderWindow &window, sf::Time &deltaTime, int map[50][50], std::vector<Platform> &p);
	void Draw(sf::RenderWindow &window);
};

#endif