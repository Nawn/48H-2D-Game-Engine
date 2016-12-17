#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2i widthHeight, float speed) :
	Object(texture, widthHeight),
	affectedByGravity(true),
	m_speed(speed)
{
	velocity.x = speed;
	velocity.y = 0;
}

int Enemy::update(float gravity, Player* player, std::set<Enemy *>& enemies, int& score, int& highscore)
{
	float elapsedTime = m_timer.restart().asSeconds();

	if (affectedByGravity)
	{
		if (velocity.y >= (gravity * -1))
		{
			velocity.y -= gravity * elapsedTime;
		}
	}
	else
	{
		velocity.y = 0;
	}

	if (getPosition().x >= player->getPosition().x && velocity.x >= -1)
	{
		velocity.x *= -1;
	}
	else if (getPosition().x <= player->getPosition().x && velocity.x <= 1)
	{
		velocity.x *= -1;
	}

	if (getPosition().y - 50 >= player->getPosition().y)
	{
		jump(gravity);
	}

	if (player->getBounds().intersects(getBounds()))
	{
		player->die();
		if (score > highscore)
		{
			highscore = score;
		}
		score = 0;
		return 2;
	}

	move((velocity.x * elapsedTime), (velocity.y * elapsedTime * -1));

	if (getPosition().x <= 1 || getPosition().x >= 800)
	{
		return 1;
	}
	else if (getPosition().y <= 1 || getPosition().y >= 800)
	{
		return 1;
	}

	return 0;
}

void Enemy::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Enemy::canJump(bool jumpStatus)
{
	m_jump = jumpStatus;
}

void Enemy::jump(float gravity)
{
	if (m_jump)
	{
		gravity = gravity / 2.5;
		velocity.y += gravity / 1.25;
		canJump(false);
	}
}