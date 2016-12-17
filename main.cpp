#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Platform.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

const int gWindowHeight = 750;
const int gWindowWidth = 750;

std::string gName = "Alien Killah";

#define GRAVITY 2000

Enemy* spawnMonster(sf::Texture* texture, float windowWidth, float windowHeight)
{
	Enemy* newEnem = new Enemy(texture, sf::Vector2i(50, 50), (rand() % 50) + 100);
	newEnem->setPosition(sf::Vector2f((rand() % (gWindowWidth / 2) + (gWindowWidth / 4)), (rand() % (gWindowHeight / 4)) + ((gWindowHeight / 4) * 3)));
	return newEnem;
}

int main()
{
	// generate the gameplay window
	sf::RenderWindow window(sf::VideoMode(gWindowHeight, gWindowWidth), gName);

	sf::Clock spawner;

	int score = 0;

	int highscore = 0;

	// load in the font
	sf::Font font;
	if (!font.loadFromFile("fonts/test_font.ttf"))
	{
		return -1;
	}
	// generate the welcoming text
	sf::Text welcome;
	welcome.setFont(font);
	welcome.setString("Score " + score);
	welcome.setCharacterSize(24);
	welcome.setFillColor(sf::Color::White);
	welcome.setOutlineColor(sf::Color::Black);
	welcome.setOutlineThickness(2.0f);
	welcome.setPosition(gWindowWidth / 2 - (gWindowWidth / 4), 50.0f);

	sf::Text highScore;
	highScore.setFont(font);
	highScore.setString("High Score " + highscore);
	highScore.setCharacterSize(18);
	highScore.setFillColor(sf::Color::White);
	highScore.setOutlineColor(sf::Color::Black);
	highScore.setOutlineThickness(2.0f);
	highScore.setPosition(gWindowWidth / 2, 150.0f);

	// generate debug text
	sf::Text debug;
	debug.setFont(font);
	debug.setCharacterSize(18);
	debug.setFillColor(sf::Color::White);
	debug.setOutlineColor(sf::Color::Black);
	debug.setOutlineThickness(2.0f);

	// generate skybox image
	sf::Texture sky;
	if (!sky.loadFromFile("sprites/sky.png"))
	{
		return -2;
	}

	// generate object
	sf::Sprite skyWall;
	skyWall.setTexture(sky);
	//skyWall.scale(1.0f, 2.5f);

	// get floor tile
	sf::Texture floorSprite;
	if (!floorSprite.loadFromFile("sprites/floor.png"))
	{
		return -3;
	}

	// grab player sprites
	sf::Texture playerSprite;
	if (!playerSprite.loadFromFile("sprites/player.png"))
	{
		return -4;
	}

	sf::Texture platformSprite;
	if (!platformSprite.loadFromFile("sprites/platform.png"))
	{
		return -5;
	}

	sf::Texture longPlatformSprite;
	if (!longPlatformSprite.loadFromFile("sprites/long_platform.png"))
	{
		return -6;
	}

	sf::Texture bulletSprite;
	if (!bulletSprite.loadFromFile("sprites/bullet.png"))
	{
		return -7;
	}

	sf::Texture enemySprite;
	if (!enemySprite.loadFromFile("sprites/enemy.png"))
	{
		return -8;
	}

	sf::Music music;
	if (!music.openFromFile("audio/music.wav"))
	{
		return -9;
	}

	sf::SoundBuffer fireSound;
	if (!fireSound.loadFromFile("audio/fire.wav"))
	{
		return -10;
	}

	sf::Sound fire;
	fire.setBuffer(fireSound);


	sf::SoundBuffer jumpSound;
	if (!jumpSound.loadFromFile("audio/jump.wav"))
	{
		return -11;
	}

	sf::Sound jump;
	jump.setBuffer(jumpSound);

	sf::SoundBuffer hitSound;
	if (!hitSound.loadFromFile("audio/hit.wav"))
	{
		return -12;
	}

	sf::Sound hit;
	hit.setBuffer(hitSound);

	sf::SoundBuffer dieSound;
	if (!dieSound.loadFromFile("audio/die.wav"))
	{
		return -13;
	}

	sf::Sound die;
	die.setBuffer(dieSound);

	music.play();
	music.setLoop(true);

	std::set<Projectile *> bulAddrs;

	std::set<Enemy *> enemAddrs;


	// create player object, drawable and transformable
	Player me(playerSprite, fire, jump, sf::Vector2i(25, 50), 500, bulAddrs);
	me.setBulletTexture(&bulletSprite);

	// set my player somewhere
	me.setPosition(350, 350);

	// create the floor. 
	Platform floor(floorSprite, sf::Vector2i(850, 100));

	// set position for floor
	floor.setPosition(gWindowWidth / 2, gWindowHeight - 50);

	// create the floating platform
	Platform testPlat(longPlatformSprite, sf::Vector2i(400, 15));

	// set to middle
	testPlat.setPosition(gWindowWidth / 2, (gWindowHeight / 2) + 175);

	Platform upperLeft(platformSprite, sf::Vector2i(200, 25));

	upperLeft.setPosition((gWindowWidth / 2) - 250, (gWindowHeight / 2) + 50);

	Platform upperRight(platformSprite, sf::Vector2i(200, 25));

	upperRight.setPosition((gWindowWidth / 2) + 250, (gWindowHeight / 2) + 50);

	Platform upperMiddle(longPlatformSprite, sf::Vector2i(400, 15));

	upperMiddle.setPosition((gWindowWidth / 2), (gWindowWidth / 2) - 100);

	Platform powerUpLayer(platformSprite, sf::Vector2i(200, 25));

	powerUpLayer.setPosition((gWindowWidth / 2), (gWindowHeight / 2) - 250);

	std::vector<Platform> platformsToDraw;

	platformsToDraw.push_back(floor);
	platformsToDraw.push_back(testPlat);
	platformsToDraw.push_back(upperLeft);
	platformsToDraw.push_back(upperRight);
	platformsToDraw.push_back(upperMiddle);
	platformsToDraw.push_back(powerUpLayer);
	int frameCount = 0;

	bool debugMenu = false;

	while (window.isOpen())
	{
		// Event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				else if (event.key.code == sf::Keyboard::V) // toggle the debug display
				{
					debugMenu ? debugMenu = false : debugMenu = true;
				} 
				else if (event.key.code == sf::Keyboard::M)
				{
					me.toggleFall();
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					me.enableFall();
					me.jump(GRAVITY);
				}
				else if (event.key.code == sf::Keyboard::Return)
				{
					me.fire();
				}
			} // Key Pressed 
			else if (event.type == sf::Event::KeyReleased)
			{

			}
		} // Poll event

		
		// Real-Time input handling
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			me.runLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			me.runRight();
		}
		else
		{
			me.setVelocity(0.0f, me.getVelocity().y);
		}
		// count the number of frames
		frameCount += 1;

		// SPAWNING MONSTERS HERE
		if (spawner.getElapsedTime().asSeconds() >= 0.75f)
		{
			spawner.restart();

			enemAddrs.insert(spawnMonster(&enemySprite, gWindowWidth, gWindowHeight));
		}

		me.update(GRAVITY);

		for (size_t i = 0; i < platformsToDraw.size(); i++)
		{
			if (platformsToDraw[i].update(me))
				i = platformsToDraw.size() + 1;
		}

		for (size_t i = 0; i < platformsToDraw.size(); i++)
		{

			if (platformsToDraw[i].update(me))
				i = platformsToDraw.size() + 1;
		}

		// debug values
		debug.setString(
			"Frame count " + std::to_string(frameCount) +
			"\ndebugMenu " + std::to_string(debugMenu) +
			"\nplayerVelocityX " + std::to_string(me.getVelocity().x) +
			"\nplayerVelocityY " + std::to_string(me.getVelocity().y) +
			"\ngravity " + std::to_string(GRAVITY) +
			"\nplayerLeft " + std::to_string(me.getPosition().x) +
			"\nplayerTop " + std::to_string(me.getPosition().y) +
			"\nplayerFacingLeft " + std::to_string(me.getDirection()) + 
			"\nalienNumber " + std::to_string(enemAddrs.size())
		);

		welcome.setString("Score\t" + std::to_string(score) + 
		"\nSpace to jump, Enter to shoot, WASD to move");

		highScore.setString("HighScore " + std::to_string(highscore));


		// drawing to the screen
		window.clear();

		// drawing to screen
		window.draw(skyWall);

		// drawing the platforms
		for (size_t i = 0; i < platformsToDraw.size(); i++)
		{
			window.draw(platformsToDraw[i]);
		}

		window.draw(welcome);
		window.draw(highScore);
		window.draw(me);

		// to create and draw out the projectiles I shoot
		std::set<Projectile *>::iterator it;
		std::set<Enemy *>::iterator it1;
		// for each bullet
		for (it = bulAddrs.begin(); it != bulAddrs.end(); ++it)
		{
			if (it != bulAddrs.end())
			{
				// draw it out unless it's out of bounds
				window.draw(**it);
				if ((*it)->update())
				{
					bulAddrs.erase(*it);
					break;
				}

				// then check each monster draw it, then see if it hit the bullet
				for (it1 = enemAddrs.begin(); it1 != enemAddrs.end(); ++it1)
				{
					if (it1 != enemAddrs.end())
					{
						// if out of bounds
						if ((*it)->checkMonster(**it1))
						{
							// erase the monster
							enemAddrs.erase(*it1);
							bulAddrs.erase(*it);
							score += 5;
							hit.setPitch((rand() % 2) + 0.5);
							hit.play();
							break;
						}
					}
				}
				break;
			}


		}

		// to create and draw out the enemies
		for (it1 = enemAddrs.begin(); it1 != enemAddrs.end(); ++it1)
		{
			if (it1 != enemAddrs.end())
			{
				window.draw(**it1);
				if ((*it1)->update(GRAVITY / 2, &me, enemAddrs, score, highscore) == 1)
				{
					enemAddrs.erase(*it1);
					break;
				}
				else if ((*it1)->update(GRAVITY / 2, &me, enemAddrs, score, highscore) == 2)
				{
					enemAddrs.clear();
					die.setPitch((rand() % 2) + 0.5);
					die.play();
					break;
				}
				else
				{
					// if I didn't disappear off screen, check if I hit a platform
					for (size_t i = 0; i < platformsToDraw.size(); i++)
					{
						platformsToDraw[i].update((**it1));
					}
				}
			}
		}

		if (debugMenu) // toggle-able menu
		{
			window.draw(debug);
		}
		window.display();
	}

	return 0;
}