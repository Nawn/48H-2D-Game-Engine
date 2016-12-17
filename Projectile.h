#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE

#include "Object.h"
#include "Enemy.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <set>

class Enemy;

class Projectile : public Object
{
public:
	Projectile(sf::Texture*, sf::Vector2i, sf::Vector2f);
	~Projectile();

	bool checkMonster(Enemy& enemy);

	bool update();
private:

	sf::Vector2f velocity;
	sf::Clock m_timer;
};

#endif // !PROJECTILE_H