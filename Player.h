#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include <SFML\System\Clock.hpp>
#include <SFML\Audio\Sound.hpp>
#include <set>
#include "Projectile.h"

class Projectile;

class Player : public Object
{
public:
	Player(sf::Texture& texture, sf::Sound& fireSound, sf::Sound& jumpSound, sf::Vector2i widthHeight, float speed, std::set<Projectile *>&);

	sf::Sprite getSprite() { return m_sprite; }
	sf::Vector2f getVelocity() const { return velocity; };
	void setVelocity(float, float);
	sf::Vector2i getSize() const { return m_size; }

	void setBulletTexture(sf::Texture *gunTexture);
	
	float update(float gravity);
	void enableFall() { affectedByGravity = true; }
	void disableFall() { affectedByGravity = false; }
	void toggleFall() { affectedByGravity ? affectedByGravity = false : affectedByGravity = true; }
	bool getDirection() const { return facingLeft; }
	void toggleDirection();
	void jump(float gravity);
	void canJump(bool jumpStatus);
	void fire();
	void die();

	void runLeft();
	void runRight();

private:

	bool facingLeft;
	bool m_jump;
	bool affectedByGravity;
	float m_speed;
	std::set<Projectile *> &b_holder;
	sf::Sprite m_sprite;
	sf::Vector2f velocity;
	sf::Texture* m_texture;
	sf::Sound* m_fireSound;
	sf::Sound& m_jumpSound;
	sf::Texture* b_texture;
	sf::Clock timer;
	sf::Vector2i m_size;
};

#endif // !PLAYER_H