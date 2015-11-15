#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"
#include "BackgroundProcesses.h"
#include "Tilemap.h"

const sf::Vector2f WINDOW_SIZE(960, 640);

int Menu::getState()
{
	return m_state;
}

int Menu::getPrevState()
{
	return m_prevState;
}

bool Menu::getMenuUp()
{
	return m_menuUp;
}

void Menu::pressedEscape()
{
	Resize();

	if(m_state == 0 && m_menuUp == true)
	{}
	else if(m_state == 0 && m_menuUp == false)
	{
		PopulateOne();
		m_menuUp = true;
	}
	else if(m_state == 1)
	{
		if(m_menuUp)
			m_menuUp = false;
		else
			m_menuUp = true;
	}
	else if(m_state == 2)
	{
		if(m_menuUp)
			m_menuUp = false;
		else
		{
			PopulateOne();
			m_menuUp = true;
		}
	}
}

void Menu::setWindow(sf::RenderWindow &window)
{
	m_window = &window;
}

void Menu::setTilemap(Tilemap &tilemap)
{
	m_tilemap = &tilemap;
}

void Menu::setPlayer(Player &player)
{
	m_player = &player;
}

void Menu::setSoundLevel(int i)
{
	if(i <= 0)
		m_sound.setVolume(0);
	else
		m_sound.setVolume(i/1.2);
}

void Menu::PopulateZero() //Main Menu
{
	//clear everything first
	m_buttonsRect.clear();
	m_buttonsSprite.clear();

	//title
	m_title.setTextureRect(sf::IntRect(0, 0, 570, 57));
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50);

	m_state = 0; //set state

	//title and tilemap
	m_tilemap->setMap(-1, *m_window);
	m_player->setPosition(sf::Vector2f(0, 0));

	//set up levels rect and sprite
	for(int i = 0; i < 15; i++) //levels
	{
		//rect
		sf::RectangleShape *rect = new sf::RectangleShape;
		rect->setFillColor(sf::Color::Red);
		rect->setSize(sf::Vector2f(64, 64)); //set size!

		if(i < 5)
			rect->setPosition(m_window->getView().getCenter().x - (2-i)*120 - rect->getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 250);
		else if(i < 10)
			rect->setPosition(m_window->getView().getCenter().x - (7-i)*120 - rect->getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 350);
		else
			rect->setPosition(m_window->getView().getCenter().x - (12-i)*120 - rect->getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 450);

		m_buttonsRect.push_back(*rect);

		//sprite
		sf::Sprite *sprite = new sf::Sprite;
		sprite->setTexture(m_buttonTexture);

		if(i < m_maxLevel)
		{
			if(i < 5)
				sprite->setTextureRect(sf::IntRect(362 + i*64, 0, 64, 64));
			else if(i < 10)
				sprite->setTextureRect(sf::IntRect(362 + (i-6)*64 + 64, 64, 64, 64));
			else
				sprite->setTextureRect(sf::IntRect(362 + (i-11)*64 + 64, 128, 64, 64));
		}
		else
			sprite->setTextureRect(sf::IntRect(362 + 4*64, 64*3, 64, 64));

		sprite->setPosition(rect->getPosition());
		m_buttonsSprite.push_back(*sprite);
	}

	//set up main Play, Options, Exit
	for(int i = 0; i < 3; i++)
	{
		//rect
		sf::RectangleShape *rect = new sf::RectangleShape;
		rect->setFillColor(sf::Color::Red);
		rect->setSize(sf::Vector2f( (544/3), 64)); //set size!
		rect->setPosition(m_window->getView().getCenter().x - (1-i)*(544/3) - (544/6), m_window->getView().getCenter().y - m_window->getSize().y/2 + 150);
		//rect->setPosition(m_window->getView().getCenter().x - m_window->getSize().x/2 + i*231 + 148, m_window->getView().getCenter().y - m_window->getSize().y/2 + 150);
		m_buttonsRect.push_back(*rect);

		//sprite
		sf::Sprite *sprite = new sf::Sprite;
		sprite->setTexture(m_buttonTexture);
		sprite->setTextureRect(sf::IntRect(0, i*64, 181, 64));
		sprite->setPosition(rect->getPosition());
		m_buttonsSprite.push_back(*sprite);
	}

	//set up selector
	m_selector.setSize(m_buttonsRect[0].getSize());
	m_selector.setFillColor(sf::Color::Transparent);
	m_selector.setOutlineThickness(-2);
	m_selector.setOutlineColor(sf::Color::Green);
}

