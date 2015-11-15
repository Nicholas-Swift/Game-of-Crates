#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tilemap.h"

class Player
{
private:
	sf::RectangleShape m_rect;
	float m_top, m_bottom, m_left, m_right;
	
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float frameCounter, switchFrame, frameSpeed;
	sf::Vector2i source;

	sf::SoundBuffer m_grassBuffer;
	sf::Sound m_walking;
	float soundInt;

	bool m_isMovingLeft, m_isMovingRight;
	float m_movSpeedConst, m_movSpeedMax;

	float m_gravity, m_inAir, m_inAirMax;
	bool m_onGround, m_jumped;

	bool m_onCrate;

	sf::Vector2f m_movement;

	bool vis;

public:
	float getTop(), getBottom(), getLeft(), getRight();
	void setSoundLevel(int i);
	void setMap(Tilemap &t, sf::Vector2f pos, int i);
	void setPosition(sf::Vector2f pos);
	void setInvis(), setVis();
	bool getVis();

public:
	Player();
	void HandleEvents(sf::Keyboard::Key, bool isPressed);
	void Update(Tilemap &t, sf::RenderWindow &window, BackgroundProcesses &b);
	void Move(sf::Time &deltaTime, Tilemap &t);
	void Animate(sf::Time &deltaTime);
	void Sound(sf::Time &deltaTime);
	void Draw(sf::RenderWindow &window);
};

#endif