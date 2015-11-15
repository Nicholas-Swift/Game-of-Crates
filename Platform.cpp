#include "stdafx.h"
#include <iostream>
#include "Platform.h"
#include "FileStream.h"

float Platform::getTop()
{
	return m_top;
}

float Platform::getBottom()
{
	return m_bottom;
}

float Platform::getLeft()
{
	return m_left;
}

float Platform::getRight()
{
	return m_right;
}

sf::Vector2f Platform::getMovement()
{
	return m_movement;
}

Platform::Platform(int left, int right, sf::Vector2f position)
{
	m_size = sf::Vector2f(64, 64);

	m_rect.setSize(sf::Vector2f(m_size.x * 3, m_size.y));
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setPosition(position);

	m_texture1.loadFromFile("Assets/tilemapsand.png");
	m_texture2.loadFromFile("Assets/tilemapforrest.png");
	m_texture3.loadFromFile("Assets/tilemapsnow.png");

	m_sprite.setTexture(m_texture1);
	m_sprite.setTextureRect(sf::IntRect(0, 5*64, m_size.x*3, m_size.y));
	m_sprite.setPosition(position);

	m_posMaxOne = left + 22; //to give leeway
	m_posMaxTwo = right - 22;
	m_posMaxFinal = m_posMaxOne; //this changes so the platform changes direction

	m_movSpeedAddition = 0.00005;
	m_movSpeedMax = 0.045;
	m_isMovingLeft = m_isMovingRight = false;
	m_movement = sf::Vector2f(0, 0);

	m_top = m_rect.getPosition().y;
	m_bottom = m_rect.getPosition().y + m_rect.getSize().y;
	m_left = m_rect.getPosition().x;
	m_right = m_rect.getPosition().x + m_rect.getSize().x;
}

void Platform::Update()
{
	m_top = m_rect.getPosition().y;
	m_bottom = m_rect.getPosition().y + m_rect.getSize().y;
	m_left = m_rect.getPosition().x;
	m_right = m_rect.getPosition().x + m_rect.getSize().x;
}

void Platform::UpdateTexture(int i)
{
	if(i < 5)
		m_sprite.setTexture(m_texture1);
	else if(i < 10)
		m_sprite.setTexture(m_texture2);
	else
		m_sprite.setTexture(m_texture3);
}

void Platform::Move(sf::Time &deltaTime)
{
	//find the correct bools
	if(m_left > m_posMaxFinal)
		m_isMovingLeft = true;
	else
	{
		m_isMovingLeft = false;
		m_posMaxFinal = m_posMaxTwo;
	}

	if((m_right - m_size.x) < m_posMaxFinal)
		m_isMovingRight = true;
	else
	{
		m_isMovingRight = false;
		m_posMaxFinal = m_posMaxOne;
	}

	//turn bools into floats
	if(m_isMovingLeft)
		m_movement.x -= m_movSpeedAddition * deltaTime.asMilliseconds();
	if(m_isMovingRight)
		m_movement.x += m_movSpeedAddition * deltaTime.asMilliseconds();

	//don't go over max
	if(m_movement.x >= m_movSpeedMax)
		m_movement.x = m_movSpeedMax;
	if(m_movement.x <= -m_movSpeedMax)
		m_movement.x = -m_movSpeedMax;

	m_rect.move(m_movement);
	m_sprite.move(m_movement);
}

void Platform::Draw(sf::RenderWindow &window)
{
	//window.draw(m_rect);
	window.draw(m_sprite);
}