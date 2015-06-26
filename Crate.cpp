#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Crate.h"
#include "Platform.h"

void Crate::SetPosition(sf::Vector2f pos)
{
	if(!m_onLeft && !m_onRight)
	{
		m_rect.setPosition(pos);
		m_sprite.setPosition(pos);
	}
	else if(m_onLeft == true && pos.x < m_rect.getPosition().x)
	{}
	else if(m_onRight == true && pos.x > m_rect.getPosition().x)
	{}
}

bool Crate::getOnLeft()
{
	return m_onLeft;
}

bool Crate::getOnRight()
{
	return m_onRight;
}

bool Crate::getOnCrate()
{
	return m_onCrate;
}

sf::Vector2f Crate::GetSize()
{
	return m_rect.getSize();
}

float Crate::getTop()
{
	return m_top;
}

float Crate::getBottom()
{
	return m_bottom;
}

float Crate::getLeft()
{
	return m_left;
}

float Crate::getRight()
{
	return m_right;
}

sf::Vector2f Crate::getMovement()
{
	return m_movement;
}

void Crate::CrateCollide(float top, float bottom, float left, float right)
{
	m_onCrate = false;

	if(m_top == top && m_bottom == bottom && m_left == left && m_right == right) //same crate
	{}
	else if(m_right < left || m_left > right || m_top > bottom || m_bottom < top) //not touching
	{}
	else if(m_bottom >= top && m_bottom - 2 <= top) //above crate
		m_onCrate = true;
	else if(bottom >= m_top && bottom - 2 <= m_top) //below crate
	{}
	else if(m_right >= left && m_left < left) //touching left
		m_onLeft = true;
	else if(m_left <= right && m_left > left) //touching right
		m_onRight = true;
}

Crate::Crate()
{
	m_size = sf::Vector2f(40, 40);
	
	m_rect.setSize(m_size);
	m_rect.setFillColor(sf::Color::Blue);
	m_rect.setPosition(0, 0);

	m_texture.loadFromFile("Assets/Crate.png");
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
	m_sprite.setScale(m_size.x / m_texture.getSize().x, m_size.y / m_texture.getSize().y);

	m_top = m_rect.getPosition().y;
	m_bottom = m_rect.getPosition().y + m_rect.getSize().y;
	m_left = m_rect.getPosition().x;
	m_right = m_rect.getPosition().x + m_rect.getSize().x;

	m_onGround = false;
	m_movement = sf::Vector2f(0, 0);
	m_gravity = 0.388;

	m_onCrate = m_onRight = m_onLeft = false;
}

