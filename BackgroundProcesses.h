#ifndef BACKGROUND_PROCESSES_H
#define BACKGROUND_PROCESSES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class BackgroundProcesses
{
private:
	float m_spawnTime, m_spawnMaxTime, m_cloudMax, m_whispMax, m_cloudMoveSpeed, m_whispMoveSpeed;
	int m_rctInt, m_rcInt, m_rcsInt, m_rwtInt, m_rwInt, m_rwsInt;  //r(andom), t(exture), c(loud), w(hisp), s(cale)
	std::vector<int> m_rctRandom, m_rcRandom, m_rcsRandom, m_rwtRandom, m_rwRandom, m_rwsRandom;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;

	sf::Texture m_cloudsTexture;
	std::vector<sf::Sprite> m_clouds;

	sf::Texture m_whispsTexture;
	std::vector<sf::Sprite> m_whisps;

	sf::Music m_musicBackground;
	sf::Music m_soundWind;

public:
	void setMusicVolume(int i);
	void setSoundEffectsVolume(int i);

public:
	BackgroundProcesses();
	void Update(sf::Time &deltaTime, sf::RenderWindow &window);
	void ViewUpdate(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	void Resize(sf::Vector2f size);
};

#endif