void Menu::UpdateZero()
{
	for(int i = 0; i < m_buttonsRect.size(); i++)
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
		{
			//mouse is NOT hovering the button -> set color rects to not hovering state
			if(m_buttonsRect[i].getFillColor() == sf::Color::Red)
				{}
			else
				m_buttonsRect[i].setFillColor(sf::Color::Red);
		}
		else
		{
			//mouse is hovering the button -> set color rects to hovering stuff
			if(m_buttonsRect[i].getFillColor() == sf::Color::Green)
				{}
			else
				m_buttonsRect[i].setFillColor(sf::Color::Green);
		}
	}

	for(int i = 0; i < m_buttonsSprite.size() - 3; i++) //levels
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
		{
			if(i <= m_maxLevel)
			{
				//mouse is NOT hovering the button sprite -> set texture rects to not hovering state
				if(i < 5)
				{
					if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + i*64, 0, 64, 64))
						{}
					else
						m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + i*64, 0, 64, 64));
				}
				else if(i < 10)
				{
					if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + (i-6)*64, 64, 64, 64))
						{}
					else
						m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + (i-6)*64 + 64, 64, 64, 64));
				}
				else
				{
					if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + (i-11)*64, 128, 64, 64))
						{}
					else
						m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + (i-11)*64 + 64, 128, 64, 64));
				}
			}
			else //set blocked out view
			{
				if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + 4*64, 64*3, 64, 64))
					{}
				else
					m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + 4*64, 64*3, 64, 64));
			}
		}
		else
		{
			if(i <= m_maxLevel)
			{
				//mouse is hovering the button sprite -> set texture rects to hovering stuff
				if(i < 5)
				{
					if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + i*64, 0, 64, 64))
						{}
					else
						m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + i*64, 0, 64, 64));
				}
				else if(i < 10)
				{
					if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + (i-5)*64, 64, 64, 64))
						{}
					else
						m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + (i-5)*64 + 64, 64, 64, 64));
				}
				else
				{
					if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + (i-10)*64, 128, 64, 64))
						{}
					else
						m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + (i-10)*64 + 64, 128, 64, 64));
				}
			}
			else //set blocked out view
			{
				if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(362 + 4*64, 64*3, 64, 64))
					{}
				else
					m_buttonsSprite[i].setTextureRect(sf::IntRect(362 + 4*64, 64*3, 64, 64));
			}
		}
	}

	for(int i = m_buttonsSprite.size() - 3; i < m_buttonsSprite.size(); i++) //play, options, exit
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
		{
			//mouse is NOT hovering the button sprite -> set texture rects to not hovering state
			if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(0, (i-(m_buttonsSprite.size() - 3))*64, 181, 64))
				{}
			else
				m_buttonsSprite[i].setTextureRect(sf::IntRect(0, (i-(m_buttonsSprite.size()-3))*64, 181, 64));
		}
		else
		{
			//mouse is hovering the button sprite -> set texture rects to hovering stuff
			if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(181, (i-(m_buttonsSprite.size()-3))*64, 181, 64))
				{}
			else
				m_buttonsSprite[i].setTextureRect(sf::IntRect(181, (i-(m_buttonsSprite.size()-3))*64, 181, 64));
		}
	}

	//update selector
	if(m_selector.getPosition() != m_buttonsSprite[m_mapLevel].getPosition())
		m_selector.setPosition(m_buttonsSprite[m_mapLevel].getPosition());
}