void Crate::Update(sf::Time &deltaTime, int map[50][50], std::vector<Platform> &p)
{
	m_top = m_rect.getPosition().y;
	m_bottom = m_rect.getPosition().y + m_rect.getSize().y;
	m_left = m_rect.getPosition().x;
	m_right = m_rect.getPosition().x + m_rect.getSize().x;

	//if on tile
	if(m_bottom / 64 < 0 || m_right < 0)
		m_onGround = false;
	else if(int(m_bottom) % 64 != 0)
		m_onGround = false;
	else if( (map[int(m_bottom)/64][int(m_left)/64] >= 100 && map[int(m_bottom)/64][int(m_left)/64] < 200) || (map[int(m_bottom)/64][int(m_left)/64] >= 500 && map[int(m_bottom)/64][int(m_left)/64] < 600) || (map[int(m_bottom)/64][int(m_right)/64] >= 100 && map[int(m_bottom)/64][int(m_right)/64] < 200) || (map[int(m_bottom)/64][int(m_right)/64] >= 500 && map[int(m_bottom)/64][int(m_right)/64] < 600) )
		m_onGround = true;
	else
		m_onGround = false;

	//if on platform
	for(int i = 0; i < p.size(); i++)
	{
		if(m_right < p[i].getLeft() || m_left > p[i].getRight() || m_top > p[i].getBottom() || m_bottom < p[i].getTop())
		{}
		else if(int(m_bottom) == p[i].getTop())
			m_onGround = true;
	}

	//don't move left or right if colliding with wall
	if(int(m_bottom) % 64 == 0 && (map[int(m_bottom + 2)/64][int(m_left)/64] == 192 || map[int(m_bottom + 2)/64][int(m_left)/64] == 191 || map[int(m_bottom+2)/64][int(m_right)/64] == 191 || map[int(m_bottom+2)/64][int(m_right)/64] == 190 || map[int(m_bottom+2)/64][int(m_left)/64] == 192 || map[int(m_bottom+2)/64][int(m_left)/64] == 592 || map[int(m_bottom+2)/64][int(m_left)/64] == 591 || map[int(m_bottom+2)/64][int(m_right)/64] == 591 || map[int(m_bottom+2)/64][int(m_right)/64] == 590))
		{}
	else if((map[int(m_bottom)/64][int(m_left)/64] == 192 || map[int(m_bottom)/64][int(m_left)/64] == 292 || map[int(m_bottom)/64][int(m_left)/64] == 392 || map[int(m_bottom)/64][int(m_left)/64] == 490 || map[int(m_bottom)/64][int(m_left)/64] == 592 || map[int(m_bottom)/64][int(m_left)/64] == 191 || map[int(m_bottom)/64][int(m_left)/64] == 291 || map[int(m_bottom)/64][int(m_left)/64] == 391 || map[int(m_bottom)/64][int(m_left)/64] == 491 || map[int(m_bottom)/64][int(m_left)/64] == 591))
		m_onLeft = true;
	else if((map[int(m_bottom)/64][int(m_right)/64] == 190 || map[int(m_bottom)/64][int(m_right)/64] == 290 || map[int(m_bottom)/64][int(m_right)/64] == 390 || map[int(m_bottom)/64][int(m_right)/64] == 492 || map[int(m_bottom)/64][int(m_right)/64] == 590 || map[int(m_bottom)/64][int(m_right)/64] == 191 || map[int(m_bottom)/64][int(m_right)/64] == 291 || map[int(m_bottom)/64][int(m_right)/64] == 391 || map[int(m_bottom)/64][int(m_right)/64] == 491 || map[int(m_bottom)/64][int(m_right)/64] == 591))
		m_onRight = true;
	else if((map[int(m_top + 2)/64][int(m_left)/64] == 192 || map[int(m_top + 2)/64][int(m_left)/64] == 292 || map[int(m_top + 2)/64][int(m_left)/64] == 392 || map[int(m_top + 2)/64][int(m_left)/64] == 490 || map[int(m_top + 2)/64][int(m_left)/64] == 592 || map[int(m_top + 2)/64][int(m_left)/64] == 191 || map[int(m_top + 2)/64][int(m_left)/64] == 291 || map[int(m_top + 2)/64][int(m_left)/64] == 391 || map[int(m_top + 2)/64][int(m_left)/64] == 491 || map[int(m_top + 2)/64][int(m_left)/64] == 591))
		m_onLeft = true;
	else if((map[int(m_top + 2)/64][int(m_right)/64] == 190 || map[int(m_top + 2)/64][int(m_right)/64] == 290 || map[int(m_top + 2)/64][int(m_right)/64] == 390 || map[int(m_top + 2)/64][int(m_right)/64] == 492 || map[int(m_top + 2)/64][int(m_right)/64] == 590 || map[int(m_top + 2)/64][int(m_right)/64] == 191 || map[int(m_top + 2)/64][int(m_right)/64] == 291 || map[int(m_top + 2)/64][int(m_right)/64] == 391 || map[int(m_top + 2)/64][int(m_right)/64] == 491 || map[int(m_top + 2)/64][int(m_right)/64] == 591))
		m_onRight = true;
	else
		m_onLeft = m_onRight = false;

	//moving on platform
	for(int i = 0; i < p.size(); i++)
	{
		//not touching
		if(m_right < p[i].getLeft() || m_left > p[i].getRight() || m_top > p[i].getBottom() || m_bottom < p[i].getTop())
		{}

		else if(m_left > p[i].getLeft() && m_right < p[i].getRight())
			m_movement.x = p[i].getMovement().x;

		else if( m_left < p[i].getLeft() && (m_left + m_right)/2 > p[i].getLeft())
			m_movement.x = p[i].getMovement().x;

		else if( m_right > p[i].getRight() && (m_left + m_right)/2 < p[i].getRight())
			m_movement.x = p[i].getMovement().x;

		else
			m_movement.x = 0;
	}

	if(m_onCrate == true)
		m_onGround = true;

	//else, fall
	if(!m_onGround)
		m_movement.y += m_gravity * 0.003 * deltaTime.asMilliseconds();
	else
		m_movement.y = 0;

	//don't fall too fast!
	if(m_movement.y > 0.35)
		m_movement.y = 0.35; 

	m_rect.move(m_movement.x, m_movement.y);
	m_sprite.move(m_movement.x, m_movement.y);
}

void Crate::Draw(sf::RenderWindow &window)
{
	//window.draw(m_rect);
	window.draw(m_sprite);
}