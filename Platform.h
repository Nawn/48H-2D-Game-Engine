#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML\Graphics\Sprite.hpp>
#include <string>

class Platform : public Object
{
public:
	Platform(sf::Texture &texture, sf::Vector2i widthHeight);

	bool update(Player& testColl);
	bool update(Enemy& testColl);
private:
	sf::Vector2i m_size;
	sf::Sprite m_sprite;
	sf::Texture* m_texture;
	bool passThrough;
};

#endif // !PLATFORM_H