void Menu::ClickZero()
{
	for(int i = 0; i < m_buttonsRect.size(); i++)
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
			{}
		else
		{
			m_sound.play();

			if(i >= 0 && i < m_buttonsRect.size() - 3)
			{
				//make level i selected
				if(i <= m_maxLevel)
					m_mapLevel = i;
				//else
					//don't select it
			}
			else if(i == 15)
			{
				//play the selected level
				m_player->setPosition(sf::Vector2f(0, 0));
				m_tilemap->setMap(m_mapLevel, *m_window);
				m_menuUp = false; //<--- temporary
			}
			else if(i == 16)
			{
				//options menu
				m_prevState = 0;
				PopulateTwo();
			}
			else if(i == 17)
			{
				//save stuff
				m_window->close();
			}

			break;
		}
	}
}

void Menu::PopulateOne() //Game Menu
{
	//clear everything first
	m_buttonsRect.clear();
	m_buttonsSprite.clear();

	m_title.setTextureRect(sf::IntRect(0, 0, 0, 0));

	m_state = 1; //set state

	//title
	m_title.setTextureRect(sf::IntRect(0, 57, 570, 57));
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50);

	//set up rects and sprites
	for(int i = 0; i < 4; i++)
	{
		//rect
		sf::RectangleShape *rect = new sf::RectangleShape;
		rect->setFillColor(sf::Color::Red);
		rect->setSize(sf::Vector2f(200, 64));
		rect->setPosition(m_window->getView().getCenter().x - rect->getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*i + 175);
		m_buttonsRect.push_back(*rect);

		//sprite
		sf::Sprite *sprite = new sf::Sprite;
		sprite->setTexture(m_buttonTexture);
		sprite->setTextureRect(sf::IntRect(0, 192 + 64*i, 200, 64));
		sprite->setPosition(rect->getPosition());
		m_buttonsSprite.push_back(*sprite);

		//BUG FIX: play is a little bugged, so gotta make it a little lower
		if(i == 0)
			sprite->setTextureRect(sf::IntRect(0, i*64+2, 181, 64-2));
	}
}

void Menu::UpdateOne()
{
	for(int i = 0; i < m_buttonsRect.size(); i++)
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
		{
			//mouse is NOT hovering the button -> set color rects to not hovering state
			if(m_buttonsRect[i].getFillColor() == sf::Color::Red)
				{}
			else
				m_buttonsRect[i].setFillColor(sf::Color::Red);
		}
		else
		{
			//mouse is hovering the button -> set color rects to hovering stuff
			if(m_buttonsRect[i].getFillColor() == sf::Color::Green)
				{}
			else
				m_buttonsRect[i].setFillColor(sf::Color::Green);
		}
	}

	for(int i = 0; i < m_buttonsSprite.size(); i++)
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
		{
			//mouse is NOT hovering the button sprite -> set texture rects to not hovering state
			if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(0, 192 + i*64, 200, 64))
				{}
			else
				m_buttonsSprite[i].setTextureRect(sf::IntRect(0, 192 + i*64, 200, 64));

			//BUG FIX: play is a little bugged, so gotta make it a little lower
			if(i == 0)
				m_buttonsSprite[0].setTextureRect(sf::IntRect(0, 192 + i*64+1, 200, 64-1));
		}
		else
		{
			//mouse is hovering the button sprite -> set texture rects to hovering stuff
			if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(200, 192 + i*64, 200, 64))
				{}
			else
				m_buttonsSprite[i].setTextureRect(sf::IntRect(200, 192 + i*64, 200, 64));

			//BUG FIX: play is a little bugged, so gotta make it a little lower
			if(i == 0)
				m_buttonsSprite[0].setTextureRect(sf::IntRect(200, 192 + i*64+1, 200, 64-1));
		}
	}
}

void Menu::ClickOne()
{
	for(int i = 0; i < m_buttonsRect.size(); i++)
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
			{}
		else
		{
			m_sound.play();

			if(i == 0) //return to playing
			{
				m_menuUp = false;
				break;
			}
			else if(i == 1) //return to main menu
				PopulateZero();
			else if(i == 2) //options
			{
				m_prevState = 1;
				PopulateTwo();
			}
			else if(i == 3) //exit
				//SAVE STUFF
				m_window->close();

			break;
		}
	}
}

