#include "Flee.h"

Flee::Flee() :
	m_position(800, 400),
	m_velocity(0, 0),
	m_maxSpeed(1.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f)
{

	if (!m_texture.loadFromFile("flee.png")) {
		//error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3, 0.3);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_sprite.setOrigin(m_position.x - (m_sprite.getTextureRect().width / 2), m_position.y - (m_sprite.getTextureRect().height / 2));

}


Flee::~Flee()
{

}
float Flee::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}
void Flee::boundry(float x, float y)
{
	if (x > 2000)
	{
		m_position.x = -100;
	}
	if (x < 0)
	{
		m_position.x = 2100;
	}
	if (y < 0)
	{
		m_position.y = 2100;
	}
	if (y > 2000)
	{
		m_position.y = -100;
	}
}

float Flee::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}


void Flee::kinematicFlee(sf::Vector2f playerPosition)
{
	m_velocity = m_position - playerPosition;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//m_velocityF = m_velocityF * m_maxSpeed;
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}

void Flee::update(sf::Vector2f playerPosition)
{
	kinematicFlee(playerPosition);

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	boundry(m_sprite.getPosition().x, m_sprite.getPosition().y);
}


void Flee::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}