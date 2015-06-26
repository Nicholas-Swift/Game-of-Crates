#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

const sf::Vector2f WINDOW_SIZE(960, 640);

Game::Game()
{
	m_window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Platformer"/*, sf::Style::None*/);
	m_window.setFramerateLimit(1000);

	//Update view
	m_view.setCenter( (m_player.getLeft() + m_player.getRight()) / 2, m_player.getBottom() );
	m_view.setSize(m_window.getSize().x, m_window.getSize().y);
	m_window.setView(m_view);

	//m_backgroundProcesses;
	m_backgroundProcesses.ViewUpdate(m_window);

	//m_tilemap;
	//m_player;
	
	//m_menu;
	m_menu.setWindow(m_window);
	m_menu.setTilemap(m_tilemap);
	m_menu.setPlayer(m_player);
	m_menu.Populate(0);
	m_menu.Resize();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 1000.f); //1000 frames per second

	while (m_window.isOpen())
	{
		processEvents(); //check for events

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame) //this collects user input. If it slows down, game loop doesn't slow down.
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame); //update the game with 'deltaTime'
		}

		render(); //render to the screen
	}

}

void Game::processEvents()
{
	sf::Event Event;
	while (m_window.pollEvent(Event))
	{
		switch(Event.type)
		{
		case sf::Event::KeyPressed:
			if(!m_menu.getMenuUp()) //if menu not up
				m_player.HandleEvents(Event.key.code, true);

			if(Event.key.code == sf::Keyboard::Key::Escape)
				m_menu.pressedEscape();

			break;

		case sf::Event::KeyReleased:
			if(!m_menu.getMenuUp()) //if menu not up
				m_player.HandleEvents(Event.key.code, false);
			break;

		case sf::Event::MouseButtonPressed:
			if(m_menu.getMenuUp())
				m_menu.DragSet();
			break;

		case sf::Event::MouseButtonReleased:
			if(m_menu.getMenuUp())
				m_menu.Click();
			break;

		case sf::Event::Resized:
			m_backgroundProcesses.Resize(sf::Vector2f(Event.size.width, Event.size.height));
			m_menu.Resize(sf::Vector2f(Event.size.width, Event.size.height));
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	if(!m_menu.getMenuUp())
	{
		//update the game!
		m_tilemap.Update(deltaTime);

		m_player.Update(m_tilemap);
		m_player.Move(deltaTime, m_tilemap);
		m_player.Animate(deltaTime);
		m_player.Sound(deltaTime);
	}
	else
	{
		m_menu.Update(m_backgroundProcesses);
	}

	//update background processes, so clouds always move!
	m_backgroundProcesses.Update(deltaTime, m_window);

	//Game update view
	m_view.setCenter( (m_player.getLeft() + m_player.getRight()) / 2, m_player.getBottom() );
	m_view.setSize(m_window.getSize().x, m_window.getSize().y);
	m_window.setView(m_view);

	//update view
	m_backgroundProcesses.ViewUpdate(m_window);
}

void Game::render()
{
	m_window.clear();

	m_backgroundProcesses.Draw(m_window);
	m_tilemap.Draw(m_window);
	m_player.Draw(m_window);

	if(m_menu.getMenuUp())
		m_menu.Draw();

	m_window.display();
}