#include "StartScreen.h"
#include <iostream>
#include <SFML/Graphics.hpp>

StartScreen::StartScreen()
{
	m_texture.loadFromFile("Assets/startTexture.jpg");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

	m_timeOne = 2;
	m_timeTwo = 4;

	m_done = false;
}

void StartScreen::Update()
{
	//set which texture rect to have it on
	if(m_currentTime.asSeconds() < m_timeOne)
		if(m_sprite.getTextureRect() != sf::IntRect(0, 0, 960, 640))
			m_sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

	else if(m_currentTime.asSeconds() < m_timeTwo)
		if(m_sprite.getTextureRect() != sf::IntRect(0, 640, 960, 640))
			m_sprite.setTextureRect(sf::IntRect(0, 640, 960, 640));


}

void StartScreen::Draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}