void Menu::PopulateTwo()
{
	//clear everything first
	m_buttonsRect.clear();
	m_buttonsSprite.clear();

	m_title.setTextureRect(sf::IntRect(0, 0, 0, 0));

	m_state = 2; //set state

	//title
	m_title.setTextureRect(sf::IntRect(0, 57*2, 570, 57));
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50);

	//set up labels
	for(int i = 0; i < 4; i++)
	{
		//rect
		sf::RectangleShape *rect = new sf::RectangleShape;
		rect->setFillColor(sf::Color::Red);
		rect->setSize(sf::Vector2f(200, 48));
		rect->setPosition(m_window->getView().getCenter().x - rect->getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*i + 175);
		m_buttonsRect.push_back(*rect);

		//sprite
		sf::Sprite *sprite = new sf::Sprite;
		sprite->setTexture(m_buttonTexture);
		sprite->setTextureRect(sf::IntRect(0, 448 + i*48, 200, 48));
		sprite->setPosition(rect->getPosition());
		m_buttonsSprite.push_back(*sprite);
	}

	//set up movers
	for(int i = 0; i < 3; i++)
	{
		//rect
		sf::RectangleShape *rect = new sf::RectangleShape;
		rect->setFillColor(sf::Color::Blue);
		rect->setSize(sf::Vector2f(32, 32));
		rect->setPosition(m_window->getView().getCenter().x - rect->getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*i + 240);
		
		if(i == 0)
		{
			rect->setPosition(m_window->getView().getCenter().x - 200 + 4*(m_musicLevel), rect->getPosition().y);
		}
		else if(i == 1)
			rect->setPosition(m_window->getView().getCenter().x - 200 + 4*(m_soundLevel), rect->getPosition().y);
		else
			rect->setPosition(m_window->getView().getCenter().x - 200 + 4*(m_contrastLevel), rect->getPosition().y);

		m_buttonsRect.push_back(*rect);

		//sprite
		sf::Sprite *sprite = new sf::Sprite;
		sprite->setTexture(m_buttonTexture);
		sprite->setTextureRect(sf::IntRect(400, 448, 32, 32));
		sprite->setPosition(rect->getPosition());
		m_buttonsSprite.push_back(*sprite);
	}
}

void Menu::UpdateTwo()
{
	for(int i = 4; i < 7; i++) //only movers are affected
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
		{
			//mouse is NOT hovering the button -> set color rects to not hovering state
			if(m_buttonsRect[i].getFillColor() == sf::Color::Blue)
				{}
			else
				m_buttonsRect[i].setFillColor(sf::Color::Blue);
		}
		else
		{
			//mouse is hovering the button -> set color rects to hovering stuff
			if(m_buttonsRect[i].getFillColor() == sf::Color::Cyan)
				{}
			else
				m_buttonsRect[i].setFillColor(sf::Color::Cyan);
		}
	}

	for(int i = 4; i < 7; i++) //only movers are affected
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
		{
			//mouse is NOT hovering the button sprite -> set texture rects to not hovering state
			if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(400, 448, 32, 32))
				{}
			else
				m_buttonsSprite[i].setTextureRect(sf::IntRect(400, 448, 32, 32));
		}
		else
		{
			//mouse is hovering the button sprite -> set texture rects to hovering stuff
			if(m_buttonsSprite[i].getTextureRect() == sf::IntRect(400, 448, 32, 32))
				{}
			else
				m_buttonsSprite[i].setTextureRect(sf::IntRect(400, 448, 32, 32));
		}
	}

	//for BACK
	if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[3].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[3].getPosition().x + m_buttonsRect[3].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[3].getPosition().y + m_buttonsRect[3].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[3].getPosition().y)
	{
		//mouse is NOT hovering the button sprite -> set texture rects to not hovering state
		if(m_buttonsSprite[3].getTextureRect() == sf::IntRect(0, 448 + 144, 200, 48))
			{}
		else
			m_buttonsSprite[3].setTextureRect(sf::IntRect(0, 448 + 144, 200, 48));
	}

	else
	{
		//mouse is hovering the button sprite -> set texture rects to hovering stuff
		if(m_buttonsSprite[3].getTextureRect() == sf::IntRect(200, 448 + 144, 200, 48))
			{}
		else
			m_buttonsSprite[3].setTextureRect(sf::IntRect(200, 448 + 144, 200, 48));
	}
}

