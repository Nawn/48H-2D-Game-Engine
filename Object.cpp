#include "Object.h"

Object::Object(sf::Texture* texture, sf::Vector2i widthHeight) :
	m_texture(texture)
	{

	m_size.x = widthHeight.x;
	m_size.y = widthHeight.y;
	
	m_sprite.setTexture(*m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, widthHeight.x, widthHeight.y));

	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
}

sf::FloatRect Object::getBounds()
{
	return sf::FloatRect(int(getPosition().x - m_size.x / 2), int(getPosition().y - m_size.y / 2), m_size.x, m_size.y);
}