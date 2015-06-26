#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Tilemap.h"

float Player::getTop()
{
	return m_top;
}

float Player::getBottom()
{
	return m_bottom;
}

float Player::getLeft()
{
	return m_left;
}

float Player::getRight()
{
	return m_right;
}

void Player::setSoundLevel(int i)
{
	if(i <= 0)
		m_walking.setVolume(0);
	else
		m_walking.setVolume(i);
}

void Player::setPosition(sf::Vector2f pos)
{
	m_rect.setPosition(pos);
	m_sprite.setPosition(pos);
}

void Player::setInvis()
{
	m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
	vis = false;
}

void Player::setVis()
{
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	vis = true;
}

bool Player::getVis()
{
	return vis;
}

Player::Player()
{
	m_rect.setSize(sf::Vector2f(32, 32));
	m_rect.setFillColor(sf::Color::Red);

	m_texture.loadFromFile("Assets/Player.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	frameCounter = 0; switchFrame = 100; frameSpeed = 500;
	source = sf::Vector2i(0, 0);

	m_grassBuffer.loadFromFile("Assets/grass.flac");
	m_walking.setBuffer(m_grassBuffer);
	soundInt = 0;
	setSoundLevel(0);

	m_top = m_rect.getPosition().y;
	m_bottom = m_rect.getPosition().y + m_rect.getSize().y;
	m_left = m_rect.getPosition().x;
	m_right = m_rect.getPosition().x + m_rect.getSize().x;

	m_isMovingRight = m_isMovingLeft = false;
	m_movSpeedConst = 0.0010f;
	m_movSpeedMax = 0.23f;

	m_gravity = 0.388;
	m_inAir = 0;
	m_inAirMax = 0.3f;
	m_onGround = m_inAir = false;

	m_onCrate = false;

	m_movement = sf::Vector2f(0, 0);

	vis = true;
}

void Player::HandleEvents(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Key::D)
		m_isMovingRight = isPressed;
	if (key == sf::Keyboard::Key::A)
		m_isMovingLeft = isPressed;
}

void Player::Update(Tilemap &t)
{
	m_top = m_rect.getPosition().y;
	m_bottom = m_rect.getPosition().y + m_rect.getSize().y;
	m_left = m_rect.getPosition().x;
	m_right = m_rect.getPosition().x + m_rect.getSize().x;

	//downward collision on tilemap
	if(m_bottom / 64 < 0 || m_right < 0)
		m_onGround = false;
	else if(int(m_bottom) % 64 != 0)
		m_onGround = false;
	else if( (t.getLevelMap(m_bottom/64, m_left/64) >= 100 && t.getLevelMap(m_bottom/64, m_left/64) < 200) || (t.getLevelMap(m_bottom/64, m_left/64) >= 500 && t.getLevelMap(m_bottom/64, m_left/64) < 600) || (t.getLevelMap(m_bottom/64, m_right/64) >= 100 && t.getLevelMap(m_bottom/64, m_right/64) < 200) || (t.getLevelMap(m_bottom/64, m_right/64) >= 500 && t.getLevelMap(m_bottom/64, m_right/64) < 600) )
		m_onGround = true;
	else
		m_onGround = false;

	//downward collision on platform
	for(int i = 0; i < t.getPlatformSize(); i++)
	{
		if(m_right < t.getPlatformLeft(i) || m_left > t.getPlatformRight(i) || m_top > t.getPlatformBottom(i) || m_bottom < t.getPlatformTop(i))
		{}
		else if(int(m_bottom) <= t.getPlatformTop(i))
			m_onGround = true;
	}
	
	for(int i = 0; i < t.getCrateSize(); i++)
	{
		//downward collision on crate
		if(m_right < t.getCrateLeft(i) || m_left > t.getCrateRight(i) || m_top > t.getCrateBottom(i) || m_bottom < t.getCrateTop(i))
		{}
		else if(m_bottom >= t.getCrateTop(i) && m_bottom - 2 <= t.getCrateTop(i))
		{
			m_onGround = true;
			m_onCrate = true;
		}
		else
		{
			m_onCrate = false;
		}

		//moving crates left and right
		if(!m_onCrate)
		{
			//not colliding with crate
			if(m_right < t.getCrateLeft(i) || m_left > t.getCrateRight(i) || m_top > t.getCrateBottom(i) || m_bottom < t.getCrateTop(i))
			{}

			//on top of crate
			else if(m_top <= t.getCrateBottom(i) && m_top >= (t.getCrateBottom(i) - 2))
			{
				t.setCratePos(i, sf::Vector2f(t.getCrateLeft(i), m_top - (t.getCrateBottom(i) - t.getCrateTop(i))));
			}

			//pushing crate right
			else if(m_right >= t.getCrateLeft(i) && m_left < t.getCrateLeft(i))
			{
				t.setCratePos(i, sf::Vector2f(m_right, t.getCrateTop(i)));
			}

			//pushing crate left
			else if(m_left <= t.getCrateRight(i) && m_left > t.getCrateLeft(i))
			{
				t.setCratePos(i, sf::Vector2f(m_left - (t.getCrateRight(i) - t.getCrateLeft(i)), t.getCrateTop(i)));
			}
		}
	}
}