void Menu::ClickTwo()
{
	for(int i = 3; i < m_buttonsRect.size(); i++)
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
			{}
		else
		{
			m_sound.play();

			if(i == 3) //back button
				Populate(m_prevState);
		}
	}
}

void Menu::ResizeZero(sf::Vector2f size)
{
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50); //set position
	/*m_title.setScale(size.x / WINDOW_SIZE.x, size.y / WINDOW_SIZE.y);*/

	//Set levels and stuff
	for(int i = 0; i < m_buttonsRect.size() - 3; i++)
	{
		if(i < 5)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (2-i)*120 - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 250); //set position!
		else if(i < 10)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (7-i)*120 - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 350); //set position!
		else
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (12-i)*120 - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 450); //set position!

		//m_buttonsRect[i].setSize(sf::Vector2f(m_buttonsRect[i].getSize().x * size.x / WINDOW_SIZE.x, m_buttonsRect[i].getSize().y * size.y / WINDOW_SIZE.y));
	}

	for(int i = 0; i < m_buttonsSprite.size() - 3; i++)
	{
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());
		//m_buttonsSprite[i].setScale(size.x / WINDOW_SIZE.x, size.y / WINDOW_SIZE.y);
	}

	//set Play Options Exit ones
	for(int i = m_buttonsRect.size() - 3; i < m_buttonsRect.size(); i++)
	{
		m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (16-i)*(544/3) - (544/6), m_window->getView().getCenter().y - m_window->getSize().y/2 + 150);
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());

		//set scale and stuff
	}
}

void Menu::ResizeZero()
{
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50); //set position

	//set levels and stuff
	for(int i = 0; i < m_buttonsRect.size() - 3; i++)
	{
		if(i < 5)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (2-i)*120 - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 250); //set position!
		else if(i < 10)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (7-i)*120 - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 350); //set position!
		else
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (12-i)*120 - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 450); //set position!
	}

	for(int i = 0; i < m_buttonsSprite.size() - 3; i++)
	{
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());
	}


	//set Play Options Exit ones
	for(int i = m_buttonsRect.size() - 3; i < m_buttonsRect.size(); i++)
	{
		m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - (16-i)*(544/3) - (544/6), m_window->getView().getCenter().y - m_window->getSize().y/2 + 150);
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());
	}
}

void Menu::ResizeOne(sf::Vector2f size)
{
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50); //set position
	/*m_title.setScale(size.x / WINDOW_SIZE.x, size.y / WINDOW_SIZE.y);*/

	for(int i = 0; i < m_buttonsRect.size(); i++)
	{
		m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*i + 175);
		//m_buttonsRect[i].setSize(sf::Vector2f(m_buttonsRect[i].getSize().x * size.x / WINDOW_SIZE.x, m_buttonsRect[i].getSize().y * size.y / WINDOW_SIZE.y));
	}

	for(int i = 0; i < m_buttonsSprite.size(); i++)
	{
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());
		//m_buttonsSprite[i].setScale(size.x / WINDOW_SIZE.x, size.y / WINDOW_SIZE.y);
	}
}

void Menu::ResizeOne()
{
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50); //set position

	for(int i = 0; i < m_buttonsRect.size(); i++)
		m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*i + 175);

	for(int i = 0; i < m_buttonsSprite.size(); i++)
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());
}

void Menu::ResizeTwo(sf::Vector2f size)
{
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50); //set position
	/*m_title.setScale(size.x / WINDOW_SIZE.x, size.y / WINDOW_SIZE.y);*/

	for(int i = 0; i < m_buttonsRect.size(); i++)
	{
		m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*i + 175);
		//m_buttonsRect[i].setSize(sf::Vector2f(m_buttonsRect[i].getSize().x * size.x / WINDOW_SIZE.x, m_buttonsRect[i].getSize().y * size.y / WINDOW_SIZE.y));
	}

	for(int i = m_buttonsRect.size() - 3; i < m_buttonsRect.size(); i++)
	{
		if(i == 4)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - 200 + 4*(m_musicLevel) - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*(i - (m_buttonsRect.size() - 3)) + 240);
		else if(i == 5)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - 200 + 4*(m_soundLevel) - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*(i - (m_buttonsRect.size() - 3)) + 240);
		else
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - 200 + 4*(m_contrastLevel) - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*(i - (m_buttonsRect.size() - 3)) + 240);
		//scale!
	}

	for(int i = 0; i < m_buttonsSprite.size(); i++)
	{
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());
		//m_buttonsSprite[i].setScale(size.x / WINDOW_SIZE.x, size.y / WINDOW_SIZE.y);
	}
}

