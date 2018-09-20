#include "Enemy.h"


Enemy::Enemy() :
	m_position(0, 0),
	m_velocity(0, 0),
	m_size(50)
{
	m_enemy.setOutlineColor(sf::Color::White);
	m_enemy.setRadius(m_size);
	m_enemy.setFillColor(sf::Color::Red);

}


Enemy::~Enemy()
{
}

void Enemy::update(double dt)
{
	srand(time(NULL));
	m_velocity.x = (rand() % 10) + 1;
	m_velocity.y = (rand() % 10) + 1;
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
	m_enemy.setPosition(m_position.x, m_position.y);

	
	if (m_enemy.getPosition().x > 2100)
	{
		m_position.x = -100;
	}
	if (m_enemy.getPosition().x < -100)
	{
		m_position.x = 2100;
	}
	if (m_enemy.getPosition().y < -100)
	{
		m_position.y = 2100;
	}
	if (m_enemy.getPosition().y > 2100)
	{
		m_position.y = -100;
	}

}

void Enemy::render(sf::RenderWindow & window)
{
	window.draw(m_enemy);
}
