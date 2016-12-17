#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include <SFML\System\Clock.hpp>
#include <set>
#include "Player.h"

class Player;

class Enemy : public Object
{
public:
	Enemy(sf::Texture *texture, sf::Vector2i heightWidth, float speed);

	void setVelocity(float, float);
	sf::Vector2f getVelocity() const { return velocity; };
	void jump(float gravity);

	void canJump(bool);

	int update(float gravity, Player* player, std::set<Enemy *>& enemies, int& score, int& highscore);
private:
	bool m_jump;
	float m_speed;
	bool affectedByGravity;
	sf::Vector2f velocity;
	sf::Clock m_timer;
};

#endif // !ENEMY_H