void Menu::ResizeTwo()
{
	m_title.setPosition(m_window->getView().getCenter().x - m_title.getGlobalBounds().width/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 50); //set position

	for(int i = 0; i < m_buttonsRect.size() - 3; i++)
		m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*i + 175);

	for(int i = m_buttonsRect.size() - 3; i < m_buttonsRect.size(); i++)
	{
		if(i == 4)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - 200 + 4*(m_musicLevel) - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*(i - (m_buttonsRect.size() - 3)) + 240);
		else if(i == 5)
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - 200 + 4*(m_soundLevel) - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*(i - (m_buttonsRect.size() - 3)) + 240);
		else
			m_buttonsRect[i].setPosition(m_window->getView().getCenter().x - 200 + 4*(m_contrastLevel) - m_buttonsRect[i].getSize().x/2, m_window->getView().getCenter().y - m_window->getSize().y/2 + 115*(i - (m_buttonsRect.size() - 3)) + 240);
	}

	for(int i = 0; i < m_buttonsSprite.size(); i++)
		m_buttonsSprite[i].setPosition(m_buttonsRect[i].getPosition());
}

void Menu::Load()
{
	//loading game properties
	std::ifstream props("Properties/gameProperties.txt");
	int lvl(0), mus(0), sou(0), con(0);
	if(props.is_open())
	{
		std::string strLine = "";
		int nLineCount = 0;

		while(std::getline(props, strLine))
		{
			if(nLineCount == 0)
				lvl = std::stoi(strLine);
			else if(nLineCount == 1)
				mus = std::stoi(strLine);
			else if(nLineCount == 2)
				sou = std::stoi(strLine);
			else if(nLineCount == 3)
				con = std::stoi(strLine);

			nLineCount++;
		}
	}
	props.close();

	if(lvl > 14)
		lvl = 14;

	m_maxLevel = m_mapLevel = lvl;
	m_musicLevel = mus;
	m_soundLevel = sou;
	m_contrastLevel = con;

	std::cout<<m_maxLevel<<", "<<m_musicLevel<<", "<<m_soundLevel<<", "<<m_contrastLevel<<std::endl;
}

void Menu::Save()
{
	//save game properties
	std::ofstream props("Properties/gameProperties.txt");
	props.clear();
	props<<m_maxLevel;
	props<<"\n";
	props<<m_musicLevel;
	props<<"\n";
	props<<m_soundLevel;
	props<<"\n";
	props<<m_contrastLevel;

	props.close();
}

Menu::Menu()
{
	m_state = 0;
	m_prevState = 0;

	Load();

	m_titleTexture.loadFromFile("Assets/titleTexture.png"); m_titleTexture.setSmooth(true);
	m_buttonTexture.loadFromFile("Assets/buttonTexture.png"); m_buttonTexture.setSmooth(true);

	m_title.setTexture(m_titleTexture);

	m_dragging = false;
	m_dragNum = -1;

	m_clickNoise.loadFromFile("Assets/menuClick.wav");
	m_sound.setBuffer(m_clickNoise);
}

void Menu::Populate(int i)
{
	if(i == 0)
		PopulateZero();
	else if(i == 1)
		PopulateOne();
	else if(i == 2)
		PopulateTwo();
}

void Menu::Update(BackgroundProcesses &b)
{
	if(m_tilemap->getLevel() >= m_maxLevel)
		m_maxLevel = m_tilemap->getLevel();

	if(!m_menuUp)
	{}
	else if(m_state == 0)
		UpdateZero();
	else if(m_state == 1)
		UpdateOne();
	else if(m_state == 2)
	{
		Drag(b);
		UpdateTwo();
	}

	if(m_state == 0)
		m_player->setInvis();
	else if(m_state == 2 && m_prevState == 0)
		m_player->setInvis();
	else if(m_state != 0 && m_player->getVis() == false)
		m_player->setVis();
}

