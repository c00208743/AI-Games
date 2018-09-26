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
	
	if (!texture.loadFromFile("rocket.png"))
	{
		// error...
	}
	
	sprite.setTexture(texture);
	sprite.setOrigin(128, 128);
	sprite.setPosition(m_position);
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
		sprite.rotate(-0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite.rotate(0.1);
	}
	//Apply direction to sprite
	float radians = sprite.getRotation()* M_PI / 180;
	direction.x = (cos(radians));
	direction.y = (sin(radians));
	sprite.setPosition(sprite.getPosition().x + (direction.x * speed), sprite.getPosition().y + (direction.y * speed));


	//looping screen 
	if (sprite.getPosition().x > 2100)
	{
		//m_shape.setPosition(-100, m_shape.getPosition().y);
		sprite.setPosition(-100, sprite.getPosition().y);
	}
	if (sprite.getPosition().x < -100)
	{
		//m_shape.setPosition(2100, m_shape.getPosition().y);
		sprite.setPosition(2100, sprite.getPosition().y);
	}
	if (sprite.getPosition().y < -100)
	{
		//m_shape.setPosition(m_shape.getPosition().y, 2100);
		sprite.setPosition(sprite.getPosition().x, 2100);
	}
	if (sprite.getPosition().y > 2100)
	{
		//m_shape.setPosition(m_shape.getPosition().y, -100);
		sprite.setPosition(sprite.getPosition().x, -100);
	}

	//sprite.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);
}

void Player::render(sf::RenderWindow & window)
{
	window.draw(sprite);
}

