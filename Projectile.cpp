#include "Projectile.h"

Projectile::Projectile(sf::Texture* texture, sf::Vector2i widthHeight, sf::Vector2f velocity) :
	Object(texture, widthHeight),
	velocity(velocity)
{

}

Projectile::~Projectile()
{

}

bool Projectile::update()
{
	float elapsedTime = m_timer.restart().asSeconds();

	move((velocity.x * elapsedTime), (velocity.y * elapsedTime * -1));

	
	if (getPosition().x <= 1 || getPosition().x >= 800)
	{
		return true;
	}
	return false;
}

bool Projectile::checkMonster(Enemy& monster)
{
	if (monster.getBounds().intersects(getBounds()))
	{
		return true;
	}

	return false;
}

/*
void Projectile::update(sf::RenderWindow &window)
{
	window.draw(*this);
}
*/