void Menu::setOptions(BackgroundProcesses &b)
{
	m_player->setSoundLevel(m_soundLevel);
	b.setMusicVolume(m_musicLevel);
	b.setSoundEffectsVolume(m_soundLevel);
	setSoundLevel(m_soundLevel);
}

void Menu::DragSet()
{
	if(m_state == 2)
	{
		m_dragging = true;

		for(int i = 4; i < m_buttonsRect.size(); i++)
		{
			if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) < m_buttonsRect[i].getPosition().x || (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x) > m_buttonsRect[i].getPosition().x + m_buttonsRect[i].getSize().x || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) > m_buttonsRect[i].getPosition().y + m_buttonsRect[i].getSize().y || (m_window->getView().getCenter().y - m_window->getSize().y/2 + sf::Mouse::getPosition(*m_window).y) < m_buttonsRect[i].getPosition().y)
				{}
			else
			{
				if(i == 4) //music
				{
					m_dragNum = 4;
					break;
				}
				else if(i == 5) //sound effects
				{
					m_dragNum = 5;
					break;
				}
				else if(i == 6) //Contrast
				{
					m_dragNum = 6;
					break;
				}
			}
		}

	}
}

void Menu::Drag(BackgroundProcesses &b)
{
	if(m_dragging == true && m_dragNum != -1)
	{
		if((m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x <= m_window->getView().getCenter().x + 200) && (m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x >= m_window->getView().getCenter().x - 200))
		{
			m_buttonsRect[m_dragNum].setPosition(m_window->getView().getCenter().x - m_window->getSize().x/2 + sf::Mouse::getPosition(*m_window).x - 16, m_buttonsRect[m_dragNum].getPosition().y);
			m_buttonsSprite[m_dragNum].setPosition(m_buttonsRect[m_dragNum].getPosition());
		}
	}

	for(int i = m_buttonsRect.size() - 3; i < m_buttonsRect.size(); i++)
	{
		if(i == 4)
			m_musicLevel = (m_buttonsRect[i].getPosition().x - (m_window->getView().getCenter().x - 200))/4;
		else if(i == 5)
			m_soundLevel = (m_buttonsRect[i].getPosition().x - (m_window->getView().getCenter().x - 200))/4;
		else if(i == 6)
			m_contrastLevel = (m_buttonsRect[i].getPosition().x - (m_window->getView().getCenter().x - 200))/4;
	}

	setOptions(b);
}

void Menu::Click()
{
	m_dragging = false;
	m_dragNum = -1;

	if(!m_menuUp)
	{}
	else if(m_state == 0)
		ClickZero();
	else if(m_state == 1)
		ClickOne();
	else if(m_state == 2)
	{
		for(int i = m_buttonsRect.size() - 3; i < m_buttonsRect.size(); i++)
		{
			if(i == 4)
				m_musicLevel = (m_buttonsRect[i].getPosition().x - (m_window->getView().getCenter().x - 200))/4;
			else if(i == 5)
				m_soundLevel = (m_buttonsRect[i].getPosition().x - (m_window->getView().getCenter().x - 200))/4;
			else
				m_contrastLevel = (m_buttonsRect[i].getPosition().x - (m_window->getView().getCenter().x - 200))/4;
		}
		ClickTwo();
	}

	Save();
}

void Menu::Draw()
{
	m_window->draw(m_title);
	
	/*for(int i = 0; i < m_buttonsRect.size(); i++)
		m_window->draw(m_buttonsRect[i]);*/

	for(int i = 0; i < m_buttonsSprite.size(); i++)
		m_window->draw(m_buttonsSprite[i]);

	if(m_state == 0)
		m_window->draw(m_selector);
}

void Menu::Resize(sf::Vector2f size)
{
	if(m_state == 0)
		ResizeZero(size);
	else if(m_state == 1)
		ResizeOne(size);
	else if(m_state == 2)
		ResizeTwo(size);
}

void Menu::Resize()
{
	if(m_state == 0)
		ResizeZero();
	else if(m_state == 1)
		ResizeOne();
	else if(m_state == 2)
		ResizeTwo();
}