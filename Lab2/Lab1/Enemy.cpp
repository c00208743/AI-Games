#include "Enemy.h"


Enemy::Enemy() :
	m_position(0, 0),
	m_velocity(0, 0),
	m_size(50)
{
	m_enemy.setRadius(float(m_size));
	m_enemy.setFillColor(sf::Color::Red);
	m_enemy.setPosition(m_position);
	if (!texture.loadFromFile("alien.png"))
	{
		// error...
	}

	sprite.setTexture(texture);

}


Enemy::~Enemy()
{
}

void Enemy::update(double dt)
{
	srand(time(NULL));
	m_velocity.x = (rand() % 10) + 1;
	m_velocity.y = (rand() % 10) + 1;
	//slow down AI
	m_velocity.x = m_velocity.x / 10;
	m_velocity.y = m_velocity.y / 10;
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
	sprite.setPosition(m_enemy.getPosition().x, m_enemy.getPosition().y);
}

void Enemy::render(sf::RenderWindow & window)
{
	window.draw(sprite);
}
