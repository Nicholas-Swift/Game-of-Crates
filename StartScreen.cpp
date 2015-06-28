#include "stdafx.h"
#include "StartScreen.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void StartScreen::setPosition(sf::RenderWindow &window)
{
	m_rect.setPosition(window.getView().getCenter().x - window.getSize().x/2, window.getView().getCenter().y - window.getSize().y/2);
	m_sprite.setPosition(window.getView().getCenter().x - window.getSize().x/2, window.getView().getCenter().y - window.getSize().y/2);
}

bool StartScreen::getDone()
{
	return m_done;
}

bool StartScreen::getDestroyed()
{
	return m_destroyed;
}

StartScreen::StartScreen()
{
	m_rect.setFillColor(sf::Color(207, 189, 134, 255));
	m_rect.setSize(sf::Vector2f(960, 640));

	m_texture.loadFromFile("Assets/startTexture.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

	m_timeOne = 2;
	m_timeTwo = 4;
	m_currentTime = 0;

	m_done = false;
	m_destroyed = false;
}

void StartScreen::Update(sf::Time &deltaTime)
{
	m_currentTime += deltaTime.asSeconds();

	//set which texture rect to have it on
	if(m_currentTime < m_timeOne)
	{
		if(m_sprite.getTextureRect() != sf::IntRect(0, 0, 960, 640))
			m_sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

		if(m_currentTime < 1)
			m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, m_currentTime*255));
		/*else if(m_currentTime > 1)
			m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, ));*/
	}

	else if(m_currentTime < m_timeTwo)
	{
		if(m_sprite.getTextureRect() != sf::IntRect(0, 640, 960, 640))
			m_sprite.setTextureRect(sf::IntRect(0, 640, 960, 640));

		if(m_currentTime < 3)
			m_sprite.setColor(sf::Color(m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, (m_currentTime - 2)*255));
	}

	else
		m_done = true;

	Destroy();
}

void StartScreen::Destroy()
{
	if(m_done == true)
	{
		m_destroyed = true;
		m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
		m_rect.setSize(sf::Vector2f(0, 0));
	}
}

void StartScreen::Draw(sf::RenderWindow &window)
{
	window.draw(m_rect);
	window.draw(m_sprite);
}