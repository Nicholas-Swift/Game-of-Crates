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

public:
	int getLevelMap(int y, int x);
	void setMap(int i);

	std::vector<Platform> getPlatforms();
	float getPlatformSize(), getPlatformTop(int i), getPlatformBottom(int i), getPlatformLeft(int i), getPlatformRight(int i);
	sf::Vector2f getPlatformMovement(int i);

	float getCrateSize(), getCrateTop(int i), getCrateBottom(int i), getCrateLeft(int i), getCrateRight(int i);
	void setCratePos(int i, sf::Vector2f pos);
	bool getCrateOnLeft(int i), getCrateOnRight(int i);
	sf::Vector2f getCrateMovement(int i);
	void CrateCrateCollision();

public:
	Tilemap();
	void Update(sf::Time &deltaTime);
	void Draw(sf::RenderWindow &window);
};

#endif