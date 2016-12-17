#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderTarget.hpp>


class Object : public sf::Transformable, public sf::Drawable
{
public:
	// add functions to play with the entity's geometry / colors / texturing...
	Object(sf::Texture *texture, sf::Vector2i heightWidth);
	sf::Sprite getSprite() const { return m_sprite; }

	sf::FloatRect getBounds();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
											// apply the texture
		states.texture = m_texture;

		target.draw(m_sprite, states);
	}

	sf::Vector2f velocity;
	sf::Sprite m_sprite;
	sf::Texture* m_texture;
	sf::Vector2i m_size;
};

#endif // !OBJECT_H