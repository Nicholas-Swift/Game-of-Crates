#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "BackgroundProcesses.h"

const sf::Vector2f WINDOW_SIZE(960, 640);

//NOTE: have to change things were it says "NOTE:" if you add or takeaway cloud textures. The number of cloud textures.

void BackgroundProcesses::setMusicVolume(int i)
{
	if(i <= 0)
		m_musicBackground.setVolume(0);
	else
		m_musicBackground.setVolume(i*1.5);
}

void BackgroundProcesses::setSoundEffectsVolume(int i)
{
	if(i <= 0)
		m_soundWind.setVolume(0);
	else
		m_soundWind.setVolume(i);
}

//used by BackgroundProcesses() and Update() for spawning clouds and whisps
void SpawnHelper(sf::RenderWindow &window, std::vector<sf::Sprite> &v, sf::Texture &texture, int &t, std::vector<int> &tV, int &p, std::vector<int> &pV, int &s, std::vector<int> &sV)
{
	sf::Sprite *sprite = new sf::Sprite; //create sprite
	sprite->setTexture(texture);

	//set which kind of sprite texture to random
	sprite->setTextureRect(sf::IntRect(tV[t] * texture.getSize().x/3, 0, texture.getSize().x/3, texture.getSize().y)); //NOTE: BEACAUSE 3 whisps
	if(t < (tV.size() - 1)) // - 1 because vector starts at 0
		t += 1;
	else
		t = 0;
	
	//set sprite position to random
	sprite->setPosition(window.getView().getCenter().x + WINDOW_SIZE.x/2, window.getView().getCenter().y - WINDOW_SIZE.y/2 + pV[p]);
	if(p < (pV.size() - 1))
		p += 1;
	else
		p = 0;

	//set sprite scale to random
	sprite->setScale(0.1 * sV[s], 0.1 * sV[s]);
	if(s < (sV.size() - 1))
		s += 1;
	else
		s = 0;

	v.push_back(*sprite);
}

void SpawnHelper(std::vector<sf::Sprite> &v, sf::Texture &texture, int &t, std::vector<int> &tV, int &p, std::vector<int> &pV, int &s, std::vector<int> &sV)
{
	sf::Sprite *sprite = new sf::Sprite; //create sprite
	sprite->setTexture(texture);

	//set which kind of sprite texture to random
	sprite->setTextureRect(sf::IntRect(tV[t] * texture.getSize().x/3, 0, texture.getSize().x/3, texture.getSize().y)); //NOTE: BEACAUSE 3 whisps
	if(t < (tV.size() - 1)) // - 1 because vector starts at 0
		t += 1;
	else
		t = 0;
	
	//set sprite position to random
	sprite->setPosition(WINDOW_SIZE.x, pV[p]);
	if(p < (pV.size() - 1))
		p += 1;
	else
		p = 0;

	//set sprite scale to random
	sprite->setScale(0.1 * sV[s], 0.1 * sV[s]);
	if(s < (sV.size() - 1))
		s += 1;
	else
		s = 0;

	v.push_back(*sprite);
}


BackgroundProcesses::BackgroundProcesses()
{
	//change these to change everything else!
	m_spawnTime = 0;
	m_spawnMaxTime = 3;

	m_cloudMax = 5;
	m_whispMax = 4;

	m_cloudMoveSpeed = 0.068;
	m_whispMoveSpeed = 0.082;

	//NOTE: have clouds speed depending on scale in move funciton way below

	//random stuff
	m_rctInt = m_rcInt = m_rcsInt = m_rwtInt =  m_rwInt = m_rwsInt = 0;
	m_rctRandom.clear(); m_rcRandom.clear(); m_rcsRandom.clear(); m_rwtRandom.clear(); m_rwRandom.clear(); m_rwsRandom.clear();

	int rct[20] = {1, 2, 2, 0, 0, 1, 2, 0, 1, 1, 2, 1, 0, 1, 2, 0, 1, 0, 2, 2}; //NOTE: 3 different cloud textures
	m_rctRandom.insert(m_rctRandom.end(), rct, rct+20);
	int rc[20] = {200, 400, 300, 100, 200, 300, 400, 200, 100, 200, 100, 300, 400, 200, 400, 300, 100, 300, 200, 300}; //multiple places across the y-axis that clouds can spawn
	m_rcRandom.insert(m_rcRandom.end(), rc, rc+20);
	int rcs[20] = {8, 10, 9, 11, 12, 9, 8, 11, 9, 10, 8, 11, 10, 12, 8, 9, 10, 9, 11, 12}; //random cloud scale
	m_rcsRandom.insert(m_rcsRandom.end(), rcs, rcs+20);
	int rwt[20] = {1, 2, 2, 0, 0, 1, 2, 0, 1, 1, 2, 1, 0, 1, 2, 0, 1, 0, 2, 2}; //NOTE: 3 different whisp textures
	m_rwtRandom.insert(m_rwtRandom.end(), rwt, rwt+20);
	int rw[20] = {200, 100, 300, 400, 300, 400, 200, 300, 400, 100, 200, 400, 100, 200, 300, 200, 400, 300, 100, 200}; //multiple places across the y-axis that whisps can spawn
	m_rwRandom.insert(m_rwRandom.end(), rw, rw+20);
	int rws[20] = {8, 10, 9, 11, 12, 9, 8, 11, 9, 10, 8, 11, 10, 12, 8, 9, 10, 9, 11, 12}; //random whisp scale
	m_rwsRandom.insert(m_rwsRandom.end(), rws, rws+20);

	//load the background
	m_backgroundTexture.loadFromFile("Assets/background.png");
	m_background.setPosition(0, 0); m_background.setTexture(m_backgroundTexture); m_background.setScale(WINDOW_SIZE.x / m_backgroundTexture.getSize().x, WINDOW_SIZE.y / m_backgroundTexture.getSize().y);

	//scatter clouds around current level
	m_cloudsTexture.loadFromFile("Assets/cloudTexture.png");
	m_clouds.clear();

	int initialClouds[5] = {-100, 0, 200, 100}; //NOTE: because m_cloudsMax-1 = 4
	for(int i = 0; i < (m_cloudMax - 1); i++) //because comment above ^
	{
		SpawnHelper(m_clouds, m_cloudsTexture, m_rctInt, m_rctRandom, m_rcInt, m_rcRandom, m_rcsInt, m_rcsRandom);
		m_clouds[i].setPosition(initialClouds[i], m_clouds[i].getPosition().y);
	}

	//scatter whisps around current level
	m_whispsTexture.loadFromFile("Assets/whispTexture.png");
	m_whisps.clear();

	int initialWhisps[4] = {700, 300, 100}; //NOTE: because m_whispsMax-1 = 3
	for(int i = 0; i < (m_whispMax - 1); i++) //^ because comment above
	{
		SpawnHelper(m_whisps, m_whispsTexture, m_rwtInt, m_rwtRandom, m_rwInt, m_rwRandom, m_rwsInt, m_rwsRandom);
		m_whisps[i].setPosition(initialWhisps[i], m_whisps[i].getPosition().y);
	}

	m_musicBackground.openFromFile("Assets/Path to Lake Land.ogg");
	m_musicBackground.setLoop(true);
	m_musicBackground.play();

	m_soundWind.openFromFile("Assets/Wind.wav");
	m_soundWind.setLoop(true);
	m_soundWind.play();

	setMusicVolume(0);
	setSoundEffectsVolume(0);
}