void Player::Move(sf::Time &deltaTime, Tilemap &t)
{
	//moving right and slowing down
	if(m_isMovingRight == true)
		m_movement.x += m_movSpeedConst * deltaTime.asMilliseconds();
	else if(m_isMovingRight == false && m_movement.x > 0)
	{
		m_movement.x -= m_movSpeedConst * 1.5 * deltaTime.asMilliseconds();
		if(m_movement.x < 0)
			m_movement.x = 0;
	}

	//moving left and slowing down
	if(m_isMovingLeft == true)
		m_movement.x -= m_movSpeedConst * deltaTime.asMilliseconds();
	else if(m_isMovingLeft == false && m_movement.x < 0)
	{
		m_movement.x += m_movSpeedConst* 1.5 * deltaTime.asMilliseconds();
		if(m_movement.x > 0)
			m_movement.x = 0;
	}

	//not over max speed
	if(m_movement.x >= m_movSpeedMax)
		m_movement.x = m_movSpeedMax;
	else if(m_movement.x <= -m_movSpeedMax)
		m_movement.x = -m_movSpeedMax;

	//don't move left right if colliding with wall
	if(int(m_bottom) % 64 == 0 && (t.getLevelMap((m_bottom + 2)/64, m_left/64) == 192 || t.getLevelMap((m_bottom + 2)/64, m_left/64) == 191 || t.getLevelMap((m_bottom + 2)/64, m_right/64) == 191 || t.getLevelMap((m_bottom + 2)/64, m_right/64) == 190 || t.getLevelMap((m_bottom + 2)/64, m_left/64) == 192 || t.getLevelMap((m_bottom + 2)/64, m_left/64) == 592 || t.getLevelMap((m_bottom + 2)/64, m_left/64) == 591 || t.getLevelMap((m_bottom + 2)/64, m_right/64) == 591 || t.getLevelMap((m_bottom + 2)/64, m_right/64) == 590))
		{}
	else if((t.getLevelMap(m_bottom/64, m_left/64) == 192 || t.getLevelMap(m_bottom/64, m_left/64) == 292 || t.getLevelMap(m_bottom/64, m_left/64) == 392 || t.getLevelMap(m_bottom/64, m_left/64) == 490 || t.getLevelMap(m_bottom/64, m_left/64) == 592 || t.getLevelMap(m_bottom/64, m_left/64) == 191 || t.getLevelMap(m_bottom/64, m_left/64) == 291 || t.getLevelMap(m_bottom/64, m_left/64) == 391 || t.getLevelMap(m_bottom/64, m_left/64) == 491 || t.getLevelMap(m_bottom/64, m_left/64) == 591) && m_movement.x < 0)
		m_movement.x = 0;
	else if((t.getLevelMap(m_bottom/64, m_right/64) == 190 || t.getLevelMap(m_bottom/64, m_right/64) == 290 || t.getLevelMap(m_bottom/64, m_right/64) == 390 || t.getLevelMap(m_bottom/64, m_right/64) == 492 || t.getLevelMap(m_bottom/64, m_right/64) == 590 || t.getLevelMap(m_bottom/64, m_right/64) == 191 || t.getLevelMap(m_bottom/64, m_right/64) == 291 || t.getLevelMap(m_bottom/64, m_right/64) == 391 || t.getLevelMap(m_bottom/64, m_right/64) == 491 || t.getLevelMap(m_bottom/64, m_right/64) == 591) && m_movement.x > 0)
		m_movement.x = 0;
	else if((t.getLevelMap((m_top + 2)/64, m_left/64) == 192 || t.getLevelMap((m_top + 2)/64, m_left/64) == 292 || t.getLevelMap((m_top + 2)/64, m_left/64) == 392 || t.getLevelMap((m_top + 2)/64, m_left/64) == 490 || t.getLevelMap((m_top + 2)/64, m_left/64) == 592 || t.getLevelMap((m_top + 2)/64, m_left/64) == 191 || t.getLevelMap((m_top + 2)/64, m_left/64) == 291 || t.getLevelMap((m_top + 2)/64, m_left/64) == 391 || t.getLevelMap((m_top + 2)/64, m_left/64) == 491 || t.getLevelMap((m_top + 2)/64, m_left/64) == 591) && m_movement.x < 0)
		m_movement.x = 0;
	else if((t.getLevelMap((m_top + 2)/64, m_right/64) == 190 || t.getLevelMap((m_top + 2)/64, m_right/64) == 290 || t.getLevelMap((m_top + 2)/64, m_right/64) == 390 || t.getLevelMap((m_top + 2)/64, m_right/64) == 492 || t.getLevelMap((m_top + 2)/64, m_right/64) == 590 || t.getLevelMap((m_top + 2)/64, m_right/64) == 191 || t.getLevelMap((m_top + 2)/64, m_right/64) == 291 || t.getLevelMap((m_top + 2)/64, m_right/64) == 391 || t.getLevelMap((m_top + 2)/64, m_right/64) == 491 || t.getLevelMap((m_top + 2)/64, m_right/64) == 591) && m_movement.x > 0)
		m_movement.x = 0;
	
	//don't move if colliding with a colliding crate!
	for(int i = 0; i < t.getCrateSize(); i++)
	{
		if(t.getCrateOnLeft(i) == true || t.getCrateOnRight(i) == true)
		{
			if(m_right < t.getCrateLeft(i) || m_left > t.getCrateRight(i) || m_top > t.getCrateBottom(i) || m_bottom < t.getCrateTop(i))
				{}
			else if(m_right >= t.getCrateLeft(i) && (m_right + m_left)/2 <= t.getCrateLeft(i) && m_movement.x > 0 &&(m_bottom - 2) >= t.getCrateTop(i))
				m_movement.x = 0;
			else if(m_left <= t.getCrateRight(i) && (m_right + m_left)/2 >= t.getCrateLeft(i) && m_movement.x < 0 && (m_bottom - 2) >= t.getCrateTop(i))
				m_movement.x = 0;
		}
	}

	//jumping
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_jumped = true;

	//if hit top of block, fall
	if((t.getLevelMap(m_top/64, (m_left + 2)/64) == 190 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 190 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 191 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 191 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 192 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 192 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 290 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 290 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 291 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 291 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 292 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 292 ||
		t.getLevelMap(m_top/64, (m_left + 2)/64) == 390 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 390 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 391 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 391 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 392 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 392 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 490 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 490 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 491 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 491 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 492 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 492 ||
		t.getLevelMap(m_top/64, (m_left + 2)/64) == 590 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 590 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 591 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 591 || t.getLevelMap(m_top/64, (m_left + 2)/64) == 592 || t.getLevelMap(m_top/64, (m_right - 2)/64) == 592) && m_movement.y < 0)
		m_movement.y = 0;

	//setting jump stuff
	if(m_jumped == true && m_onGround == true)
	{
		m_movement.y = -m_gravity;
		m_jumped = false;
	}
	else
	{
		m_jumped = false;

		if(!m_onGround)
			m_movement.y += m_gravity * 0.003 * deltaTime.asMilliseconds();
		else
			m_movement.y = 0;

		if(m_movement.y > 0.5)
			m_movement.y = 0.5;
	}

	//move if on a platform
	for(int i = 0; i < t.getPlatformSize(); i++)
	{
		//not touching
		if(m_right < t.getPlatformLeft(i) || m_left > t.getPlatformRight(i) || m_top > t.getPlatformBottom(i) || m_bottom < t.getPlatformTop(i))
		{}
		else if(m_left > t.getPlatformLeft(i) && m_right < t.getPlatformRight(i))
			m_movement.x += t.getPlatformMovement(i).x;
		else if( m_left < t.getPlatformLeft(i) && (m_left + m_right)/2 > t.getPlatformLeft(i) && int(m_movement.x) == 0)
			m_movement.x += t.getPlatformMovement(i).x;
		else if( m_right > t.getPlatformRight(i) && (m_left + m_right)/2 < t.getPlatformRight(i) && int(m_movement.x) == 0)
			m_movement.x += t.getPlatformMovement(i).x;
	}
	//move if on a crate (movement will be non-zero if crate is on a platform so...)
	for(int i = 0; i < t.getCrateSize(); i++)
	{
		if(m_right < t.getCrateLeft(i) || m_left > t.getCrateRight(i) || m_top > t.getCrateBottom(i) || m_bottom < t.getCrateTop(i))
			{}
		else if(int(m_bottom) <= t.getCrateTop(i))
			m_movement.x += t.getCrateMovement(i).x;
	}

	//the actual move part
	m_rect.move(m_movement.x, m_movement.y);
	m_sprite.move(m_movement.x, m_movement.y);

	//change the movement after actually moving so it doesn't mess up earlier processes
	for(int i = 0; i < t.getPlatformSize(); i++)
	{
		//not touching
		if(m_right < t.getPlatformLeft(i) || m_left > t.getPlatformRight(i) || m_top > t.getPlatformBottom(i) || m_bottom < t.getPlatformTop(i))
		{}
		else if(m_left > t.getPlatformLeft(i) && m_right < t.getPlatformRight(i))
			m_movement.x -= t.getPlatformMovement(i).x;
		else if( m_left < t.getPlatformLeft(i) && (m_left + m_right)/2 > t.getPlatformLeft(i) && int(m_movement.x) == 0)
			m_movement.x -= t.getPlatformMovement(i).x;
		else if( m_right > t.getPlatformRight(i) && (m_left + m_right)/2 < t.getPlatformRight(i) && int(m_movement.x) == 0)
			m_movement.x -= t.getPlatformMovement(i).x;
	}
	//change the movement after actually moving the crate so it doesn't mess up earlier processes
	for(int i = 0; i < t.getCrateSize(); i++)
	{
		if(m_right < t.getCrateLeft(i) || m_left > t.getCrateRight(i) || m_top > t.getCrateBottom(i) || m_bottom < t.getCrateTop(i))
			{}
		else if(int(m_bottom) <= t.getCrateTop(i))
			m_movement.x -= t.getCrateMovement(i).x;
	}
}

