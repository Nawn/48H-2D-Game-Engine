#include "Player.h"

// constructor
Player::Player(sf::Texture& texture, sf::Sound& fireSound, sf::Sound& jumpSound, sf::Vector2i widthHeight, float speed, std::set<Projectile *> &bulHolder) :
	Object(&texture, widthHeight),
	m_fireSound(&fireSound),
	m_jumpSound(jumpSound),
	affectedByGravity(true),
	m_speed(speed),
	m_jump(true),
	b_holder(bulHolder)
{
	velocity.x = 0;
	velocity.y = 0;
}


// takes in the force of gravity to apply 
float Player::update(float gravity)
{
	float elapsedTime = timer.restart().asSeconds();

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

	move((velocity.x * elapsedTime), (velocity.y * elapsedTime * -1));

	if (getPosition().x <= 1 || getPosition().x >= 750)
	{
		setPosition(sf::Vector2f(350, getPosition().y));
	}
	
	if (getPosition().y <= -150 || getPosition().y >= 750)
	{
		setPosition(sf::Vector2f(getPosition().x, 350));
	}


	return elapsedTime;
}

// simply increases the velocity to make the player jump
void Player::jump(float gravity)
{
	if (m_jump)
	{
		gravity = gravity / 2;
		move(sf::Vector2f(0, gravity * -1 * 0.02));
		velocity.y += gravity / 1.25;
		canJump(false);
		m_jumpSound.setPitch((rand() % 2) + 0.5);
		m_jumpSound.play();
	}
}

void Player::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Player::runLeft()
{
	if (!facingLeft)
	{
		toggleDirection();
	}
	velocity.x = m_speed * -1;
}

void Player::runRight()
{
	if (facingLeft)
	{
		toggleDirection();
	}
	velocity.x = m_speed;
}

void Player::canJump(bool jumpStatus)
{
	m_jump = jumpStatus;
}

void Player::toggleDirection()
{
	facingLeft ? facingLeft = false : facingLeft = true;
	scale(-1, 1);
}

void Player::fire()
{
	if (facingLeft)
	{
		Projectile *bullet = new Projectile(b_texture, sf::Vector2i(10, 5), sf::Vector2f(-2000, 0));
		bullet->setPosition(getPosition());
		b_holder.insert(bullet);
	}
	else
	{
		Projectile *bullet = new Projectile(b_texture, sf::Vector2i(10, 5), sf::Vector2f(2000, 0));
		bullet->setPosition(getPosition());
		b_holder.insert(bullet);
	}
	m_fireSound->setPitch((rand() % 2) + 0.5);
	m_fireSound->play();
}

void Player::setBulletTexture(sf::Texture* bulletSprite)
{
	 b_texture = bulletSprite;
}

void Player::die()
{
	setPosition(350, 50);
}