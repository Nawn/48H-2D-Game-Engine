#include "Platform.h"

Platform::Platform(sf::Texture &texture, sf::Vector2i widthHeight) : Object(&texture, widthHeight)
{

}

bool Platform::update(Player &testColl) 
{
	if (getBounds().intersects(testColl.getBounds()))
	{
		testColl.setVelocity(testColl.getVelocity().x, 200.0f);

		testColl.canJump(true);
		return true;
	}
	else
	{
		return false;
	}
}

bool Platform::update(Enemy& testColl)
{
	if (getBounds().intersects(testColl.getBounds()))
	{
		testColl.setVelocity(testColl.getVelocity().x, 200.0f);

		testColl.canJump(true);

		return true;
	}
	else
	{
		return false;
	}
}