void Player::Animate(sf::Time &deltaTime)
{
	if(m_isMovingRight || m_isMovingLeft)
	{
		frameCounter += frameSpeed * deltaTime.asMilliseconds() * 0.001;
		if(frameCounter >= switchFrame)
		{
			frameCounter = 0;
			source.x++;
			if(source.x * 32 >= 32*3)
				source.x = 0;
		}
	}

	if(m_isMovingRight)
		source.y = 2; //source corresponds with .png
	else if(m_isMovingLeft)
		source.y = 1;
	else if(m_onGround)
	{
		source.y = 0;
		source.x = 1;
	}
	else if(!m_onGround)
	{
		source.y = 3;
		source.x = 1;
	}

	m_sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32)); //make sure that texture is 32!!
}

void Player::Sound(sf::Time &deltaTime)
{
	if((m_isMovingRight || m_isMovingLeft) && m_onGround)
	{
		if(soundInt >= m_grassBuffer.getDuration().asSeconds()*1.2)
		{
			m_walking.play();
			soundInt = 0;
		}
	}

	if(soundInt <= m_grassBuffer.getDuration().asSeconds()*1.2)
		soundInt += deltaTime.asSeconds();
}

void Player::Draw(sf::RenderWindow &window)
{
	//window.draw(m_rect);
	window.draw(m_sprite);
}