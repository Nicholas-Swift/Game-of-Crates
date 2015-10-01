#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Crate.h"

class Tilemap
{
private:
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	std::vector<sf::Sprite> m_trees, m_rockshrooms, m_bushes;
	sf::Texture m_treesTexture, m_rockshroomsTexture, m_bushesTexture;

	std::vector<Crate> m_crates;
	std::vector<Platform> m_platforms;

	int m_level;
	int m_levelMap[50][50]; //50 because had to initilize a variable, make it bigger than neccessary.

	sf::Texture m_loadingScreenTexture;
	sf::Sprite m_loadingScreen;
	sf::Sprite m_loadingText;

	//credits
	sf::Sprite m_creditsSprite;
	sf::Texture m_creditsTexture;

public:
	int getLevelMap(int y, int x);
	int getLevel();
	void setMap(sf::RenderWindow &window), setMap(int i, sf::RenderWindow &window);

	std::vector<Platform> getPlatforms();
	float getPlatformSize(), getPlatformTop(int i), getPlatformBottom(int i), getPlatformLeft(int i), getPlatformRight(int i);
	sf::Vector2f getPlatformMovement(int i);

	float getCrateSize(), getCrateTop(int i), getCrateBottom(int i), getCrateLeft(int i), getCrateRight(int i);
	void setCratePos(int i, sf::Vector2f pos);
	bool getCrateOnLeft(int i), getCrateOnRight(int i);
	sf::Vector2f getCrateMovement(int i);
	void CrateCrateCollision(sf::RenderWindow &window);

private:
	void LoadLevelZero(), LoadLevelOne(), LoadLevelTwo(), LoadLevelThree(), LoadLevelFour(), LoadLevelFive(), LoadLevelSix(), LoadLevelSeven(), LoadLevelEight(), LoadLevelNine(), LoadLevelTen(), LoadLevelEleven(), LoadLevelTwelve(), LoadLevelThirteen(), LoadLevelFourteen(), LoadLevelFifteen(), LoadLevelCredits();

public:
	Tilemap(sf::RenderWindow &window);
	void Update(sf::Time &deltaTime, sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
};

#endif