#include "Player.h"
#include <iostream>

Player::Player() :
	m_position(0, 0),
	m_velocity(0, 0),
	size(50)
{
	m_shape.setRadius(float(size));
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setPosition(m_position);
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

	m_shape.setPosition(m_shape.getPosition().x + m_velocity.x, m_shape.getPosition().y + m_velocity.y);

	//key presses 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//std::cout << 
		m_velocity.x -= .001f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_velocity.x += .001f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_velocity.y -= .001f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_velocity.y += .001f;
	}

	//looping screen 
	if (m_shape.getPosition().x > 2100)
	{
		m_shape.setPosition(-100, m_shape.getPosition().y);
	}
	if (m_shape.getPosition().x < -100)
	{
		m_shape.setPosition(2100, m_shape.getPosition().y);
	}
	if (m_shape.getPosition().y < -100)
	{
		m_shape.setPosition(m_shape.getPosition().y, 2100);
	}
	if (m_shape.getPosition().y > 2100)
	{
		m_shape.setPosition(m_shape.getPosition().y, -100);
	}
}

void Player::render(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

