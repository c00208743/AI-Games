#include "Player.h"
#include <iostream>
#include "math.h"

#define M_PI   3.14159265358979323846264338327950288

Player::Player() :
	m_position(300, 300),
	m_velocity(0, 0),
	size(50),
	speed(0)
{
	
	if (!m_texture.loadFromFile("rocket.png"))
	{
		// error...
	}
	
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(128, 128);
	m_sprite.setPosition(m_position);
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
Player::~Player()
{
}

void Player::update(double dt)
{

	//increase velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (speed < 1)
		{
			speed = speed + 0.01;
		}
	}
	else
	{
		if (speed > 0)
		{
			speed = speed - 0.001;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed > -1)
		{
			speed = speed - 0.01;
		}
	}
	else
	{
		if (speed < 0)
		{
			speed = speed + 0.001;
		}
	}
	//change rotation 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_sprite.rotate(-0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_sprite.rotate(0.1);
	}

	//Apply direction to sprite
	float radians = m_sprite.getRotation()* M_PI / 180;
	direction.x = (cos(radians));
	direction.y = (sin(radians));
	m_sprite.setPosition(m_sprite.getPosition().x + (direction.x * speed), m_sprite.getPosition().y + (direction.y * speed));


	//looping screen 
	if (m_sprite.getPosition().x > 2100)
	{
		m_sprite.setPosition(-100, m_sprite.getPosition().y);
	}
	if (m_sprite.getPosition().x < -100)
	{
		m_sprite.setPosition(2100, m_sprite.getPosition().y);
	}
	if (m_sprite.getPosition().y < -100)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, 2100);
	}
	if (m_sprite.getPosition().y > 2100)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, -100);
	}

}

void Player::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}


sf::Vector2f Player::getPosition()
{
	return m_sprite.getPosition();
}