void BackgroundProcesses::Update(sf::Time &deltaTime, sf::RenderWindow &window)
{
	//increase spawning time
	m_spawnTime += deltaTime.asSeconds();

	//despawn clouds and whisps
	for(int i = 0; i < m_clouds.size(); i++) //despawn clouds
		if(m_clouds[i].getPosition().x + m_clouds[i].getGlobalBounds().width < window.getView().getCenter().x - WINDOW_SIZE.x/2 || //out of bounds left
			m_clouds[i].getPosition().y + m_clouds[i].getGlobalBounds().height < window.getView().getCenter().y - WINDOW_SIZE.y/2 || //out of bounds top
			m_clouds[i].getPosition().y > window.getView().getCenter().y + WINDOW_SIZE.y/2) //out of bounds bottom
			m_clouds.erase(m_clouds.begin() + i);
	for(int i = 0; i < m_whisps.size(); i++) //despawn whisps
		if(m_whisps[i].getPosition().x + m_whisps[i].getGlobalBounds().width < window.getView().getCenter().x - WINDOW_SIZE.x/2 ||
			m_whisps[i].getPosition().y + m_whisps[i].getGlobalBounds().height < window.getView().getCenter().y - WINDOW_SIZE.y/2 ||
			m_whisps[i].getPosition().y > window.getView().getCenter().y + WINDOW_SIZE.y/2)
			m_whisps.erase(m_whisps.begin() + i);

	//spawn clouds and whisps
	if(m_spawnTime >= m_spawnMaxTime)
	{
		//spawn clouds
		if(m_clouds.size() <= m_cloudMax)
			SpawnHelper(window, m_clouds, m_cloudsTexture, m_rctInt, m_rctRandom, m_rcInt, m_rcRandom, m_rcsInt, m_rcsRandom);

		//spawn whisp
		if(m_whisps.size() <= m_whispMax)
			SpawnHelper(window, m_whisps, m_whispsTexture, m_rwtInt, m_rwtRandom, m_rwInt, m_rwRandom, m_rwsInt, m_rwsRandom);

		m_spawnTime = 0;
	}

	//update all the sprites with movement
	for(int i = 0; i < m_clouds.size(); i++)
		m_clouds[i].move(-m_cloudMoveSpeed * 0.4 * m_clouds[i].getScale().x * deltaTime.asMilliseconds(), 0);
	for(int i = 0; i < m_whisps.size(); i++)
		m_whisps[i].move(-m_whispMoveSpeed * 0.4 * m_whisps[i].getScale().x * deltaTime.asMilliseconds(), 0);
}

void BackgroundProcesses::ViewUpdate(sf::RenderWindow &window)
{
	m_background.setPosition(window.getView().getCenter().x - window.getSize().x/2, window.getView().getCenter().y - window.getSize().y/2);
}

void BackgroundProcesses::Draw(sf::RenderWindow &window)
{
	window.draw(m_background);

	for(int i = 0; i < m_clouds.size(); i++)
		window.draw(m_clouds[i]);
	for(int i = 0; i < m_whisps.size(); i++)
		window.draw(m_whisps[i]);
}

void BackgroundProcesses::Resize(sf::Vector2f size)
{
	m_background.setScale(size.x / WINDOW_SIZE.x, size.y / WINDOW_SIZE.y);
}